#include <fugui/widgets/widget/combobox.h>
#include <fugui/model/standard_list_model.h>
#include <gui/core/drawer.h>

namespace fugui {
ComboBox::ComboBox(Widget* const parent, std::u8string_view label, bool show)
	: AbstractMinimumControl{ parent, label, show },
	cur_idx_{ 0 },
	prev_idx_{ static_cast<uint64_t>(-1) }
{
	model_ = std::make_shared<StandardListModel>();
}

void ComboBox::OnItemShowablePaintBegin() {
	is_combo_open_ = Drawer::ComboBox(label_, model_, &cur_idx_, flags(), size());
}

void ComboBox::OnUpdate() {
	AbstractMinimumControl::OnUpdate();
	if (cur_idx_ != prev_idx_) {
		Emit(on_current_changed_, cur_idx_, prev_idx_);
	}
	prev_idx_ = cur_idx_;
}
}