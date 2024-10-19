#include "table_view_impl.h"
#include <miniwin/core/imgui_helper.h>

namespace miniwin {
TableView::TableView(Widget* parent, std::u8string_view id)
    : AbstractItemView(parent)
{
    impl_ = std::make_unique<Impl>(this);
    impl_->Init();
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
    auto item_delegate = ItemDelegate();
    auto col_count = model->ColumnCount();
    auto row_count = model->RowCount();

    if (ImGuiHelper::BeginTable(id(), col_count, flags(), size()))
    {
        auto hori_header = HorizontalHeader();
        if (hori_header && hori_header->Visible())
        {
            for (size_t col = 0; col < col_count; ++col)
            {
                auto text = model->HeaderData(col, Orientation::Horizontal, ItemRole::Display).ToString();
                auto flags = model->HeaderData(col, Orientation::Horizontal, ItemRole::Flags).ToInt32();
                ImGuiHelper::TableSetupColumn(text, static_cast<TableColumnFlags>(flags));
            }
            ImGuiHelper::TableNextRow(TableRowFlags::kHeaders);

            for (size_t col = 0; col < col_count; ++col)
            {
                ImGuiHelper::TableSetColumnIndex(col);
                ImGuiHelper::PushID(col);
                hori_header->PaintSection(col);
                ImGuiHelper::PopID();
            }
        }

        auto vert_header = VerticalHeader();
        bool paint_vert_header = vert_header && vert_header->Visible();
        if (paint_vert_header)
            --col_count;

        for (size_t row = 0; row < row_count; ++row)
        {
            ImGuiHelper::TableNextRow();
            if (paint_vert_header)
            {
                vert_header->PaintSection(row);
            }
            for (size_t col = 0; col < col_count; ++col)
            {
                ImGuiHelper::TableSetColumnIndex(col);
                item_delegate->Paint(this, { row, col });
            }
        }

        ImGuiHelper::EndTable();
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
