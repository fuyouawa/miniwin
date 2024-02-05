#include <mvcgui/widgets/widget/checkbox.h>
#include <mvcgui/tools/algorithm.h>
#include <mvcgui/core/drawer.h>

namespace mvcgui {
CheckBox::CheckBox(Widget* const parent, std::u8string_view label, bool show)
	: AbstractButton{ parent, label, show }
{
}

void CheckBox::OnItemShowablePaintBegin() {
	Drawer::CheckBox(label_, &cur_checked_, size_);
}
}