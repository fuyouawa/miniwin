#pragma once
#include <miniwin/widgets/tablewidget.h>
#include <miniwin/widgets/view/tableview.h>

namespace miniwin {
class TableWidget::Impl
{
public:
	Impl(TableWidget* owner);

	void Init(std::u8string_view id);

	TableWidget* owner_;
	TableView* view_ = nullptr;
};
}