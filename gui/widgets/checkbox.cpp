#include <fugui/widgets/checkbox.h>
#include <gui/core/drawer.h>

namespace fugui {
CheckBox::CheckBox(Widget* const parent, std::u8string_view label, bool show)
	: AbstractButton{ parent, label, show }
{
}

void CheckBox::set_checked(bool b) {
    cur_checked_ = b;
}

void CheckBox::PaintBegin() {
    AbstractButton::PaintBegin();
	Drawer::CheckBox(label(), &cur_checked_, size());
}
}
