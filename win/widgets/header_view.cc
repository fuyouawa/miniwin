#include "win/widgets/header_view_impl.h"

namespace miniwin {
inline HeaderView::HeaderView(Widget* parent, Orientation orientation)
    : AbstractItemView(parent)
{
    impl_ = std::make_unique<Impl>(this, orientation);
    set_draw_flags(WidgetDrawFlags::kIgnoreDraw);
}
}
