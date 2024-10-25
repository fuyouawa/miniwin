#include "checkbox_impl.h"

#include <miniwin/core/imgui_helper.h>

namespace miniwin {
CheckBox::CheckBox(Widget* const parent, const String& label)
	: AbstractControl(parent, label)
{
}

void CheckBox::SetChecked(bool b) {
	impl_->checked_sc_.SetControl(b);
}

void CheckBox::PaintBegin() {
	AbstractControl::PaintBegin();
	impl_->PaintBegin();
}
}
