#include <miniwin/widgets/checkbox.h>

#include <miniwin/core/imgui.h>
#include <miniwin/tools/scope_variable.h>

#include "win/tools/debug.h"

namespace miniwin {
class CheckBox::Impl {
public:
	Impl(CheckBox* owner) : owner_(owner) {}

	Vector2D CalcSize() const {
		return imgui::CalcTextSize(owner_->Text());
	}

	CheckBox* owner_;
	ScopeCondition checked_sc_{false};
	ScopeVariable<Vector2D> size_sc_;
};

CheckBox::CheckBox() {
	impl_ = std::make_unique<Impl>(this);
}

CheckBox::~CheckBox() = default;

void CheckBox::SetChecked(bool b) {
	impl_->checked_sc_.SetControl(b);
}

String CheckBox::Text() const {
	return Name();
}

void CheckBox::SetText(const String& text) {
	SetName(text);
}

Vector2D CheckBox::Size() const {
	//TODO CheckBox::Size
	return {};
}

void CheckBox::SetSize(const Vector2D& size) {
	//TODO CheckBox::SetSize
}

void CheckBox::PaintBegin(size_t index) {
	AbstractControl::PaintBegin(index);

	impl_->checked_sc_.Enter();

	bool c = impl_->checked_sc_.cur_value();
	imgui::CheckBox(Text(), &c);

	// 如果选中有改变，发送OnToggled信号，传入选中bool
	if (c != impl_->checked_sc_.cur_value() || impl_->checked_sc_.HasChange()) {
		impl_->checked_sc_.SetValueDirectly(c);
		OnToggled(c);
	}
}

void CheckBox::PaintEnd(size_t index) {
	impl_->checked_sc_.Exit();
	AbstractControl::PaintEnd(index);
}
}
