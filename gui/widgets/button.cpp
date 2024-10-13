#include <fugui/widgets/button.h>

#include <gui/core/drawer.h>

namespace fugui {
Button::Button(Widget* const parent, std::u8string_view label, bool show)
	: AbstractButton{ parent, label, show }
{
}

void Button::PaintBegin()
{
    AbstractButton::PaintBegin();
    cur_checked_ = Drawer::Button(label(), size());
}
}
