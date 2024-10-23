#include "combobox_impl.h"

#include <miniwin/delegate/selectable_item_delegate.h>
#include <miniwin/model/standard_item_model.h>

namespace miniwin {
ComboBoxView::Impl::Impl(ComboBoxView* owner)
	: owner_(owner)
{
}

void ComboBoxView::Impl::Init()
{
	auto d = new SelectableItemDelegate(owner_);
	owner_->SetItemDelegate(d);
}

ComboBox::Impl::Impl(ComboBox* owner)
	: owner_(owner)
{
}

void ComboBox::Impl::Init(std::u8string_view text)
{
	view_ = new ComboBoxView(owner_, text);
	auto model = new StandardItemModel(owner_);
	model->SetColumnCount(1);
	view_->SetModel(model);
}
}
