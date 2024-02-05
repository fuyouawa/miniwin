#include <mvcgui/widgets/view/list_view.h>
#include <mvcgui/model/standard_list_model.h>
#include <mvcgui/widgets/delegate/selection_item_delegate.h>
#include <mvcgui/core/drawer.h>

namespace mvcgui {
ListView::ListView(Widget* const parent, std::u8string_view label, bool show)
	: AbstractListView{ parent, label,
		Instantiate<StandardListModel>(),
		Instantiate<SelectionItemDelegate>(),
		show }
{
}

void ListView::OnItemShowablePaintBegin()
{
	listbox_open_ = Drawer::BeginListBox(label_);
	if (listbox_open_) {
		PaintItems();
	}
}

void ListView::OnItemShowablePaintEnd()
{
	if (listbox_open_) {
		Drawer::EndListBox();
	}
}
}