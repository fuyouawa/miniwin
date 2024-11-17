#include "object_impl.h"

#include "win/tools/debug.h"


namespace miniwin {
ConnectionFlags operator|(ConnectionFlags x, ConnectionFlags y) {
	return static_cast<ConnectionFlags>(static_cast<int>(x) | static_cast<int>(y));
}

ConnectionFlags operator&(ConnectionFlags x, ConnectionFlags y) {
	return static_cast<ConnectionFlags>(static_cast<int>(x) & static_cast<int>(y));
}

Object::Disconnecter::Disconnecter(std::function<bool()>&& func)
	: func_(std::move(func)) {}

bool Object::Disconnecter::Disconnect() const {
	if (func_) {
		return func_();
	}
	return false;
}

Object::Object() {
	impl_ = std::make_unique<Impl>(this);
}

Object::~Object() {
	OnDestroy();
}

SharedObject Object::Parent() const {
	return impl_->parent_;
}


void Object::SetParent(const SharedObject& parent) const {
	impl_->SetParent(parent);
}

String Object::Name() const {
	return impl_->name_;
}

void Object::SetName(const String& name) const {
	impl_->name_ = name;
}

bool Object::Orphaned() const {
	return impl_->orphaned_;
}

FlagsType Object::Flags() const {
	return impl_->flags_;
}

void Object::SetFlags(FlagsType flags) {
	impl_->flags_ = flags;
}

void Object::EnableFlags(FlagsType flags, bool enable) {
	if (enable) {
		impl_->flags_ |= flags;
	}
	else {
		impl_->flags_ &= ~flags;
	}
}

List<SharedObject> Object::Children() const {
	return impl_->GetChildrenWithProcess();
}

bool Object::IsWidget() const {
	return impl_->is_widget_;
}

bool Object::IsLayout() const {
	return impl_->is_layout_;
}

void Object::Invoke(std::function<void()> func, InvokeType invoke_type) const {
	func();
}

void Object::Initialize(const SharedObject& parent) {
	impl_->Init(parent);
}

Object::Disconnecter Object::ConnectImpl(const SharedObject& sender, const std::type_info& signal_info,
                                         const SharedObject& receiver, internal::UniqueSlotObject&& slot_obj, ConnectionFlags connection_flags,
                                         InvokeType invoke_type)
{
	MW_ASSERT_X(receiver);
	MW_ASSERT_X(slot_obj);
	return Impl::ConnectImpl(sender, signal_info, receiver, std::move(slot_obj), connection_flags, invoke_type);
}

void Object::EmitSignalImpl(const std::type_info& signal_info,
                            const internal::SharedSlotArgsStore& args_store) const {
	MW_ASSERT_X(args_store);
	impl_->EmitSignalImpl(signal_info, args_store);
}
}
