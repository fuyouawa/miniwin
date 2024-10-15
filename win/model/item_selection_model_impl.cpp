#include "win/model/item_selection_model_impl.h"

#include <cassert>

namespace miniwin {
ItemSelectionModel::Impl::Impl(ItemSelectionModel* owner)
    : owner_(owner), model_(nullptr)
{
}

bool ItemSelectionModel::Impl::Contains(const ModelIndex& index) const
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

void ItemSelectionModel::Impl::Select(const ModelIndex& index, bool is_select)
{
    assert(model_ && model_->IsValidIndex(index));
    EnsureIndex(index);
    auto c = GetSelectionsTableIndex(index.column);
    auto r& = selections_[c];
    auto& b = r[index.row];
    auto i = GetSelectionIndex(index.column);
    b.set(i, is_select);
}

void ItemSelectionModel::Impl::Clear()
{
    selections_.clear();
}

void ItemSelectionModel::Impl::EnsureIndex(const ModelIndex& index)
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
            selections_.emplace_back(model_->row_count());
        }
    }
}

size_t ItemSelectionModel::Impl::GetSelectionsTableIndex(size_t column)
{
    return ((column + kLengthOfOneBitsetSelections) / kLengthOfOneBitsetSelections) - 1;
}

size_t ItemSelectionModel::Impl::GetSelectionIndex(size_t column)
{
    return column & kLengthOfOneBitsetSelections;
}
}
