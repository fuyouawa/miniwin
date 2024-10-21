#include <miniwin/widgets/label.h>
#include <miniwin/core/imgui_helper.h>

namespace miniwin {
Label::Label(Widget* const parent, std::u8string_view label)
	: AbstractControl{ parent, label }
{
}

void Label::PaintBegin() {
    AbstractControl::PaintBegin();
	ImGuiHelper::Text(label(), size());
}
}
