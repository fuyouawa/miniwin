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

const std::any& StandardItemModel::user_data(const ModelIndex& index) const
{
    return impl_->item(index).user_data;
}

void StandardItemModel::set_user_data(const ModelIndex& index, std::any&& data)
{
    auto& i = impl_->GetOrCreateItem(index);
    i.user_data = std::move(data);
}

std::u8string_view StandardItemModel::text(const ModelIndex& index) const
{
    return impl_->item(index).text;
}

void StandardItemModel::set_text(const ModelIndex& index, std::u8string_view text)
{
    auto& i = impl_->GetOrCreateItem(index);
    i.text = text;
}

int StandardItemModel::flags(const ModelIndex& index) const
{
    return impl_->item(index).flags;
}

void StandardItemModel::set_flags(const ModelIndex& index, int flags)
{
    auto& i = impl_->GetOrCreateItem(index);
    i.flags = flags;
}

void StandardItemModel::Clear()
{
    impl_->Clear();
}

const std::any& StandardItemModel::header_data(int section, Orientation orientation, ItemRole role)
{
    //TODO header_data
}

void StandardItemModel::set_header_data(int section, Orientation orientation, ItemRole role, const std::any& data)
{
    //TODO set_header_data
}
}
