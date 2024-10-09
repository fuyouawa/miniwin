#include <fugui/widgets/widget/base/abstract_window.h>

namespace fugui {
AbstractWindow::AbstractWindow(AbstractWindow* const parent, std::u8string_view title, bool show)
	: Widget{ parent, show }, title_{ title }
{
	widget_type_ = WidgetType::kWindow;
}
}