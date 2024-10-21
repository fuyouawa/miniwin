#include "tableview_impl.h"

#include <miniwin/core/imgui_helper.h>

#include <cassert>

#include <miniwin/delegate/base/abstract_item_delegate.h>

namespace miniwin {
TableView::TableView(Widget* parent, std::u8string_view id)
    : AbstractItemView(parent)
{
    impl_ = std::make_unique<Impl>(this);
    impl_->id_ = id;
    impl_->Init();
    set_flags(TableFlags::kBorders);
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
    auto m = Model();
    auto col_count = m->ColumnCount();
    auto row_count = m->RowCount();

    if (ImGuiHelper::BeginTable(id(), col_count, flags(), size()))
    {
        auto hori = HorizontalHeader();
        if (hori && hori->Visible())
        {
            for (size_t col = 0; col < col_count; ++col)
            {
                auto text = m->HeaderData(col, Orientation::Horizontal, ItemRole::Display).ToString();
                auto flags = m->HeaderData(col, Orientation::Horizontal, ItemRole::Flags).ToInt32();
                ImGuiHelper::TableSetupColumn(text, static_cast<TableColumnFlags>(flags));
            }
            ImGuiHelper::TableNextRow(TableRowFlags::kHeaders);

            for (size_t col = 0; col < col_count; ++col)
            {
                ImGuiHelper::TableSetColumnIndex(col);
                ImGuiHelper::PushID(col);
                hori->PaintSection(col);
                ImGuiHelper::PopID();
            }
        }

        auto vert = VerticalHeader();
        bool show_vert = vert && vert->Visible();
        if (show_vert)
            --col_count;

        auto d = ItemDelegate();
        for (size_t row = 0; row < row_count; ++row)
        {
            ImGuiHelper::TableNextRow();
            if (show_vert)
            {
                ImGuiHelper::PushID(row);
                vert->PaintSection(row);
                ImGuiHelper::PopID();
            }
            if (d)
            {
                for (size_t col = 0; col < col_count; ++col)
                {
                    ImGuiHelper::TableSetColumnIndex(col);
                    ImGuiHelper::PushID(row * 10 + col);
                    d->Paint(this, { row, col });
                    ImGuiHelper::PopID();
                }
            }
        }

        ImGuiHelper::EndTable();
    }
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

void TableView::SetModel(AbstractItemModel* model)
{
    AbstractItemView::SetModel(model);
    for (auto& header : impl_->headers_)
    {
        auto h = header.second;
        if (h)
        {
            auto m = h->Model();
            if (!m || m == Model())
            {
                h->SetModel(model);
            }
        }
    }
}
}
