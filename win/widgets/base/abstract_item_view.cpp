#include <cassert>

#include "win/widgets/base/abstract_item_view_impl.h"

namespace miniwin {
AbstractItemView::AbstractItemView(Widget* parent, bool show)
    : Widget(parent, u8"View", show, WidgetType::kView)
{
    impl_ = std::make_unique<Impl>(this);
}

void AbstractItemView::set_model(AbstractItemModel* model)
{
    if (impl_->model_ == model)
        return;

    if (impl_->model_ && impl_->model_ != AbstractItemModel::StaticEmptyModel())
    {
        impl_->model_->set_parent(nullptr);
    }
    impl_->model_ = model ? model : AbstractItemModel::StaticEmptyModel();

    if (impl_->model_ != AbstractItemModel::StaticEmptyModel())
    {
        impl_->model_->set_parent(this);
    }

    impl_->selection_model_->set_parent(model);
}

AbstractItemModel* AbstractItemView::model() const
{
    return impl_->model_;
}

void AbstractItemView::set_selection_model(ItemSelectionModel* selection_model)
{
    if (impl_->selection_model_ == selection_model)
        return;
    assert(selection_model);

    if (impl_->selection_model_)
    {
        impl_->selection_model_->set_parent(nullptr);
    }
    impl_->selection_model_ = selection_model;

    impl_->selection_model_->set_parent(this);
}

ItemSelectionModel* AbstractItemView::selection_model() const
{
    return impl_->selection_model_;
}

void AbstractItemView::set_item_delegate(AbstractItemDelegate* item_delegate)
{
    if (impl_->item_delegate_ == item_delegate)
        return;
    assert(item_delegate);

    if (impl_->item_delegate_)
    {
        impl_->item_delegate_->set_parent(nullptr);
    }
    impl_->item_delegate_ = item_delegate;

    impl_->item_delegate_->set_parent(this);
}

AbstractItemDelegate* AbstractItemView::item_delegate() const
{
    return impl_->item_delegate_;
}
}
