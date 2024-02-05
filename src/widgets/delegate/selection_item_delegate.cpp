#include <mvcgui/widgets/delegate/selection_item_delegate.h>
#include <mvcgui/widgets/view/base/abstract_item_view.h>
#include <mvcgui/model/base/abstract_item_model.h>
#include <mvcgui/core/drawer.h>
#include <mvcgui/io/input.h>
#include <mvcgui/core/flags.h>

namespace mvcgui {
SelectionItemDelegate::SelectionItemDelegate()
	: AbstractItemDelegate{}
{
}

void SelectionItemDelegate::Paint(const AbstractItemView& view, const ModelIndex& index) {
	auto model = view.model();
	auto text = model->text(index);
	bool is_selected = view.is_selected_item(index);
	bool tmp = is_selected;
	if (Drawer::Selectable(text, &tmp, flags::selectable::kSpanAllColumns | flags::selectable::kAllowOverlap)) {
        if (Input::GetKeyDown(KeyCode::kCtrl)) {
            Emit(on_selection_changed_, index, !is_selected);
        }
        else {
            Emit(on_current_index_changed_, index);
        }
	}
}
}