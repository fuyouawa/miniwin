#include <cassert>

#include "win/widgets/base/abstract_item_view_impl.h"

namespace miniwin {
AbstractItemView::AbstractItemView(Widget* parent)
    : Widget(parent, u8"View", WidgetType::kView)
{
    impl_ = std::make_unique<Impl>(this);
}

AbstractItemView::~AbstractItemView()
{
}

void AbstractItemView::SetModel(AbstractItemModel* model)
{
    if (impl_->model_ == model)
        return;

    if (impl_->model_ && impl_->model_ != AbstractItemModel::StaticEmptyModel())
    {
        impl_->model_->SetParent(nullptr);
    }
    impl_->model_ = model ? model : AbstractItemModel::StaticEmptyModel();

    if (impl_->model_ != AbstractItemModel::StaticEmptyModel())
    {
        impl_->model_->SetParent(this);
    }

    impl_->selection_model_->SetModel(model);
}

AbstractItemModel* AbstractItemView::GetModel() const
{
    return impl_->model_;
}

void AbstractItemView::SetSelectionModel(ItemSelectionModel* selection_model)
{
    if (impl_->selection_model_ == selection_model)
        return;
    assert(selection_model);
    if (selection_model->GetModel() != impl_->model_)
    {
        throw std::exception("AbstractItemView::SetSelectionModel() failed: "
                             "Trying to set a selection model, "
                             "which works on a different model than the view.");
    }

    if (impl_->selection_model_)
    {
        impl_->selection_model_->SetModel(nullptr);
    }
    impl_->selection_model_ = selection_model;
}

ItemSelectionModel* AbstractItemView::GetSelectionModel() const
{
    return impl_->selection_model_;
}

void AbstractItemView::SetItemDelegate(AbstractItemDelegate* item_delegate)
{
    if (impl_->item_delegate_ == item_delegate)
        return;
    assert(item_delegate);

    impl_->item_delegate_ = item_delegate;

    impl_->item_delegate_->SetParent(this);
}

AbstractItemDelegate* AbstractItemView::GetItemDelegate() const
{
    return impl_->item_delegate_;
}
}
