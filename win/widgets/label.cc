#include <miniwin/widgets/label.h>
#include <miniwin/core/imgui_helper.h>

namespace miniwin {
Label::Label(Widget* const parent, std::u8string_view text)
	: AbstractControl{ parent, text }
{
}

void Label::PaintBegin() {
    AbstractControl::PaintBegin();
	ImGuiHelper::Text(Text(), Size());
}
}
