#include <miniwin/widgets/base/abstract_item_view.h>

#include <miniwin/delegate/base/abstract_item_delegate.h>
#include <miniwin/model/base/abstract_item_model.h>
#include <miniwin/model/item_selection_model.h>

#include "win/tools/debug.h"


namespace miniwin {
class AbstractItemView::Impl {
public:
    explicit Impl(AbstractItemView* owner) : owner_(owner) {}

    AbstractItemView* owner_;

    SharedItemModel model_;
    SharedItemDelegate item_delegate_ ;
    SharedItemSelectionModel selection_model_;
};

AbstractItemView::AbstractItemView()
{
    impl_ = std::make_unique<Impl>(this);
}

AbstractItemView::~AbstractItemView()
{
}

void AbstractItemView::SetModel(const SharedItemModel& model)
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
        impl_->model_->SetParent(shared_from_this());
    }

    auto m = Instantiate<ItemSelectionModel>(shared_from_this());
    m->SetModel(impl_->model_);
    SetSelectionModel(m);
}

const SharedItemModel& AbstractItemView::Model() const
{
    return impl_->model_;
}

void AbstractItemView::SetSelectionModel(const SharedItemSelectionModel& selection_model)
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

SharedItemSelectionModel AbstractItemView::SelectionModel() const
{
    return impl_->selection_model_;
}

void AbstractItemView::SetItemDelegate(const SharedItemDelegate& item_delegate)
{
    if (impl_->item_delegate_ == item_delegate)
        return;
    MW_ASSERT_X(item_delegate);

    impl_->item_delegate_ = item_delegate;

    impl_->item_delegate_->SetParent(shared_from_this());
}

const SharedItemDelegate& AbstractItemView::ItemDelegate() const
{
    return impl_->item_delegate_;
}

void AbstractItemView::Initialize(const SharedObject& parent) {
	Widget::Initialize(parent);
    SetName("ItemView");
}
}
