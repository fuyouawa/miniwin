#include "win/core/object_impl.h"

#include <cassert>

#include <format>
#include <mutex>

namespace miniwin {
namespace {
std::mutex signal_mutex_pool[131];
auto& signal_mutex(const Object* obj) {
    return signal_mutex_pool[
        reinterpret_cast<uintptr_t>(obj) %
            (sizeof(signal_mutex_pool) / sizeof(std::mutex))];
}
}   // namespace

Object::Impl::Impl(Object* owner)
    : owner_(owner), connections_manager_()
{
}

Object::Impl::~Impl() {
    std::unique_lock lk{ signal_mutex(owner_) };

    deleting_ = true;
    if (!connections_manager_.map_.empty() || !connected_sender_connections_.empty())
    {
        for (auto& conns : connections_manager_.map_)
        {
            for (auto& c : conns.second)
            {
                std::lock_guard lk2{ signal_mutex(c->receiver) };
                if (c->receiver)
                {
                    size_t count = c->receiver->impl_->connected_sender_connections_
                        .EraseIf([&](auto& sc) { return sc == c; });
                    assert(count == 1);
                }
            }
            conns.second.Clear();
        }

        for (auto& sender_conn : connected_sender_connections_)
        {
            auto sender = sender_conn->sender;
            std::lock_guard lk2{ signal_mutex(sender) };
            if (!sender_conn || sender_conn->sender != sender)
            {
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

void Object::Impl::ConnectionsManager::ClearDirty()
{
    if (dirty_)
    {
        for (auto& conns : map_)
	        conns.second.EraseIf([](auto& c) { return !c->receiver; });
        dirty_ = false;
    }
}

Object::Disconnecter Object::Impl::ConnectImpl(
    const Object* sender,
    const std::type_info& signal_info,
    const Object* receiver,
    internal::SlotObjectPtr&& slot_obj,
    ConnectionFlags connection_flags,
    InvokeType invoke_type)
{
    bool has_unique_flag = (connection_flags & ConnectionFlags::kUnique) != ConnectionFlags::kNone;
    bool has_replace_flag = (connection_flags & ConnectionFlags::kReplace) != ConnectionFlags::kNone;

    assert(!(has_unique_flag && has_replace_flag));

    std::scoped_lock lk{ signal_mutex(sender), signal_mutex(receiver) };

    // 如果connection_type是Unique, 表示不重复连接
    // 检测目标Signal中所有Connection的Slot是否有跟当前想连接的Slot重复的
    if (has_unique_flag || has_replace_flag) {
        // 获取当前链接的Signal Connection List
        if (auto res = sender->impl_->connections_manager_.map_.find(signal_info); res != sender->impl_->connections_manager_.map_.end())
        {
            if (res->first != signal_info)
            {
                auto errmsg = std::format("Hash conflict between signal '{}' and signal '{}', try to change the name or parameter of one of them", res->first.name(), signal_info.name());
                throw std::exception(errmsg.c_str());
            }
            auto res2 = res->second.FindIf([&](auto& c)
                {
                    return c->receiver == receiver && c->slot_obj->Compare(slot_obj.get());
                });
            if (!res2.IsEnd())
            {
                if (has_unique_flag)
                {
                    //TODO has_unique_flag暂时啥也不干
                }
                else
                {
                    (*res2)->slot_obj = std::move(slot_obj);
                }
                return { [c = *res2, &signal_info, sender] { return sender->impl_->DisconnectImpl(signal_info, c); } };
            }
        }
    }

    auto conn = std::make_shared<Connection>(sender, receiver, std::move(slot_obj), signal_info, connection_flags, invoke_type);

    return sender->impl_->AddConnectionWithoutLock(signal_info, std::move(conn));
}

void Object::Impl::EmitSignalImpl(const type_info& type_info, const internal::SlotArgsStoreSharedPtr& args_store)
{
    std::lock_guard lk{ signal_mutex(owner_) };

    auto res = connections_manager_.map_.find(type_info);
    if (res == connections_manager_.map_.end())
        return;
    const auto& conns = res->second;
    for (auto& c : conns)
    {
        assert(c->sender == owner_ && c->signal_info == type_info);

        auto receiver = c->receiver;
        std::lock_guard lk2{ signal_mutex(c->receiver) };

        if (!c || c->sender != owner_ || c->receiver != receiver)
        {
            // 也许就在迭代时没有锁的那段间隔, 这个连接就被切断了
            continue;
        }

        c->receiver->Invoke([receiver = c->receiver, slot_obj = &c->slot_obj, args_store]
            {
                if (!receiver || !*slot_obj) return;
                (*slot_obj)->Call(receiver, args_store.get());
            }, c->invoke_type);
    }
}

bool Object::Impl::DisconnectImpl(const std::type_info& signal_info, const SharedConnection& connection)
{
    if (connection->receiver == nullptr) return false;
    std::scoped_lock lk{ signal_mutex(owner_), signal_mutex(connection->receiver) };
    auto res = connections_manager_.map_.find(signal_info);
    if (res == connections_manager_.map_.end())
        return false;
    res->second.Erase(connection);
    connection->receiver->impl_->connected_sender_connections_.Erase(connection);
    return true;
}

Object::Disconnecter Object::Impl::AddConnectionWithoutLock(const std::type_info& signal_info,
    SharedConnection conn)
{
    auto [it, _] = connections_manager_.map_.try_emplace(signal_info);
    conn->receiver->impl_->connected_sender_connections_.PushBack(conn);
    it->second.PushBack(std::move(conn));
    connections_manager_.ClearDirty();
    return { [this, conn, &signal_info] { return DisconnectImpl(signal_info, conn); } };
}

void Object::Impl::SetParent(Object* parent)
{
    if (owner_ == parent)
        return;
    // 如果parent正在删除中, 就不从parent中移除自己
    //TODO 确保当parent遍历children的时候都不应该进行删除操作
    if (parent_ && !parent_->impl_->deleting_)
    {
        size_t count = parent_->impl_->children_.Erase(owner_);
        assert(count == 1);
    }
    parent_ = parent;

    if (parent_)
    {
        parent_->impl_->children_.PushBack(owner_);
    }
}

void Object::Impl::DeleteChildren()
{
    for (auto c : children_)
    {
        delete c;
    }
    children_.Clear();
}
}
