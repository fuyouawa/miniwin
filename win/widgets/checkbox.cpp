#include <miniwin/widgets/checkbox.h>
#include <miniwin/core/drawer.h>

namespace miniwin {
CheckBox::CheckBox(Widget* const parent, std::u8string_view label)
	: AbstractButton{ parent, label }
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
