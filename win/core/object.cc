#include "object_impl.h"

#include "win/tools/debug.h"


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

Object::Object(Object* parent, const String& name)
{
	impl_ = std::make_unique<Impl>(this);
    impl_->name_ = name;
    SetParent(parent);
}

Object::~Object()
{
    OnDestroy();
}

const Object* Object::Parent() const
{
    return impl_->parent_;
}

void Object::SetParent(Object* parent) const
{
    impl_->SetParent(parent);
}

const String& Object::Name() const
{
    return impl_->name_;
}

void Object::SetName(const String& name) const
{
    auto prev = std::move(impl_->name_);
    impl_->name_ = name;
    OnNameChanged(name, prev);
}

FlagsType Object::Flags() const
{
    return impl_->flags_;
}

void Object::SetFlags(FlagsType flags)
{
    impl_->flags_ = flags;
}

void Object::EnableFlags(FlagsType flags, bool enable)
{
	if (enable)
	{
        impl_->flags_ |= flags;
	}
	else
	{
        impl_->flags_ &= ~flags;
	}
}

const List<Object*>& Object::Children() const
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
    MW_ASSERT_X(receiver);
    MW_ASSERT_X(slot_obj);
    return Impl::ConnectImpl(sender, signal_info, receiver, std::move(slot_obj), connection_flags, invoke_type);
}

void Object::EmitSignalImpl(const std::type_info& signal_info,
    const internal::SlotArgsStoreSharedPtr& args_store) const
{
    MW_ASSERT_X(args_store);
    impl_->EmitSignalImpl(signal_info, args_store);
}
}
