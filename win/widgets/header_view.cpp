#include <miniwin/widgets/header_view.h>

namespace miniwin {
HeaderView::HeaderView(Widget* parent)
    : AbstractItemView(parent)
{
    set_widget_flags(WidgetFlags::kIgnoreDraw);
}
}
