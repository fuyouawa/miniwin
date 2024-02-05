#include <imwin/widgets/view/single_selection_list_view.h>
#include <imgui/imgui.h>
#include <imwin/tools/utils.h>

namespace imwin {
SingleSelectionListView::SingleSelectionListView(Widget* const parent, std::u8string_view label)
	: AbstractItemView{ parent, label }
{
}

void SingleSelectionListView::ShowItems() {
	for (int i = 0; i < model_->row_count(); ++i) {
		const bool selected = (cur_selection_.row() == i);
		if (ImGui::Selectable(cstr(model_->text(i)), selected)) {
			cur_selection_.set_row(i);
		}

		if (selected) {
			ImGui::SetItemDefaultFocus();
		}
	}

	if (selection_changed()) {
		Emit(on_selection_changed_, cur_selection_, prev_selection_);
	}
	prev_selection_ = cur_selection_;
}
}