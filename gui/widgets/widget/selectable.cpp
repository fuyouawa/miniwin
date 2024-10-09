#include <fugui/widgets/widget/selectable.h>
#include <gui/core/drawer.h>

#include <gui/tools/algorithm.h>

namespace fugui {
Selectable::Selectable(Widget* const parent, std::u8string_view label, bool show)
	: AbstractMinimumControl{ parent, label, show },
	cur_selected_{ false },
	prev_selected_{ false }
{
}
void Selectable::OnItemShowablePaintBegin() {
	Drawer::Selectable(label_, &cur_selected_, flags(), size());
}

void Selectable::OnUpdate() {
	AbstractMinimumControl::OnUpdate();

	if (cur_selected_ != prev_selected_) {
		Emit(on_selection_changed_, cur_selected_);
	}
	prev_selected_ = cur_selected_;
}
}