#include "win/model/standard_item_model_impl.h"

namespace miniwin {
StandardItemModel::StandardItemModel()
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

std::any* StandardItemModel::user_data(const ModelIndex& index) const
{
    if (auto i = impl_->item(index))
    {
        return &i->user_data;
    }
    return nullptr;
}

void StandardItemModel::set_user_data(const ModelIndex& index, std::any&& data)
{
    auto& i = impl_->GetOrCreateItem(index);
    i.user_data = std::move(data);
}

std::u8string_view StandardItemModel::text(const ModelIndex& index) const
{
    if (auto i = impl_->item(index))
    {
        return i->text;
    }
    return u8"";
}

void StandardItemModel::set_text(const ModelIndex& index, std::u8string_view text)
{
    auto& i = impl_->GetOrCreateItem(index);
    i.text = text;
}

int StandardItemModel::flags(const ModelIndex& index) const
{
    if (auto i = impl_->item(index))
    {
        return i->flags;
    }
    return 0;
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
}
