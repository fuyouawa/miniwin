#pragma once
#include <miniwin/core/object.h>
#include <miniwin/model/base/model_index.h>

namespace miniwin {
class ItemSelection {
public:
    ItemSelection() = default;
    ItemSelection(const ModelIndex& top_left, const ModelIndex& bottom_right);

    bool Contains(const ModelIndex& index) const;

    auto& top_left() const { return tl_; }
    auto& bottom_right() const { return br_; }

private:
    ModelIndex tl_, br_;
};

bool operator==(const ItemSelection& x, const ItemSelection& y);

class ItemSelectionModel : public Object
{
public:
    enum class SelectionType
    {
        Clear,
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

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
}
