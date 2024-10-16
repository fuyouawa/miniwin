#pragma once
#include <miniwin/model/item_selection_model.h>
#include <miniwin/model/base/abstract_item_model.h>
#include <bitset>
#include <cassert>

namespace miniwin {
class ItemSelectionModel::Impl {
public:
    static constexpr size_t kLengthOfOneBitsetSelections = sizeof(size_t) * 8;
    using BitsetSelections = std::bitset<kLengthOfOneBitsetSelections>;
    using OneBitsetSelectionsTable = std::vector<BitsetSelections>;

    explicit Impl(ItemSelectionModel* owner, AbstractItemModel* model)
        : owner_(owner), model_(model)
    {
    }

    bool Contains(const ModelIndex& index) const
    {
        auto c = GetSelectionsTableIndex(index.column);
        if (c > selections_.size())
        {
            return false;
        }
        auto& r = selections_[c];
        if (index.row >= r.size())
        {
            return false;
        }
        auto& b = r[index.row];
        auto i = GetSelectionIndex(index.column);
        return b[i];
    }

    void Select(const ItemSelection& selection, bool is_select)
    {

        EnsureIndex(selection.bottom_right);

        for (int row = selection.top_left.row; row <= selection.bottom_right.row; ++row)
        {
            for (int col = selection.top_left.column; col <= selection.bottom_right.column; ++col)
            {
                assert(model_ && model_->IsValidIndex({ row, col }));
                auto c = GetSelectionsTableIndex(col);
                auto& r = selections_[c];
                auto& b = r[row];
                auto i = GetSelectionIndex(col);
                b.set(i, is_select);
            }
        }

        current_selection_ = selection;
    }
    void Clear()
    {
        selections_.clear();
    }

    void EnsureIndex(const ModelIndex& index)
    {
        assert(model_ && model_->IsValidIndex(index));

        // 确保selection表的行数不小于index的行
        for (auto& s : selections_)
        {
            if (s.size() < index.row)
            {
                s.resize(index.row);
            }
        }

        // 确保selection表的列数不小于index的列
        auto c = GetSelectionsTableIndex(index.column);
        if (c >= selections_.size())
        {
            for (size_t i = 0; i < c - selections_.size() + 1; ++i)
            {
                selections_.emplace_back(model_->RowCount());
            }
        }
    }

    static size_t GetSelectionsTableIndex(size_t column)
    {
        return ((column + kLengthOfOneBitsetSelections) / kLengthOfOneBitsetSelections) - 1;
    }
    static size_t GetSelectionIndex(size_t column)
    {
        return column & kLengthOfOneBitsetSelections;
    }

    ItemSelectionModel* owner_;
    ItemSelection current_selection_;
    std::vector<OneBitsetSelectionsTable> selections_;
    AbstractItemModel* model_;
};
}
