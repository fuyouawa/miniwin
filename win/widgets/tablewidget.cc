#include "tablewidget_impl.h"

namespace miniwin {
TableWidget::TableWidget(Widget* parent, std::u8string_view id)
	: Widget(parent, u8"TableWidget")
{
	impl_ = std::make_unique<Impl>(this);
	impl_->Init(id);
}

TableWidget::~TableWidget()
{
}
}
