#include "win/model/standard_item_model_impl.h"

#include <cassert>

namespace miniwin {
StandardItemModel::Impl::Impl(StandardItemModel* owner)
    : owner_(owner), column_count_(0)
{
}

size_t StandardItemModel::Impl::row_count() const
{
    return items_.size();
}

size_t StandardItemModel::Impl::column_count() const
{
    return column_count_;
}

void StandardItemModel::Impl::set_row_count(size_t c)
{
    items_.resize(c);
}

void StandardItemModel::Impl::set_column_count(size_t c)
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
    assert(row <= row_count());
    auto pos = std::next(items_.begin(), row);
    items_.insert(pos, count, {});
}

void StandardItemModel::Impl::RemoveRows(size_t row, size_t count)
{
    assert(row + count <= row_count());
    auto start = std::next(items_.begin(), row);
    auto end = std::next(start, count);
    items_.erase(start, end);
}

void StandardItemModel::Impl::InsertColumns(size_t column, size_t count)
{
    assert(column <= column_count());
    // 如果是在末尾插入的, 只需要修改column_count_
    if (column != column_count())
    {
        for (auto& r : items_)
        {
            // 如果是在当前行的列数中间插入的, 才需要真正插入
            if (r.size() > column)
            {
                auto pos = std::next(r.begin(), column);
                r.insert(pos, count, {});
            }
        }
    }
    column_count_ += count;
}

void StandardItemModel::Impl::RemoveColumns(size_t column, size_t count)
{
    assert(column + count <= column_count());
    for (auto& r : items_)
    {
        if (r.size() > column)
        {
            auto c = r.size() - column;
            auto start = std::next(r.begin(), column);
            auto end = std::next(start, c);
            r.erase(start, end);
        }
    }
    column_count_ -= count;
}

std::optional<StandardItem&> StandardItemModel::Impl::item(const ModelIndex& idx)
{
    assert(idx.valid());
    assert(idx.row <= row_count() && idx.column <= column_count());
    auto& r = items_[idx.row];
    if (r.size() <= idx.column)
    {
        return std::nullopt;
    }
    return r[idx.column - 1];
}

StandardItem& StandardItemModel::Impl::GetOrCreateItem(const ModelIndex& idx)
{
    assert(idx.valid());
    assert(idx.row <= row_count() && idx.column <= column_count());
    auto& r = items_[idx.row];
    if (r.size() <= idx.column)
    {
        r.resize(idx.column);
    }
    return r[idx.column - 1];
}

void StandardItemModel::Impl::Clear()
{
    items_.clear();
}
}
