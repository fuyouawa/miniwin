#include <mvcgui/widgets/view/table_view.h>
#include <mvcgui/core/drawer.h>

namespace mvcgui {
TableView::TableView(Widget* const parent, std::u8string_view label, bool show)
	: AbstractItemView{ parent, label, show },
	table_open_{ false }
{
}

void TableView::OnItemShowablePaintBegin() {
	table_open_ = Drawer::BeginTable(label_, model_->column_count(), flags_, size_);
	if (table_open_) {
		Drawer::TableColumns(column_model_);
		Drawer::TableItems(model_, delegate_);
	}
}

void TableView::OnItemShowablePaintEnd() {
	if (table_open_) {
		Drawer::EndTable();
	}
}
}