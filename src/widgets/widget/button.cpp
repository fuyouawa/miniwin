#include <fugui/widgets/widget/button.h>
#include <fugui/core/drawer.h>
#include <fugui/tools/algorithm.h>

namespace fugui {
Button::Button(Widget* const parent, std::u8string_view label, bool show)
	: AbstractButton{ parent, label, show }
{
}
void Button::OnItemShowablePaintBegin() {
	cur_checked_ = Drawer::Button(label_, size_);
}
}