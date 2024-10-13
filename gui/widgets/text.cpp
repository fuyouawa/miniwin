#include <fugui/widgets/text.h>
#include <gui/core/drawer.h>

namespace fugui {
Text::Text(Widget* const parent, std::u8string_view label, bool show)
	: AbstractControl{ parent, label, show }
{
}

void Text::PaintBegin() {
    AbstractControl::PaintBegin();
	Drawer::Text(label(), size());
}
}
