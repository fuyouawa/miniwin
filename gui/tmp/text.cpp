#include <fugui/widgets/widget/text.h>
#include <gui/core/drawer.h>

namespace fugui {
Text::Text(Widget* const parent, std::u8string_view label, bool show)
	: AbstractMinimumControl{ parent, label, show }
{
}

void Text::OnItemShowablePaintBegin()
{
	Drawer::Text(label_, size());
}
}