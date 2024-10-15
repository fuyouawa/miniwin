#include <cassert>
#include "win/core/object_impl.h"

namespace miniwin {
ConnectionFlags operator|(ConnectionFlags x, ConnectionFlags y)
{
    return static_cast<ConnectionFlags>(static_cast<int>(x) | static_cast<int>(y));
}

ConnectionFlags operator&(ConnectionFlags x, ConnectionFlags y)
{
    return static_cast<ConnectionFlags>(static_cast<int>(x) & static_cast<int>(y));
}

Object::Disconnecter::Disconnecter(std::function<bool()>&& func)
    : func_(std::move(func))
{
}

bool Object::Disconnecter::Disconnect() const
{
    if (func_)
    {
        return func_();
    }
    return false;
}

Object::Object(Object* parent, std::u8string_view name, ObjectType object_type)
{
	impl_ = std::make_unique<Impl>(this);
    impl_->name_ = name;
    impl_->object_type_ = object_type;
    set_parent(parent);
}

Object::~Object()
{
    OnDestroy();
}

const Object* Object::parent() const
{
    return impl_->parent_;
}

void Object::set_parent(Object* parent) const
{
    impl_->set_parent(parent);
}

std::u8string_view Object::name() const
{
    return impl_->name_;
}

void Object::set_name(std::u8string_view name) const
{
    impl_->name_ = name;
}

ObjectType Object::object_type() const
{
    return impl_->object_type_;
}

int Object::flags() const
{
    return impl_->flags_;
}

void Object::set_flags(int flags)
{
    impl_->flags_ = flags;
}

const std::vector<Object*>& Object::children() const
{
    return impl_->children_;
}

void Object::Invoke(std::function<void()>&& func, InvokeType invoke_type) const
{
    func();
}

Object::Disconnecter Object::ConnectImpl(
    const Object* sender,
    const std::type_info& signal_info,
    const Object* receiver,
    internal::SlotObjectPtr&& slot_obj,
    ConnectionFlags connection_flags,
    InvokeType invoke_type)
{
    assert(receiver);
    assert(slot_obj);
    return Impl::ConnectImpl(sender, signal_info, receiver, std::move(slot_obj), connection_flags, invoke_type);
}

void Object::EmitSignalImpl(const std::type_info& signal_info,
    const internal::SlotArgsStoreSharedPtr& args_store) const
{
    assert(args_store);
    impl_->EmitSignalImpl(signal_info, args_store);
}
}
