#pragma once
#include <miniwin/core/object.h>
#include <miniwin/model/base/model_index.h>

namespace miniwin {
struct ItemSelection {
    ModelIndex top_left;
    ModelIndex bottom_right;

    bool valid() const;
};

bool operator==(const ItemSelection& x, const ItemSelection& y);

class ItemSelectionModel : public Object
{
public:
    enum class SelectionType
    {
        Select,
        Deselect,
        ClearSelect
    };

    ItemSelectionModel();

    void Select(const ModelIndex& index, SelectionType selection_type);
    void Select(const ItemSelection& selection, SelectionType selection_type);
    void Clear();

    bool IsSelected(const ModelIndex& index) const;

    MW_SIGNAL(OnSelectionChanged, (ItemSelection) selection, (SelectionType) selection_type)
    MW_SIGNAL(OnClearedSelection)

private:
    friend class AbstractItemView;
    void set_parent(Object* parent) const override;

    _MW_IMPL
};
}
