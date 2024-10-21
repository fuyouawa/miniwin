#include <miniwin/widgets/checkbox.h>
#include <miniwin/core/imgui_helper.h>

namespace miniwin {
CheckBox::CheckBox(Widget* const parent, std::u8string_view label)
	: AbstractButton{ parent, label }
{
}

void CheckBox::SetChecked(bool b) {
    cur_checked_ = b;
}

void CheckBox::PaintBegin() {
    AbstractButton::PaintBegin();
	ImGuiHelper::CheckBox(Text(), &cur_checked_, Size());
}
}
