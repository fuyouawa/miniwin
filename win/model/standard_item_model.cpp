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

size_t StandardItemModel::row_count() const
{
    return impl_->row_count();
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

size_t StandardItemModel::column_count() const
{
    return impl_->column_count();
}

const std::any& StandardItemModel::data(const ModelIndex& index, ItemRole role) const
{
    static std::any empty;

    auto i = impl_->item(index);
    auto res = i.find(role);
    if (res != i.end())
    {
        return res->second;
    }
    return empty;
}

void StandardItemModel::set_data(const ModelIndex& index, std::any&& data, ItemRole role)
{
    auto i = impl_->GetOrCreateItem(index);
    i[role] = std::move(data);
}

std::u8string_view StandardItemModel::text(const ModelIndex& index) const
{
    auto& d = data(index, ItemRole::Display);
    if (d.has_value())
    {
        assert(d.type() == typeid(std::u8string));
        return std::any_cast<const std::u8string&>(d);
    }
    return u8"";
}

void StandardItemModel::set_text(const ModelIndex& index, std::u8string_view text)
{
    set_data(index, std::u8string(text), ItemRole::Display);
}

int StandardItemModel::flags(const ModelIndex& index) const
{
    auto& d = data(index, ItemRole::Flags);
    if (d.has_value())
    {
        assert(d.type() == typeid(int));
        return std::any_cast<int>(d);
    }
    return 0;
}

void StandardItemModel::set_flags(const ModelIndex& index, int flags)
{
    set_data(index, flags, ItemRole::Flags);
}

std::u8string_view StandardItemModel::header_text(int section, Orientation orientation) const
{
    auto& d = header_data(section, orientation, ItemRole::Display);
    if (d.has_value())
    {
        assert(d.type() == typeid(std::u8string));
        return std::any_cast<const std::u8string&>(d);
    }
    return u8"";
}

void StandardItemModel::set_header_text(int section, Orientation orientation, std::u8string_view text)
{
    set_header_data(section, orientation, std::u8string(text), ItemRole::Display);
}

int StandardItemModel::header_flags(int section, Orientation orientation) const
{
    auto& d = header_data(section, orientation, ItemRole::Display);
    if (d.has_value())
    {
        assert(d.type() == typeid(int));
        return std::any_cast<int>(d);
    }
    return 0;
}

void StandardItemModel::set_header_flags(int section, Orientation orientation, int flags)
{
    set_header_data(section, orientation, flags, ItemRole::Flags);
}

void StandardItemModel::Clear()
{
    impl_->Clear();
}

const std::any& StandardItemModel::header_data(int section, Orientation orientation, ItemRole role) const
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

void StandardItemModel::set_header_data(int section, Orientation orientation, std::any&& data, ItemRole role)
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
