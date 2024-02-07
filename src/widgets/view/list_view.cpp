#include <mvcgui/widgets/view/list_view.h>
#include <mvcgui/model/standard_list_model.h>
#include <mvcgui/delegate/selection_item_delegate.h>
#include <mvcgui/core/drawer.h>

namespace mvcgui {
ListView::ListView(Widget* const parent, std::u8string_view label, bool show)
	: AbstractItemView{ parent, label, show },
	listbox_open_{ false }
{
	set_model(Instantiate<StandardListModel>());
	set_delegate(Instantiate<SelectionItemDelegate>());
}

void ListView::OnItemShowablePaintBegin()
{
	listbox_open_ = Drawer::BeginListBox(label_);
	if (listbox_open_) {
		Drawer::ListItems(model_, delegate_);
	}
}

void ListView::OnItemShowablePaintEnd()
{
	if (listbox_open_) {
		Drawer::EndListBox();
	}
}
}