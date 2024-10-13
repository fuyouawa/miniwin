#include <miniwin/widgets/text.h>
#include <win/core/drawer.h>

namespace miniwin {
Text::Text(Widget* const parent, std::u8string_view label, bool show)
	: AbstractControl{ parent, label, show }
{
}

void Text::PaintBegin() {
    AbstractControl::PaintBegin();
	Drawer::Text(label(), size());
}
}
