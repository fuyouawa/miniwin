#include <mvcgui/widgets/widget/base/abstract_button.h>

namespace mvcgui {
AbstractButton::AbstractButton(Widget* const parent, std::u8string_view label, bool show)
	: AbstractMinimumControl{ parent, label, show },
	cur_checked_{ false },
	prev_checked_{ false }
{
}

void AbstractButton::OnUpdate() {
	AbstractMinimumControl::OnUpdate();
	if (cur_checked_ != prev_checked_) {
		if (cur_checked_)
			Emit(on_clicked_);
		Emit(on_toggled_, cur_checked_);
	}
	prev_checked_ = cur_checked_;
}
}