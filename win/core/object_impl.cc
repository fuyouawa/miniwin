#include "win/core/object_impl.h"

#include <format>
#include <mutex>
#include <shared_mutex>

#include "win/tools/debug.h"

namespace miniwin {
namespace {
std::mutex signal_mutex_pool[131];

auto& signal_mutex(const Object* obj) {
	return signal_mutex_pool[
		reinterpret_cast<uintptr_t>(obj) %
		(sizeof(signal_mutex_pool) / sizeof(std::mutex))];
}
} // namespace

Object::Impl::Impl(Object* owner)
	: owner_(owner), connections_manager_() {}

Object::Impl::~Impl() {
	{
		std::lock_guard lk{ signal_mutex(owner_) };

		deleting_ = true;

		for (auto& conns : connections_manager_.map_) {
			conns.second.Clear();
		}

		for (auto& sender_conn : connected_sender_connections_) {
			auto sender = sender_conn->sender;
			std::unique_lock<std::mutex> lk2;
			if (owner_ != sender)
				lk2 = std::unique_lock(signal_mutex(sender));

			if (!sender_conn || sender_conn->sender != sender) {
				// 也许就在迭代时没有锁的那段间隔, 这个连接就被切断了
				continue;
			}
			sender_conn->receiver = nullptr;
			sender->impl_->connections_manager_.dirty_ = true;
		}
	}

	DeleteChildren();
	SetParent(nullptr);
}

void Object::Impl::ConnectionsManager::ClearDirty() {
	if (dirty_) {
		for (auto& conns : map_) {
			std::lock_guard lk(conns.second.mutex_);
			conns.second.EraseIf([](auto& c) {
				return !c->receiver;
				});
		}
		dirty_ = false;
	}
}

Object::Disconnecter Object::Impl::ConnectImpl(const Object* sender, const std::type_info& signal_info,
                                               const Object* receiver, internal::UniqueSlotObject&& slot_obj,
                                               ConnectionFlags connection_flags,
                                               InvokeType invoke_type) {
	bool has_unique_flag = (connection_flags & ConnectionFlags::kUnique) != ConnectionFlags::kNone;
	bool has_replace_flag = (connection_flags & ConnectionFlags::kReplace) != ConnectionFlags::kNone;

	MW_ASSERT_X(!(has_unique_flag && has_replace_flag));

	// 如果connection_type是Unique, 表示不重复连接
	// 检测目标Signal中所有Connection的Slot是否有跟当前想连接的Slot重复的
	if (has_unique_flag || has_replace_flag) {
		std::unique_lock lk(signal_mutex(sender));
		// 获取当前链接的ConnectionList
		auto sender_conns = sender->impl_->connections_manager_.map_.find(signal_info);
		if (sender_conns != sender->impl_->connections_manager_.map_.end()) {
			// 锁住ConnectionList，解锁sender
			std::lock_guard lk2(sender_conns->second.mutex_);
			lk.unlock();

			if (sender_conns->first != signal_info) {
				//TODO throw 优化
				auto errmsg = std::format(
					"Maybe hash conflict between signal '{}' and signal '{}', try to change the name or parameter of one of them",
					sender_conns->first.name(), signal_info.name());
				throw std::exception(errmsg.c_str());
			}

			auto conn = sender_conns->second.FindIf([receiver, &slot_obj](auto& c) {
				return c->receiver == receiver && c->slot_obj->Compare(slot_obj.get());
			});
			MW_ASSERT_X((*conn)->signal_info == signal_info);

			if (!conn.IsEnd()) {
				if (has_unique_flag) {
					//TODO has_unique_flag暂时啥也不干
				}
				else {
					(*conn)->slot_obj = std::move(slot_obj);
				}
				return {
					[c = *conn, sender] {
						return sender->impl_->DisconnectImpl(c);
					}
				};
			}
		}
	}

	auto conn = std::make_shared<Connection>(sender, receiver, std::move(slot_obj), signal_info, connection_flags,
	                                         invoke_type);

	return sender->impl_->AddConnection(std::move(conn));
}

void Object::Impl::Init(Object* parent) {
	SetParent(parent);
}

void Object::Impl::EmitSignalImpl(const type_info& signal_info, const internal::SharedSlotArgsStore& args_store) {
	// 给自身上锁
	std::unique_lock lk{ signal_mutex(owner_)};

	// 找到信号对应的槽连接列表
	auto conns = connections_manager_.map_.find(signal_info);
	if (conns == connections_manager_.map_.end())
		return;
	std::lock_guard lk2(conns->second.mutex_);
	lk.unlock();

	// 遍历连接，触发槽函数
	for (auto& c : conns->second) {
		MW_ASSERT_X(c->sender == owner_ && c->signal_info == signal_info);

		// 触发槽函数
		c->receiver->Invoke([receiver = c->receiver, slot_obj = &c->slot_obj, as = args_store] {
			if (!receiver || !*slot_obj) return;
			(*slot_obj)->Call(receiver, as.get());
		}, c->invoke_type);
	}
}

bool Object::Impl::DisconnectImpl(const SharedConnection& connection) {
	if (connection->receiver == nullptr) return false;
	{
		std::unique_lock lk{ signal_mutex(owner_) };
		auto conns = connections_manager_.map_.find(connection->signal_info);
		if (conns == connections_manager_.map_.end())
			return false;
		std::lock_guard lk2(conns->second.mutex_);
		lk.unlock();

		conns->second.Erase(connection);
	}
	{
		std::lock_guard lk{ signal_mutex(connection->receiver) };
		connection->receiver->impl_->connected_sender_connections_.Erase(connection);
	}
	return true;
}

Object::Disconnecter Object::Impl::AddConnection(SharedConnection&& conn) {
	{
		std::lock_guard lk(signal_mutex(conn->receiver));
		conn->receiver->impl_->connected_sender_connections_.EmplaceBack(conn);
	}

	{
		std::unique_lock lk(signal_mutex(owner_));
		MW_ASSERT_X(owner_ == conn->sender);
		auto [conns, _] = connections_manager_.map_.try_emplace(conn->signal_info);

		std::unique_lock lk2(conns->second.mutex_);
		conns->second.EmplaceBack(conn);
		lk2.unlock();

		connections_manager_.ClearDirty();
	}
	return {
		[this, c = std::move(conn)] {
			return DisconnectImpl(c);
		}
	};
}

void Object::Impl::SetParent(Object* parent) {
	if (owner_ == parent || parent_ == parent)
		return;
	auto prev_parent = parent_;

	// 如果parent正在删除中, 就不处理
	if (prev_parent && !prev_parent->impl_->deleting_) {
		auto item = prev_parent->impl_->child_items_.FindIf([owner = owner_](const ChildItem& i) {
			return i.obj == owner;
		});
		// 如果没在原父级的子列表中找到自己，说明只是加入了父级的pending_addition_children_，但是父级还没处理
		if (item.IsEnd()) {
			// 从原父级的添加队列中删除自己
			auto s = prev_parent->impl_->pending_addition_children_.Erase(owner_);
			MW_ASSERT_X(s > 0);
		}
		else {
			prev_parent->impl_->dirty_ = true;
			item->orphaned = true;
		}
	}

	if (parent) {
		parent->impl_->pending_addition_children_.PushBack(owner_);
	}
	parent_ = parent;
}

List<Object*> Object::Impl::GetChildrenWithProcess() {
	MW_ASSERT_X(children_cache_.size() == child_items_.size());
	// 处理移除的子物体
	if (dirty_) {
		children_cache_.Clear();

		auto remove_count = child_items_.EraseIf([](const ChildItem& i) {
			return i.orphaned;
		});
		if (dirty_)
			MW_ASSERT_X(remove_count > 0);

		children_cache_ = child_items_.Transform<Object*>([](const ChildItem& i) {
			return i.obj;
		});
		dirty_ = false;
	}

	// 处理添加的子物体
	for (auto c : pending_addition_children_) {
		child_items_.EmplaceBack(false, c);
		children_cache_.EmplaceBack(c);
	}
	pending_addition_children_.Clear();

	return children_cache_;
}

void Object::Impl::DeleteChildren() {
	for (auto i : child_items_) {
		if (!i.orphaned) {
			delete i.obj;
		}
	}
	child_items_.Clear();
	children_cache_.Clear();
}
}
