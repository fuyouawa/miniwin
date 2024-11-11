#include <miniwin/widgets/label.h>

#include <miniwin/core/imgui.h>

namespace miniwin {
Label::Label(Widget* const parent, const String& text)
	: AbstractControl{ parent, text }
{
}

void Label::PaintBegin() {
    AbstractControl::PaintBegin();
	imgui::Text(Text());
}
}
