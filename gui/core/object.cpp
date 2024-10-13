#include <cassert>
#include "gui/core/object_impl.h"

namespace fugui {
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

Object::Object(Object* parent, std::u8string_view name)
{
	impl_ = std::make_unique<Impl>(this);
    impl_->name_ = name;
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

int Object::flags() const
{
    return impl_->flags_;
}

void Object::set_flags(int flags)
{
    impl_->flags_ = flags;
}

void Object::set_flags_active(int flags, bool b)
{
    if (b) {
        impl_->flags_ |= flags;
    }
    else {
        impl_->flags_ &= (~flags);
    }
}

const std::vector<Object*>& Object::children() const
{
    return impl_->children_;
}

void Object::Invoke(std::function<void()>&& func, InvokeType invoke_type) const
{
    func();
}

Object::Disconnecter Object::ConnectImpl(const std::type_info& signal_info,
                                         const Object* receiver,
                                         internal::SlotObjectPtr&& slot_obj,
                                         ConnectionFlags connection_flags,
                                         InvokeType invoke_type) const
{
    assert(receiver);
    assert(slot_obj);
    return impl_->ConnectImpl(signal_info, receiver, std::move(slot_obj), connection_flags, invoke_type);
}

void Object::EmitSignalImpl(const std::type_info& signal_info,
    const internal::SlotArgsStoreSharedPtr& args_store) const
{
    assert(args_store);
    impl_->EmitSignalImpl(signal_info, args_store);
}
}
