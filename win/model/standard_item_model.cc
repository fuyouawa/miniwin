#include <cassert>
#include <string>

#include "win/model/standard_item_model_impl.h"

namespace miniwin {
StandardItemModel::StandardItemModel(Object* parent)
    : AbstractItemModel(parent)
{
    impl_ = std::make_unique<Impl>(this);
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

const std::any& StandardItemModel::Data(const ModelIndex& index, ItemRole role) const
{
    static std::any empty;

    auto i = impl_->Item(index);
    auto res = i.find(role);
    if (res != i.end())
    {
        return res->second;
    }
    return empty;
}

void StandardItemModel::SetData(const ModelIndex& index, std::any&& data, ItemRole role)
{
    auto i = impl_->GetOrCreateItem(index);
    i[role] = std::move(data);
}

std::u8string_view StandardItemModel::Text(const ModelIndex& index) const
{
    auto& d = Data(index, ItemRole::Display);
    if (d.has_value())
    {
        assert(d.type() == typeid(std::u8string));
        return std::any_cast<const std::u8string&>(d);
    }
    return u8"";
}

void StandardItemModel::SetText(const ModelIndex& index, std::u8string_view text)
{
    SetData(index, std::u8string(text), ItemRole::Display);
}

int StandardItemModel::Flags(const ModelIndex& index) const
{
    auto& d = Data(index, ItemRole::Flags);
    if (d.has_value())
    {
        assert(d.type() == typeid(int));
        return std::any_cast<int>(d);
    }
    return 0;
}

void StandardItemModel::SetFlags(const ModelIndex& index, int flags)
{
    SetData(index, flags, ItemRole::Flags);
}

std::u8string_view StandardItemModel::HeaderText(int section, Orientation orientation) const
{
    auto& d = HeaderData(section, orientation, ItemRole::Display);
    if (d.has_value())
    {
        assert(d.type() == typeid(std::u8string));
        return std::any_cast<const std::u8string&>(d);
    }
    return u8"";
}

void StandardItemModel::SetHeaderText(int section, Orientation orientation, std::u8string_view text)
{
    SetHeaderData(section, orientation, std::u8string(text), ItemRole::Display);
}

int StandardItemModel::HeaderFlags(int section, Orientation orientation) const
{
    auto& d = HeaderData(section, orientation, ItemRole::Display);
    if (d.has_value())
    {
        assert(d.type() == typeid(int));
        return std::any_cast<int>(d);
    }
    return 0;
}

void StandardItemModel::SetHeaderFlags(int section, Orientation orientation, int flags)
{
    SetHeaderData(section, orientation, flags, ItemRole::Flags);
}

void StandardItemModel::Clear()
{
    impl_->Clear();
}

const std::any& StandardItemModel::HeaderData(int section, Orientation orientation, ItemRole role) const
{
    static std::any empty;
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
    return empty;
}

void StandardItemModel::SetHeaderData(int section, Orientation orientation, std::any&& data, ItemRole role)
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
}
