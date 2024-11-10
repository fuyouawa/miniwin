#include "standard_item_model_impl.h"

#include "win/tools/debug.h"

namespace miniwin {
StandardItemModel::Impl::Impl(StandardItemModel* owner) : owner_(owner), column_count_(0)
{
}

size_t StandardItemModel::Impl::RowCount() const
{
    return items_.size();
}

size_t StandardItemModel::Impl::ColumnCount() const
{
    return column_count_;
}

void StandardItemModel::Impl::SetRowCount(size_t c)
{
    items_.resize(c);
}

void StandardItemModel::Impl::SetColumnCount(size_t c)
{
    // 如果当前要减少列数, 将那些超出列数的行调整到指定列数
    if (c < column_count_)
    {
        for (auto& r : items_)
        {
            if (r.size() > c)
            {
                r.resize(c);
            }
        }
    }
    column_count_ = c;
}

void StandardItemModel::Impl::InsertRows(size_t row, size_t count)
{
    MW_ASSERT_X(row <= RowCount());
    items_.Insert(items_.begin() + row, count, {});

    vertical_header_items_.Insert(vertical_header_items_.begin() + row, count, {});
}

void StandardItemModel::Impl::RemoveRows(size_t row, size_t count)
{
    MW_ASSERT_X(row + count <= RowCount());
    items_.Erase(items_.begin() + row, count);

    vertical_header_items_.Erase(
        vertical_header_items_.begin() + row, count);
}

void StandardItemModel::Impl::InsertColumns(size_t column, size_t count)
{
    MW_ASSERT_X(column <= ColumnCount());
    // 如果是在末尾插入的, 只需要修改column_count_
    if (column != ColumnCount())
    {
        for (auto& r : items_)
        {
            // 如果是在当前行的列数中间插入的, 才需要真正插入
            if (r.size() > column)
            {
                r.Insert(r.begin() + column, count, {});
            }
        }
    }
    horizontal_header_items_.Insert(horizontal_header_items_.begin() + column, count, {});
    column_count_ += count;
}

void StandardItemModel::Impl::RemoveColumns(size_t column, size_t count)
{
    MW_ASSERT_X(column + count <= ColumnCount());
    for (auto& r : items_)
    {
        if (r.size() > column)
        {
            r.Erase(r.begin() + column, r.size() - column);
        }
    }
    horizontal_header_items_.Erase(
        horizontal_header_items_.begin() + column, count);

    column_count_ -= count;
}

StandardItem& StandardItemModel::Impl::Item(const ModelIndex& idx)
{
    static StandardItem empty_item;
    MW_ASSERT_X(idx.valid());
    MW_ASSERT_X(idx.row() < RowCount() && idx.column() < ColumnCount());
    auto& r = items_[idx.row()];
    if (r.size() <= idx.column())
    {
        return empty_item;
    }
    return r[idx.column()];
}

StandardItem& StandardItemModel::Impl::GetOrCreateItem(const ModelIndex& idx)
{
    MW_ASSERT_X(idx.valid());
    MW_ASSERT_X(idx.row() < RowCount() && idx.column() < ColumnCount());
    auto& r = items_[idx.row()];
    if (r.size() <= idx.column())
    {
        r.resize(idx.column() + 1);
    }
    return r[idx.column()];
}

void StandardItemModel::Impl::Clear()
{
    items_.Clear();
}
}
