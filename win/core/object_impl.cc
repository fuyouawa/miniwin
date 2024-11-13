#include "win/core/object_impl.h"

#include <format>
#include <mutex>
#include <shared_mutex>

#include "win/tools/debug.h"

namespace miniwin {
namespace {
// std::mutex signal_mutex_pool[131];
//
// auto& signal_mutex(const Object* obj) {
// 	return signal_mutex_pool[
// 		reinterpret_cast<uintptr_t>(obj) %
// 		(sizeof(signal_mutex_pool) / sizeof(std::mutex))];
// }
std::shared_mutex signal_shared_mutex_pool[131];

auto& signal_shared_mutex(const Object* obj) {
	return signal_shared_mutex_pool[
		reinterpret_cast<uintptr_t>(obj) %
			(sizeof(signal_shared_mutex_pool) / sizeof(std::shared_mutex))];
}
} // namespace

Object::Impl::Impl(Object* owner)
	: owner_(owner), connections_manager_() {}

Object::Impl::~Impl() {
	std::unique_lock lk{ signal_shared_mutex(owner_)};

	deleting_ = true;
	if (!connections_manager_.map_.empty() || !connected_sender_connections_.empty()) {
		for (auto& conns : connections_manager_.map_) {
			for (auto& c : conns.second) {

				std::unique_lock<std::shared_mutex> lk2;
				if (owner_ != c->receiver)
					lk2 = std::unique_lock(signal_shared_mutex(c->receiver));

				if (c->receiver) {
					size_t count = c->receiver->impl_->connected_sender_connections_
					                .EraseIf([&](auto& sc) {
						                return sc == c;
					                });
					MW_ASSERT_X(count == 1);
				}
			}
			conns.second.Clear();
		}

		for (auto& sender_conn : connected_sender_connections_) {
			auto sender = sender_conn->sender;
			std::unique_lock<std::shared_mutex> lk2;
			if (owner_ != sender)
				lk2 = std::unique_lock(signal_shared_mutex(sender));

			if (!sender_conn || sender_conn->sender != sender) {
				// 也许就在迭代时没有锁的那段间隔, 这个连接就被切断了
				continue;
			}
			sender_conn->receiver = nullptr;
			sender->impl_->connections_manager_.dirty_ = true;
		}
	}

	lk.unlock();

	DeleteChildren();
	SetParent(nullptr);
}

void Object::Impl::ConnectionsManager::ClearDirty() {
	if (dirty_) {
		for (auto& conns : map_)
			conns.second.EraseIf([](auto& c) {
				return !c->receiver;
			});
		dirty_ = false;
	}
}

Object::Disconnecter Object::Impl::ConnectImpl(const Object* sender, const std::type_info& signal_info,
	const Object* receiver, internal::UniqueSlotObject&& slot_obj, ConnectionFlags connection_flags,
	InvokeType invoke_type)
{
	bool has_unique_flag = (connection_flags & ConnectionFlags::kUnique) != ConnectionFlags::kNone;
	bool has_replace_flag = (connection_flags & ConnectionFlags::kReplace) != ConnectionFlags::kNone;

	MW_ASSERT_X(!(has_unique_flag && has_replace_flag));

	std::unique_lock sender_lk(signal_shared_mutex(sender));
	std::unique_lock<std::shared_mutex> receiver_lk;

	if (sender != receiver) {
		receiver_lk = std::unique_lock(signal_shared_mutex(receiver));
	}

	// 如果connection_type是Unique, 表示不重复连接
	// 检测目标Signal中所有Connection的Slot是否有跟当前想连接的Slot重复的
	if (has_unique_flag || has_replace_flag) {
		// 获取当前链接的Signal Connection List
		if (auto res = sender->impl_->connections_manager_.map_.find(signal_info); res != sender->impl_->
			connections_manager_.map_.end()) {
			if (res->first != signal_info) {
				auto errmsg = std::format(
					"Hash conflict between signal '{}' and signal '{}', try to change the name or parameter of one of them",
					res->first.name(), signal_info.name());
				throw std::exception(errmsg.c_str());
			}
			auto res2 = res->second.FindIf([&](auto& c) {
				return c->receiver == receiver && c->slot_obj->Compare(slot_obj.get());
				});
			if (!res2.IsEnd()) {
				if (has_unique_flag) {
					//TODO has_unique_flag暂时啥也不干
				}
				else {
					(*res2)->slot_obj = std::move(slot_obj);
				}
				return {
					[c = *res2, &signal_info, sender] {
						return sender->impl_->DisconnectImpl(signal_info, c);
					}
				};
			}
		}
	}

	auto conn = std::make_shared<Connection>(sender, receiver, std::move(slot_obj), signal_info, connection_flags,
		invoke_type);

	return sender->impl_->AddConnectionWithoutLock(signal_info, std::move(conn));
}

void Object::Impl::Init(Object* parent) {
	SetParent(parent);
}

void Object::Impl::EmitSignalImpl(const type_info& signal_info, const internal::SharedSlotArgsStore& args_store) {
	// 给自身上锁
	std::shared_lock lk{ signal_shared_mutex(owner_)};

	// 找到信号对应的槽连接列表
	auto res = connections_manager_.map_.find(signal_info);
	if (res == connections_manager_.map_.end())
		return;
	const auto& conns = res->second;
	// 遍历连接，触发槽函数
	for (auto& c : conns) {
		MW_ASSERT_X(c->sender == owner_ && c->signal_info == signal_info);

		// 给发送者上锁
		auto receiver = c->receiver;
		std::shared_lock<std::shared_mutex> lk2;
		if (receiver != owner_)
			lk2 = std::shared_lock(signal_shared_mutex(c->receiver));

		if (!c || c->sender != owner_ || c->receiver != receiver) {
			// 也许就在迭代时没有锁的那段间隔, 这个连接就被切断了
			continue;
		}

		// 触发槽函数
		c->receiver->Invoke([receiver = c->receiver, slot_obj = &c->slot_obj, args_store] {
			if (!receiver || !*slot_obj) return;
			(*slot_obj)->Call(receiver, args_store.get());
		}, c->invoke_type);
	}
}

bool Object::Impl::DisconnectImpl(const std::type_info& signal_info, const SharedConnection& connection) {
	if (connection->receiver == nullptr) return false;
	std::scoped_lock lk{ signal_shared_mutex(owner_), signal_shared_mutex(connection->receiver)};
	auto res = connections_manager_.map_.find(signal_info);
	if (res == connections_manager_.map_.end())
		return false;
	res->second.Erase(connection);
	connection->receiver->impl_->connected_sender_connections_.Erase(connection);
	return true;
}

Object::Disconnecter Object::Impl::AddConnectionWithoutLock(const std::type_info& signal_info,
                                                            SharedConnection conn) {
	auto [it, _] = connections_manager_.map_.try_emplace(signal_info);
	conn->receiver->impl_->connected_sender_connections_.PushBack(conn);
	it->second.PushBack(conn);
	connections_manager_.ClearDirty();
	return {
		[this, conn, &signal_info] {
			return DisconnectImpl(signal_info, conn);
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
