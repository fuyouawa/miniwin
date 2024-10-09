#pragma once
#include <fugui/widgets/widget/base/abstract_control.h>

namespace fugui {
class AbstractButton : public AbstractMinimumControl
{
public:
	AbstractButton(Widget* const parent, std::u8string_view label, bool show);

	bool checked() const { return cur_checked_; }

	Signal<> on_clicked_;
	Signal<bool> on_toggled_;

protected:
	void OnUpdate() override;

	bool cur_checked_;
	bool prev_checked_;
};
}