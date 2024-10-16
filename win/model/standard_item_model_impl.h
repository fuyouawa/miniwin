#pragma once
#include <cassert>
#include <miniwin/model/standard_item_model.h>
#include <string>

namespace miniwin {
using StandardItem = std::unordered_map<ItemRole, std::any>;

using StandardLineItems = std::vector<StandardItem>;

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
        items_.insert(items_.begin() + row, count, {});

        vertical_header_items_.insert(vertical_header_items_.begin() + row, count, {});
    }
    void RemoveRows(size_t row, size_t count) {
        assert(row + count <= row_count());
        auto pos = items_.begin() + row;
        items_.erase(pos, pos + count);

        auto pos2 = vertical_header_items_.begin() + row;
        vertical_header_items_.erase(pos2, pos2 + count);
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
                    r.insert(r.begin() + column, count, {});
                }
            }
        }
        horizontal_header_items_.insert(horizontal_header_items_.begin() + column, count, {});
        column_count_ += count;
    }
    void RemoveColumns(size_t column, size_t count) {
        assert(column + count <= column_count());
        for (auto& r : items_)
        {
            if (r.size() > column)
            {
                auto c = r.size() - column;
                auto pos = r.begin() + column;
                r.erase(pos, pos + c);
            }
        }
        auto pos = horizontal_header_items_.begin() + column;
        horizontal_header_items_.erase(pos, pos + count);

        column_count_ -= count;
    }

    StandardItem& item(const ModelIndex& idx) {
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
    std::vector<StandardLineItems> items_;
    size_t column_count_;
    StandardLineItems horizontal_header_items_;
    StandardLineItems vertical_header_items_;
};
}
