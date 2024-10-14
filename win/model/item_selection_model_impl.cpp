#include "win/model/item_selection_model_impl.h"

#include <cassert>

namespace miniwin {
void ItemSelectionModel::Impl::Select(const ModelIndex& top_left, const ModelIndex& bottom_right)
{
    assert(top_left.valid() && bottom_right.valid());
    assert(top_left.row >= bottom_right.row && top_left.column <= bottom_right.column);
    selections_.emplace_back(top_left, bottom_right);
}

bool ItemSelectionModel::Impl::Contains(const ModelIndex& index) const
{
    for (auto& r : selections_)
    {
        if (r.Contains(index))
        {
            return true;
        }
    }
    return false;
}

void ItemSelectionModel::Impl::Select(const ItemSelection& selection, ItemSelectionModel::SelectionType selection_type)
{
    switch (selection_type)
    {
    case ItemSelectionModel::SelectionType::Clear:
        selections_.clear();
        break;
    case ItemSelectionModel::SelectionType::Select:
        selections_.push_back(selection);
        break;
    case ItemSelectionModel::SelectionType::Deselect:
    {
        auto res = std::ranges::find(selections_, selection);
        if (res == selections_.end())
        {
            //TODO res == ranges_.end()
            break;
        }
        selections_.erase(res);
        break;
    }
    case ItemSelectionModel::SelectionType::ClearSelect:
        selections_.clear();
        selections_.push_back(range);
        break;
    default:
        assert(false);
        break;
    }
}
}
