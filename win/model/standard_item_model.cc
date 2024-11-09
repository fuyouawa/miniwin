#include "standard_item_model_impl.h"

#include <string>

#include "win/tools/debug.h"

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

void StandardItemModel::SetData(const ModelIndex& index, const Variant& data, ItemRole role)
{
    auto& i = impl_->GetOrCreateItem(index);
    i[role] = data;
}

String StandardItemModel::Text(const ModelIndex& index) const
{
    auto d = Data(index, ItemRole::Display);
    return d.ToString();
}

void StandardItemModel::SetText(const ModelIndex& index, const String& text)
{
    SetData(index, text, ItemRole::Display);
}

void StandardItemModel::SetRowTexts(size_t row, size_t begin_column, const StringList& texts)
{
    MW_ASSERT_X(begin_column + texts.size() <= ColumnCount());
    size_t i = 0;
    for (auto& t : texts)
    {
        SetText({ row, begin_column + i }, t);
        ++i;
    }
}

void StandardItemModel::SetColumnTexts(size_t begin_row, size_t column, const StringList& texts)
{
    MW_ASSERT_X(begin_row + texts.size() <= RowCount());
    size_t i = 0;
    for (auto& t : texts)
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


Variant StandardItemModel::HeaderData(size_t section, HeaderOrientation orientation, ItemRole role) const
{
    StandardLineItems* items = nullptr;
    switch (orientation)
    {
    case HeaderOrientation::Horizontal:
        items = &impl_->horizontal_header_items_;
        break;
    case HeaderOrientation::Vertical:
        items = &impl_->vertical_header_items_;
        break;
    default:
        MW_ASSERT_X(false);
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

void StandardItemModel::SetHeaderData(size_t section, HeaderOrientation orientation, const Variant& data, ItemRole role)
{
    StandardLineItems* items = nullptr;
    switch (orientation)
    {
    case HeaderOrientation::Horizontal:
        items = &impl_->horizontal_header_items_;
        break;
    case HeaderOrientation::Vertical:
        items = &impl_->vertical_header_items_;
        break;
    default:
        MW_ASSERT_X(false);
        break;
    }
    (*items)[section][role] = data;
}

String StandardItemModel::HeaderText(int section, HeaderOrientation orientation) const
{
    auto d = HeaderData(section, orientation, ItemRole::Display);
    return d.ToString();
}

void StandardItemModel::SetHeaderText(int section, HeaderOrientation orientation, const String& text)
{
    SetHeaderData(section, orientation, text, ItemRole::Display);
}

void StandardItemModel::SetHorizontalHeaderTexts(const StringList& texts)
{
    MW_ASSERT_X(texts.size() <= ColumnCount());
    size_t i = 0;
    for (auto& t : texts)
    {
        SetHeaderText(i, HeaderOrientation::Horizontal, t);
        ++i;
    }
}

void StandardItemModel::SetVerticalHeaderTexts(const StringList& texts)
{
    MW_ASSERT_X(texts.size() <= RowCount());
    size_t i = 0;
    for (auto& t : texts)
    {
        SetHeaderText(i, HeaderOrientation::Vertical, t);
        ++i;
    }
}

int StandardItemModel::HeaderFlags(int section, HeaderOrientation orientation) const
{
    auto d = HeaderData(section, orientation, ItemRole::Flags);
    return d.ToInt32();
}

void StandardItemModel::SetHeaderFlags(int section, HeaderOrientation orientation, int flags)
{
    SetHeaderData(section, orientation, flags, ItemRole::Flags);
}

void StandardItemModel::Clear()
{
    impl_->Clear();
}
}
