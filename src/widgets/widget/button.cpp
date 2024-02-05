#include <mvcgui/widgets/widget/button.h>
#include <mvcgui/core/drawer.h>
#include <mvcgui/tools/algorithm.h>

namespace mvcgui {
Button::Button(Widget* const parent, std::u8string_view label, bool show)
	: AbstractButton{ parent, label, show }
{
}
void Button::OnItemShowablePaintBegin() {
	cur_checked_ = Drawer::Button(label_, size_);
}
}