#include "tablewidget_impl.h"

#include "miniwin/model/standard_item_model.h"

namespace miniwin {
TableWidget::Impl::Impl(TableWidget* owner)
	: owner_(owner)
{
}

void TableWidget::Impl::Init(std::u8string_view id)
{
	view_ = new TableView(owner_, id);

	auto model = new StandardItemModel(owner_);
	view_->SetModel(model);
}
}
