#include <fugui/delegate/selection_item_delegate.h>
#include <fugui/model/base/abstract_item_model.h>
#include <fugui/core/drawer.h>
#include <fugui/io/input.h>
#include <fugui/core/flags.h>

namespace fugui {
SelectionItemDelegate::SelectionItemDelegate()
	: AbstractItemDelegate{}
{
}

void SelectionItemDelegate::Paint(AbstractItemModelPtr model, const ModelIndex& index) {
	auto text = model->text(index);
	bool is_selected = model->is_selected(index);
	bool tmp = is_selected;
	if (Drawer::Selectable(text, &tmp, flags::selectable::kSpanAllColumns | flags::selectable::kAllowOverlap)) {
        if (Input::IsIoKeyDown(IoKeyCode::kCtrl)) {
            Emit(on_selection_changed_, index, !is_selected);
        }
        else {
            Emit(on_current_index_changed_, index);
        }
	}
}
}