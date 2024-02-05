#include <mvcgui/widgets/widget/base/abstract_window.h>

namespace mvcgui {
AbstractWindow::AbstractWindow(AbstractWindow* const parent, std::u8string_view title, bool show)
	: Widget{ parent, show }, title_{ title }
{
	widget_type_ = Type::kWindow;
	id_ = u8"Window: " + title_;
}
}