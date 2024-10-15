#include "win/widgets/table_view_impl.h"

namespace miniwin {
TableView::TableView(Widget* parent)
    : AbstractItemView(parent)
{
    impl_ = std::make_unique<Impl>(this);
}

TableView::~TableView()
{
}
}
