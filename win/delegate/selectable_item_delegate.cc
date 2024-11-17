#include <miniwin/delegate/selectable_item_delegate.h>

#include <miniwin/io/input.h>
#include <miniwin/core/imgui.h>
#include <miniwin/widgets/base/abstract_item_view.h>
#include <miniwin/model/item_selection_model.h>

namespace miniwin {
class SelectableItemDelegate::Impl {
public:
	Impl(SelectableItemDelegate* owner) : owner_(owner) {}

	SelectableItemDelegate* owner_;

	bool alloc_multi_select = true;
};

SelectableItemDelegate::SelectableItemDelegate() {
	impl_ = std::make_unique<Impl>(this);
}

SelectableItemDelegate::~SelectableItemDelegate() {}

bool SelectableItemDelegate::IsAllocMultiSelect() const {
	return impl_->alloc_multi_select;
}

void SelectableItemDelegate::SetAllocMultiSelect(bool b) {
	impl_->alloc_multi_select = b;
}

void SelectableItemDelegate::Paint(const SharedItemView& view, const ModelIndex& index) {
	auto model = view->Model();
	auto selection_model = view->SelectionModel();
	auto text = model->Data(index).ToString();
	bool is_selected = selection_model->IsSelected(index);
	if (imgui::Selectable(text, &is_selected)) {
		if (io::IsKeyDown(KeyCode::kCtrl) && IsAllocMultiSelect()) {
			selection_model->Select(index, is_selected
				                               ? ItemSelectionType::Select
				                               : ItemSelectionType::Deselect);
		}
		else {
			if (is_selected) {
				selection_model->Select(index, ItemSelectionType::ClearSelect);
			}
			else {
				selection_model->Clear();
			}
		}
	}
}
}
