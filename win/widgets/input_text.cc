#include <miniwin/widgets/input_text.h>
#include <miniwin/core/drawer.h>

namespace miniwin {
InputText::InputText(Widget* const parent, std::u8string_view label, std::u8string_view initial_text)
	: AbstractControl{ parent, label }
{
    set_text(initial_text);
}

void InputText::set_text(std::u8string_view text)
{
    text_ = text;
}

std::u8string_view InputText::text() const
{
    return text_;
}

void InputText::PaintBegin() {
    AbstractControl::PaintBegin();
	Drawer::InputText(label(), &text_, flags(), size());
}
}
