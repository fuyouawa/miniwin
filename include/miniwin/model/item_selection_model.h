#pragma once
#include <miniwin/core/object.h>
#include <miniwin/model/base/abstract_item_model.h>
#include <miniwin/model/base/model_index.h>

namespace miniwin {
class ItemSelection {
public:
    ItemSelection() = default;
    ItemSelection(const ModelIndex& index)
		: top_left_(index), bottom_right_(index)
	{}
    ItemSelection(const ModelIndex & top_left, const ModelIndex& bottom_right)
        : top_left_(top_left), bottom_right_(bottom_right)
    {}

    bool valid() const;

    auto& top_left() const { return top_left_; }
    auto& bottom_right() const { return bottom_right_; }

    void set_top_left(const ModelIndex& index) { top_left_ = index; }
    void set_bottom_right(const ModelIndex& index) { bottom_right_ = index; }

private:
    ModelIndex top_left_;
    ModelIndex bottom_right_;
};

bool operator==(const ItemSelection& x, const ItemSelection& y);

enum class ItemSelectionType
{
    Select,
    Deselect,
    ClearSelect
};

class ItemSelectionModel : public Object
{
public:
    ItemSelectionModel(Object* parent, AbstractItemModel* model);

    const ItemSelection& CurrentSelection() const;

    AbstractItemModel* Model() const;

    void Select(size_t row, size_t column, ItemSelectionType selection_type = ItemSelectionType::Select);
    void Select(const ItemSelection& selection, ItemSelectionType selection_type = ItemSelectionType::Select);
    void Clear();

    bool IsSelected(const ModelIndex& index) const;

    MW_SIGNAL(OnSelectionChanged, (ItemSelection) selection, (ItemSelectionType) selection_type)
    MW_SIGNAL(OnClearedSelection)

    _MW_IMPL
};
}
