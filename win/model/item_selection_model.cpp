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
    assert(selection.valid());
    if (selection_type == SelectionType::ClearSelect)
    {
        impl_->Clear();
        selection_type = SelectionType::Select;
    }
    for (int row = selection.top_left.row; row <= selection.bottom_right.row; ++row)
    {
        for (int col = selection.top_left.column; col <= selection.bottom_right.column; ++col)
        {
            impl_->Select({ row, col }, selection_type == SelectionType::Select);
        }
    }
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

void ItemSelectionModel::set_parent(Object* parent) const
{
    auto m = dynamic_cast<AbstractItemModel*>(parent);
    assert(m != nullptr);
    Object::set_parent(parent);
    impl_->model_ = m;
    impl_->Clear();
}
}
