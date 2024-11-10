#include "abstract_item_view_impl.h"

#include <miniwin/delegate/base/abstract_item_delegate.h>

#include "win/tools/debug.h"


namespace miniwin {
AbstractItemView::AbstractItemView(Widget* parent)
    : Widget(parent, "View")
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

    auto m = new ItemSelectionModel(this, impl_->model_);
    SetSelectionModel(m);
}

AbstractItemModel* AbstractItemView::Model() const
{
    return impl_->model_;
}

void AbstractItemView::SetSelectionModel(ItemSelectionModel* selection_model)
{
    if (impl_->selection_model_ == selection_model)
        return;
    MW_ASSERT_X(selection_model);
    if (selection_model->Model() != impl_->model_)
    {
        throw std::exception("AbstractItemView::SetSelectionModel() failed: "
                             "Trying to set a selection model, "
                             "which works on a different model than the view.");
    }

    impl_->selection_model_ = selection_model;
}

ItemSelectionModel* AbstractItemView::SelectionModel() const
{
    return impl_->selection_model_;
}

void AbstractItemView::SetItemDelegate(AbstractItemDelegate* item_delegate)
{
    if (impl_->item_delegate_ == item_delegate)
        return;
    MW_ASSERT_X(item_delegate);

    impl_->item_delegate_ = item_delegate;

    impl_->item_delegate_->SetParent(this);
}

AbstractItemDelegate* AbstractItemView::ItemDelegate() const
{
    return impl_->item_delegate_;
}
}
