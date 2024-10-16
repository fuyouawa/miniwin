#include <win/model/item_selection_model_impl.h>
#include <cassert>

namespace miniwin {
bool ItemSelection::valid() const
{
    return top_left.valid() && bottom_right.valid()
        && top_left.row <= bottom_right.row
        && top_left.column <= bottom_right.column;
}

bool operator==(const ItemSelection& x, const ItemSelection& y)
{
    return x.top_left == y.top_left && x.bottom_right == y.bottom_right;
}

ItemSelectionModel::ItemSelectionModel(Object* parent, AbstractItemModel* model)
    : Object(parent, u8"SelectionModel", ObjectType::SelectionModel)
{
    impl_ = std::make_unique<Impl>(this, model);
}

const ItemSelection& ItemSelectionModel::current_selection() const
{
    return impl_->current_selection_;
}

AbstractItemModel* ItemSelectionModel::Model() const
{
    return impl_->model_;
}

void ItemSelectionModel::Select(const ModelIndex& index, SelectionType selection_type)
{
    Select(ItemSelection{ index, index }, selection_type);
}

void ItemSelectionModel::Select(const ItemSelection& selection, SelectionType selection_type)
{
    assert(selection.valid());
    if (selection_type == SelectionType::ClearSelect)
    {
        impl_->Clear();
        selection_type = SelectionType::Select;
    }
    impl_->Select(selection, selection_type == SelectionType::Select);
    OnSelectionChanged(selection, selection_type);
}

void ItemSelectionModel::Clear()
{
    impl_->Clear();
    OnClearedSelection();
}

bool ItemSelectionModel::IsSelected(const ModelIndex& index) const
{
    assert(index.valid());
    return impl_->Contains(index);
}
}
