#include <miniwin/widgets/text.h>
#include <miniwin/core/imgui_helper.h>

namespace miniwin {
Text::Text(Widget* const parent, std::u8string_view label)
	: AbstractControl{ parent, label }
{
}

void Text::PaintBegin() {
    AbstractControl::PaintBegin();
	ImGuiHelper::Text(label(), size());
}
}
