#include "checkbox_impl.h"

#include <miniwin/core/imgui.h>

namespace miniwin {
CheckBox::CheckBox(Widget* const parent, const String& label)
	: AbstractControl(parent, label)
{
	impl_ = std::make_unique<Impl>(this);
}

void CheckBox::SetChecked(bool b) {
	impl_->checked_sc_.SetControl(b);
}

void CheckBox::PaintBegin() {
	AbstractControl::PaintBegin();
	impl_->PaintBegin();
}

void CheckBox::PaintEnd() {
	AbstractControl::PaintEnd();
}
}
