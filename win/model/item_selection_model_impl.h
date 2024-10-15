#pragma once
#include <miniwin/model/item_selection_model.h>
#include <miniwin/model/base/abstract_item_model.h>
#include <bitset>

namespace miniwin {
class ItemSelectionModel::Impl {
public:
    static constexpr size_t kLengthOfOneBitsetSelections = sizeof(size_t) * 8;
    using BitsetSelections = std::bitset<kLengthOfOneBitsetSelections>;
    using OneBitsetSelectionsTable = std::vector<BitsetSelections>;

    explicit Impl(ItemSelectionModel* owner);

    bool Contains(const ModelIndex& index) const;

    void Select(const ModelIndex& index, bool is_select);
    void Clear();

    void EnsureIndex(const ModelIndex& index);

    static size_t GetSelectionsTableIndex(size_t column);
    static size_t GetSelectionIndex(size_t column);

    ItemSelectionModel* owner_;
    std::vector<OneBitsetSelectionsTable> selections_;
    AbstractItemModel* model_;
};
}
