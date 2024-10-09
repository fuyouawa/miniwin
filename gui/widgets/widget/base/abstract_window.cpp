#include <fugui/widgets/widget/base/abstract_window.h>

namespace fugui {
AbstractWindow::AbstractWindow(AbstractWindow* const parent, std::u8string_view title, bool show)
	: Widget{ parent, show, WidgetType::kWindow }, title_{ title }
{
}
}