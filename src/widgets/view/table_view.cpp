#include <fugui/widgets/view/table_view.h>
#include <fugui/core/drawer.h>
#include <fugui/model/standard_table_model.h>
#include <fugui/delegate/selection_item_delegate.h>

namespace fugui {
TableView::TableView(Widget* const parent, std::u8string_view label, bool show)
	: AbstractItemView{ parent, label, show },
	table_open_{ false }
{
	set_model(Instantiate<StandardTableModel>());
	set_delegate(Instantiate<SelectionItemDelegate>());
}

void TableView::OnItemShowablePaintBegin() {
	table_open_ = Drawer::BeginTable(label_, model_->column_count(), flags_, size_);
	if (table_open_) {
		Drawer::TableColumns(model());
		Drawer::TableItems(model(), delegate_);
	}
}

void TableView::OnItemShowablePaintEnd() {
	if (table_open_) {
		Drawer::EndTable();
	}
}
}