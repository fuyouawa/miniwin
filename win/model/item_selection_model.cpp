#include <win/model/item_selection_model_impl.h>

namespace miniwin {
ItemSelection::ItemSelection(const ModelIndex& top_left, const ModelIndex& bottom_right)
    : tl_(top_left), br_(bottom_right)
{
}

bool ItemSelection::Contains(const ModelIndex& index) const
{
    return tl_.row <= index.row && tl_.column <= index.column
        && br_.row >= index.row && br_.column >= index.column;
}

bool operator==(const ItemSelection& x, const ItemSelection& y)
{
    return x.top_left() == y.top_left() && x.bottom_right() == y.bottom_right();
}

ItemSelectionModel::ItemSelectionModel()
    : Object(nullptr, u8"SelectionModel", ObjectType::SelectionModel)
{
    impl_ = std::make_unique<Impl>(this);
}

void ItemSelectionModel::Select(const ModelIndex& index, SelectionType selection_type)
{
    Select(ItemSelection{ index, index }, selection_type);
}

void ItemSelectionModel::Select(const ItemSelection& selection, SelectionType selection_type)
{
    impl_->Select(selection, selection_type);
    OnSelectionChanged(selection, selection_type);
}

void ItemSelectionModel::Clear()
{
    Select(ItemSelection{}, SelectionType::Clear);
}
}
