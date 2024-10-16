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
    return impl_->Header(Orientation::Horizontal);
}

void TableView::SetHorizontalHeader(HeaderView* header)
{
    impl_->SetHeader(Orientation::Horizontal, header);
}

HeaderView* TableView::VerticalHeader() const
{
    return impl_->Header(Orientation::Vertical);
}

void TableView::SetVerticalHeader(HeaderView* header)
{
    impl_->SetHeader(Orientation::Vertical, header);
}

void TableView::PaintBegin()
{
    AbstractItemView::PaintBegin();
    auto model = Model();
    auto col_count = model->ColumnCount();

    impl_->begin_table_ = ImGuiHelper::BeginTable(id(), col_count, flags(), size());
    if (impl_->begin_table_)
    {
        auto hori_header = HorizontalHeader();
        if (hori_header && hori_header->Visible())
        {
            hori_header->UpdateEarly();
            for (size_t i = 0; i < col_count; ++i)
            {
                auto text = std::any_cast<const std::u8string&>(model->HeaderData(i, Orientation::Horizontal, ItemRole::Display));
                auto flags = std::any_cast<int>(model->HeaderData(i, Orientation::Horizontal, ItemRole::Flags));
                ImGuiHelper::TableSetupColumn(text, static_cast<TableColumnFlags>(flags));
            }
            ImGuiHelper::TableNextRow(TableRowFlags::kHeaders);

            hori_header->PaintBegin();
            for (size_t i = 0; i < col_count; ++i)
            {
                ImGuiHelper::TableSetColumnIndex(i);
                ImGuiHelper::PushID(i);
                hori_header->PaintSection(i);
                ImGuiHelper::PopID();
            }
            hori_header->PaintEnd();
        }
        //TODO 行的绘制
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
