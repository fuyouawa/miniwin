#include "combobox_impl.h"

#include <miniwin/delegate/selectable_item_delegate.h>
#include <miniwin/model/standard_item_model.h>

namespace miniwin {
ComboBoxView::Impl::Impl(ComboBoxView* owner)
	: owner_(owner)
{
}

void ComboBoxView::Impl::Awake()
{
	auto d = Instantiate<SelectableItemDelegate>(owner_->shared_from_this());
	owner_->SetItemDelegate(d);
}

ComboBox::Impl::Impl(ComboBox* owner)
	: owner_(owner)
{
}

void ComboBox::Impl::Awake()
{
	view_ = Instantiate<ComboBoxView>(owner_->shared_from_this());
	auto model = Instantiate<StandardItemModel>(owner_->shared_from_this());
	model->SetColumnCount(1);
	view_->SetModel(model);
}
}
