#include <fugui/widgets/widget/button.h>

#include <gui/core/drawer.h>

namespace fugui {
Button::Button(Widget* const parent, std::u8string_view label, bool show)
	: AbstractButton{ parent, label, show }
{
}
void Button::OnItemShowablePaintBegin() {
	cur_checked_ = Drawer::Button(label_, size());
}
}