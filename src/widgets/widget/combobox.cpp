#include <mvcgui/widgets/widget/combobox.h>
#include <mvcgui/model/standard_list_model.h>
#include <mvcgui/tools/algorithm.h>
#include <mvcgui/core/drawer.h>

namespace mvcgui {
ComboBox::ComboBox(Widget* const parent, std::u8string_view label, bool show)
	: AbstractMinimumControl{ parent, label, show },
	cur_idx_{ 0 },
	prev_idx_{ -1 }
{
	model_ = std::make_shared<StandardListModel>();
}

void ComboBox::OnItemShowablePaintBegin() {
	is_combo_open_ = Drawer::ComboBox(label_, model_, &cur_idx_, flags_, size_);
}

void ComboBox::OnUpdate() {
	AbstractMinimumControl::OnUpdate();
	if (cur_idx_ != prev_idx_) {
		Emit(on_current_changed_, cur_idx_, prev_idx_);
	}
	prev_idx_ = cur_idx_;
}
}