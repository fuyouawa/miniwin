#include <miniwin/widgets/text.h>
#include <miniwin/core/drawer.h>

namespace miniwin {
Text::Text(Widget* const parent, std::u8string_view label)
	: AbstractControl{ parent, label }
{
}

void Text::PaintBegin() {
    AbstractControl::PaintBegin();
	Drawer::Text(label(), size());
}
}
