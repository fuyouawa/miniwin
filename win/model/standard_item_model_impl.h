#pragma once
#include <cassert>
#include <optional>
#include <miniwin/model/standard_item_model.h>
#include <string>

namespace miniwin {
struct StandardItem
{
    std::u8string text;
    std::any user_data;
    int flags = 0;
};

class StandardItemModel::Impl
{
public:
    Impl(StandardItemModel* owner)
        : owner_(owner), column_count_(0)
    {
    }

    StandardItemModel* owner_;

    size_t row_count() const {
        return items_.size();
    }
    size_t column_count() const {
        return column_count_;
    }

    void set_row_count(size_t c) {
        items_.resize(c);
    }
    void set_column_count(size_t c) {
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

    void InsertRows(size_t row, size_t count) {
        assert(row <= row_count());
        auto pos = std::next(items_.begin(), row);
        items_.insert(pos, count, {});
    }
    void RemoveRows(size_t row, size_t count) {
        assert(row + count <= row_count());
        auto start = std::next(items_.begin(), row);
        auto end = std::next(start, count);
        items_.erase(start, end);
    }

    void InsertColumns(size_t column, size_t count) {
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
    void RemoveColumns(size_t column, size_t count) {
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

    const StandardItem& item(const ModelIndex& idx) {
        static StandardItem empty_item;
        assert(idx.valid());
        assert(idx.row <= row_count() && idx.column <= column_count());
        auto& r = items_[idx.row];
        if (r.size() <= idx.column)
        {
            return empty_item;
        }
        return r[idx.column - 1];
    }
    StandardItem& GetOrCreateItem(const ModelIndex& idx) {
        assert(idx.valid());
        assert(idx.row <= row_count() && idx.column <= column_count());
        auto& r = items_[idx.row];
        if (r.size() <= idx.column)
        {
            r.resize(idx.column);
        }
        return r[idx.column - 1];
    }

    void Clear() {
        items_.clear();
    }

private:
    using RowData = std::vector<StandardItem>;
    std::vector<RowData> items_;
    size_t column_count_;
};
}
