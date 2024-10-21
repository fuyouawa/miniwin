#include <miniwin/widgets/button.h>
#include <miniwin/core/imgui_helper.h>

namespace miniwin {
Button::Button(Widget* const parent, std::u8string_view text)
	: AbstractButton{ parent, text }
{
}

void Button::PaintBegin()
{
    AbstractButton::PaintBegin();
    cur_checked_ = ImGuiHelper::Button(Text(), Size());
}
}
