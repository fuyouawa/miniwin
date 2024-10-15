#include "win/widgets/table_view_impl.h"
#include <miniwin/core/drawer.h>

namespace miniwin {
TableView::TableView(Widget* parent, std::u8string_view id)
    : AbstractItemView(parent)
{
    impl_ = std::make_unique<Impl>(this);
}

TableView::~TableView()
{
}

HeaderView* TableView::horizontal_header() const
{
    return impl_->horizontal_header;
}

void TableView::set_horizontal_header(HeaderView* header_view)
{
    impl_->horizontal_header = header_view;
}

void TableView::PaintBegin()
{
    AbstractItemView::PaintBegin();
    impl_->begin_table_ = Drawer::BeginTable(id(), model()->column_count(), flags(), size());
    if (impl_->begin_table_)
    {
        
    }
}

void TableView::PaintEnd()
{
    AbstractItemView::PaintEnd();
}

std::u8string_view TableView::id() const
{
    return impl_->id_;
}

void TableView::set_id(std::u8string_view id)
{
    impl_->id_ = id;
}
}
