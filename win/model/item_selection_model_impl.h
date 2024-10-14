#pragma once
#include <miniwin/model/item_selection_model.h>
#include <miniwin/model/base/abstract_item_model.h>

namespace miniwin {
class ItemSelectionModel::Impl {
public:
    explicit Impl(ItemSelectionModel* owner)
        : owner_(owner), model_(nullptr)
    {
    }

    void Select(const ModelIndex& top_left, const ModelIndex& bottom_right);
    bool Contains(const ModelIndex& index) const;

    void Select(const ItemSelection& selection, SelectionType selection_type);

    ItemSelectionModel* owner_;
    std::list<ItemSelection> selections_;
    AbstractItemModel* model_;
};
}
