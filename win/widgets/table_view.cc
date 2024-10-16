#include "win/widgets/table_view_impl.h"
#include <miniwin/core/imgui_helper.h>

namespace miniwin {
TableView::TableView(Widget* parent, std::u8string_view id)
    : AbstractItemView(parent)
{
    impl_ = std::make_unique<Impl>(this);
}

TableView::~TableView()
{
}

HeaderView* TableView::HorizontalHeader() const
{
    return impl_->horizontal_header;
}

void TableView::SetHorizontalHeader(HeaderView* header_view)
{
    impl_->horizontal_header = header_view;
}

void TableView::PaintBegin()
{
    AbstractItemView::PaintBegin();
    auto model = Model();
    impl_->begin_table_ = ImGuiHelper::BeginTable(id(), model->ColumnCount(), flags(), size());
    if (impl_->begin_table_)
    {
        for (size_t i = 0; i < model->ColumnCount(); ++i)
        {
            auto text = std::any_cast<const std::u8string&>(model->HeaderData(i, Orientation::Horizontal, ItemRole::Display));
            auto flags = std::any_cast<int>(model->HeaderData(i, Orientation::Horizontal, ItemRole::Flags));
            ImGuiHelper::TableSetupColumn(text, static_cast<TableColumnFlags>(flags));
        }
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

TableFlags TableView::flags() const
{
    return impl_->flags_;
}

void TableView::set_flags(TableFlags flags)
{
    impl_->flags_ = flags;
}
}
