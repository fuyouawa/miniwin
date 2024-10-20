#include <cassert>
#include <string>

#include "win/model/standard_item_model_impl.h"

namespace miniwin {
StandardItemModel::StandardItemModel(Object* parent)
    : AbstractItemModel(parent)
{
    impl_ = std::make_unique<Impl>(this);
}

StandardItemModel::~StandardItemModel()
{
}

void StandardItemModel::InsertRows(size_t row, size_t count)
{
    impl_->InsertRows(row, count);
    OnRowsInserted(row, count);
}

void StandardItemModel::RemoveRows(size_t row, size_t count)
{
    impl_->RemoveRows(row, count);
    OnRowsRemoved(row, count);
}

size_t StandardItemModel::RowCount() const
{
    return impl_->RowCount();
}

void StandardItemModel::InsertColumns(size_t column, size_t count)
{
    impl_->InsertColumns(column, count);
    OnColumnsInserted(column, count);
}

void StandardItemModel::RemoveColumns(size_t column, size_t count)
{
    impl_->RemoveColumns(column, count);
    OnColumnsRemoved(column, count);
}

size_t StandardItemModel::ColumnCount() const
{
    return impl_->ColumnCount();
}

Variant StandardItemModel::Data(const ModelIndex& index, ItemRole role) const
{
    auto& i = impl_->Item(index);
    auto res = i.find(role);
    if (res != i.end())
    {
        return res->second;
    }
    return {};
}

void StandardItemModel::SetData(const ModelIndex& index, Variant&& data, ItemRole role)
{
    auto& i = impl_->GetOrCreateItem(index);
    i[role] = std::move(data);
}

std::u8string_view StandardItemModel::Text(const ModelIndex& index) const
{
    auto d = Data(index, ItemRole::Display);
    return d.ToString();
}

void StandardItemModel::SetText(const ModelIndex& index, std::u8string_view text)
{
    SetData(index, text, ItemRole::Display);
}

void StandardItemModel::SetRowTexts(size_t row, size_t begin_column, std::initializer_list<std::u8string_view> texts)
{
    assert(begin_column + texts.size() <= ColumnCount());
    size_t i = 0;
    for (auto t : texts)
    {
        SetText({ row, begin_column + i }, t);
        ++i;
    }
}

void StandardItemModel::SetColumnTexts(size_t begin_row, size_t column, std::initializer_list<std::u8string_view> texts)
{
    assert(begin_row + texts.size() <= RowCount());
    size_t i = 0;
    for (auto t : texts)
    {
        SetText({ begin_row + i, column }, t);
        ++i;
    }
}

int StandardItemModel::Flags(const ModelIndex& index) const
{
    auto d = Data(index, ItemRole::Flags);
    return d.ToInt32();
}

void StandardItemModel::SetFlags(const ModelIndex& index, int flags)
{
    SetData(index, flags, ItemRole::Flags);
}


Variant StandardItemModel::HeaderData(size_t section, Orientation orientation, ItemRole role) const
{
    StandardLineItems* items = nullptr;
    switch (orientation)
    {
    case Orientation::Horizontal:
        items = &impl_->horizontal_header_items_;
        break;
    case Orientation::Vertical:
        items = &impl_->vertical_header_items_;
        break;
    default:
        assert(false);
        break;
    }

    auto& i = (*items)[section];
    auto res = i.find(role);
    if (res != i.end())
    {
        return res->second;
    }
    return {};
}

void StandardItemModel::SetHeaderData(size_t section, Orientation orientation, Variant&& data, ItemRole role)
{
    StandardLineItems* items = nullptr;
    switch (orientation)
    {
    case Orientation::Horizontal:
        items = &impl_->horizontal_header_items_;
        break;
    case Orientation::Vertical:
        items = &impl_->vertical_header_items_;
        break;
    default:
        assert(false);
        break;
    }
    (*items)[section][role] = std::move(data);
}

std::u8string_view StandardItemModel::HeaderText(int section, Orientation orientation) const
{
    auto d = HeaderData(section, orientation, ItemRole::Display);
    return d.ToString();
}

void StandardItemModel::SetHeaderText(int section, Orientation orientation, std::u8string_view text)
{
    SetHeaderData(section, orientation, text, ItemRole::Display);
}

void StandardItemModel::SetHorizontalHeaderTexts(std::initializer_list<std::u8string_view> texts)
{
    assert(texts.size() <= ColumnCount());
    size_t i = 0;
    for (auto t : texts)
    {
        SetHeaderText(i, Orientation::Horizontal, t);
        ++i;
    }
}

void StandardItemModel::SetVerticalHeaderTexts(std::initializer_list<std::u8string_view> texts)
{
    assert(texts.size() <= RowCount());
    size_t i = 0;
    for (auto t : texts)
    {
        SetHeaderText(i, Orientation::Vertical, t);
        ++i;
    }
}

int StandardItemModel::HeaderFlags(int section, Orientation orientation) const
{
    auto d = HeaderData(section, orientation, ItemRole::Flags);
    return d.ToInt32();
}

void StandardItemModel::SetHeaderFlags(int section, Orientation orientation, int flags)
{
    SetHeaderData(section, orientation, flags, ItemRole::Flags);
}

void StandardItemModel::Clear()
{
    impl_->Clear();
}
}
