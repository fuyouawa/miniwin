#include <fugui/widgets/widget/checkbox.h>
#include <fugui/tools/algorithm.h>
#include <fugui/core/drawer.h>

namespace fugui {
CheckBox::CheckBox(Widget* const parent, std::u8string_view label, bool show)
	: AbstractButton{ parent, label, show }
{
}

void CheckBox::OnItemShowablePaintBegin() {
	Drawer::CheckBox(label_, &cur_checked_, size_);
}
}