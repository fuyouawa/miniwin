#include <mvcgui/widgets/widget/text.h>
#include <mvcgui/core/drawer.h>
#include <mvcgui/tools/algorithm.h>

namespace mvcgui {
Text::Text(Widget* const parent, std::u8string_view label, bool show)
	: AbstractMinimumControl{ parent, label, show }
{
}

void Text::OnItemShowablePaintBegin()
{
	Drawer::Text(label_, size_);
}
}