#include "combobox_impl.h"

#include "miniwin/model/standard_item_model.h"

namespace miniwin {
ComboBox::Impl::Impl(ComboBox* owner)
	: owner_(owner)
{
}

void ComboBox::Impl::Init(std::u8string_view label)
{
	view_ = new ComboBoxView(owner_, label);
	auto model = new StandardItemModel(owner_);
	model->SetColumnCount(1);
	view_->SetModel(model);
}
}
