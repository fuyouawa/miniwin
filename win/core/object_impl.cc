#include "win/core/object_impl.h"

#include <format>
#include <mutex>
#include <shared_mutex>

#include "win/tools/debug.h"

namespace miniwin {
// namespace {
// std::mutex signal_mutex_pool[131];
//
// auto& signal_mutex(const Object* obj) {
// 	return signal_mutex_pool[
// 		reinterpret_cast<uintptr_t>(obj) %
// 		(sizeof(signal_mutex_pool) / sizeof(std::mutex))];
// }
//
// } // namespace

Object::Impl::Impl(Object* owner)
	: owner_(owner), connections_manager_() {}

Object::Impl::~Impl() {
	deleting_ = true;

	for (auto& sender_conn : connected_sender_connections_) {
		auto sc = sender_conn.lock();
		if (!sc) continue;
		MW_ASSERT(sc->sender.lock(), "The connection has not failed, but the sender has been destructed?");
		MW_ASSERT_X(sc->receiver.lock().get() == owner_);
		sc->receiver.reset();
	}

	DeleteChildren();
	SetParent(nullptr);
}

void Object::Impl::ConnectionsManager::ClearDirty() {
	if (dirty_) {
		for (auto& conns : map_) {
			std::lock_guard lk(conns.second.mutex_);
			conns.second.EraseIf([](const SharedConnection& c) {
				return !c->receiver.lock();
				});
		}
		dirty_ = false;
	}
}

Object::Disconnecter Object::Impl::ConnectImpl(
	const SharedObject& sender,
	const std::type_info& signal_info,
	const SharedObject& receiver,
	internal::UniqueSlotObject&& slot_obj,
	ConnectionFlags connection_flags,
	InvokeType invoke_type)
{
	bool has_unique_flag = (connection_flags & ConnectionFlags::kUnique) != ConnectionFlags::kNone;
	bool has_replace_flag = (connection_flags & ConnectionFlags::kReplace) != ConnectionFlags::kNone;

	MW_ASSERT_X(!(has_unique_flag && has_replace_flag));

	// 如果connection_type是Unique, 表示不重复连接
	// 检测目标Signal中所有Connection的Slot是否有跟当前想连接的Slot重复的
	if (has_unique_flag || has_replace_flag) {
		std::unique_lock lk(sender->impl_->signal_mutex_);
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

			auto conn = sender_conns->second.FindIf([receiver, &slot_obj](const SharedConnection& c) {
				return c->receiver.lock() == receiver && c->slot_obj->Compare(slot_obj.get());
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

void Object::Impl::Init(const SharedObject& parent) {
	SetParent(parent);
}

void Object::Impl::EmitSignalImpl(const type_info& signal_info, const internal::SharedSlotArgsStore& args_store) {
	std::unique_lock lk(signal_mutex_);						// 给自身上锁

	auto conns = connections_manager_.map_.find(signal_info);	// 找到信号对应的槽连接列表
	if (conns == connections_manager_.map_.end())
		return;
	std::lock_guard lk2(conns->second.mutex_);				// 给信号对应的连接列表上锁
	lk.unlock();												// 解锁自身，因为接下来要遍历触发槽函数了，防止死锁

	for (auto& c : conns->second) {								// 遍历连接，触发槽函数
		auto sender = c->sender.lock();
		auto receiver = c->receiver.lock();
		MW_ASSERT_X(sender && receiver && sender.get() == owner_ && c->signal_info == signal_info);

		// 触发槽函数
		receiver->Invoke([conn = std::weak_ptr(c), args_store] {
			auto c = conn.lock();
			if (!c) return;
			auto r = c->receiver.lock();
			if (!r || !c->slot_obj) return;
			c->slot_obj->Call(r, args_store);
		}, c->invoke_type);
	}
}

bool Object::Impl::DisconnectImpl(const SharedConnection& connection) {
	MW_ASSERT_X(connection->sender.lock().get() == owner_);

	auto r = connection->receiver.lock();
	if (!r) return false;

	std::lock_guard lk(signal_mutex_);			// 给自身上锁
	std::unique_lock<std::mutex> lk2;				// 给接收者上锁，由于可能发送者和接收者是同一个对象，所以需要判断
	if (r.get() != owner_) {
		lk2 = std::unique_lock(r->impl_->signal_mutex_);
	}

	auto conns = connections_manager_.map_.find(connection->signal_info);
	if (conns == connections_manager_.map_.end())
		return false;

	r->impl_->connected_sender_connections_.EraseIf([&connection](const WeakConnection& c) { return c.lock() == connection; });

	std::lock_guard lk3(conns->second.mutex_);	// 给信号对应的连接列表上锁
	conns->second.Erase(connection);

	return true;
}

Object::Disconnecter Object::Impl::AddConnection(SharedConnection&& connection) {
	MW_ASSERT_X(connection->sender.lock().get() == owner_);

	auto r = connection->receiver.lock();
	if (!r) return {};

	std::lock_guard lk(signal_mutex_);			// 给自身上锁
	std::unique_lock<std::mutex> lk2;				// 给接收者上锁，由于可能发送者和接收者是同一个对象，所以需要判断
	if (r.get() != owner_) {
		lk2 = std::unique_lock(r->impl_->signal_mutex_);
	}

	auto [conns, _] = connections_manager_.map_.try_emplace(connection->signal_info);
	r->impl_->connected_sender_connections_.EmplaceBack(connection);		// 把连接加入接收者的发送者连接列表里面

	std::unique_lock lk3(conns->second.mutex_);	// 给信号对应的连接列表上锁
	conns->second.EmplaceBack(connection);		// 把连接对象加入连接列表
	lk3.unlock();									// 解锁连接列表，因为接下来要调用ClearDirty了，里面也会有锁

	connections_manager_.ClearDirty();				// 清理断开的或者无效的连接

	return {
		[this, c = std::move(connection)] {
			return DisconnectImpl(c);
		}
	};
}

void Object::Impl::SetParent(const SharedObject& parent) {
	auto prev_parent = parent_;
	if (owner_ == parent.get() || prev_parent == parent)
		return;

	// 如果parent正在删除中, 就不处理
	if (prev_parent && !prev_parent->impl_->deleting_) {
		auto c = prev_parent->impl_->children_.FindIf([owner = owner_](const SharedObject& o) {
			return o.get() == owner;
		});
		// 如果没在原父级的子列表中找到自己，说明只是加入了父级的pending_addition_children_，但是父级还没处理
		if (c.IsEnd()) {
			// 从原父级的添加队列中删除自己
			auto s = prev_parent->impl_->pending_addition_children_.Erase(owner_->shared_from_this());
			MW_ASSERT_X(s > 0);
		}
		else {
			prev_parent->impl_->dirty_ = true;
			c->reset();
		}
	}

	if (parent) {
		parent->impl_->pending_addition_children_.PushBack(owner_->shared_from_this());
	}
	parent_ = parent;
}

List<SharedObject> Object::Impl::GetChildrenWithProcess() {
	// 处理移除的子物体
	if (dirty_) {
		auto remove_count = children_.EraseIf([](const SharedObject& o) {
			return o->impl_->orphaned_;
		});
		MW_ASSERT_X(remove_count > 0);
		dirty_ = false;
	}

	// 处理添加的子物体
	for (auto& c : pending_addition_children_) {
		children_.EmplaceBack(c);
	}
	pending_addition_children_.Clear();

	return children_;
}

void Object::Impl::DeleteChildren() {
	children_.Clear();
}
}
