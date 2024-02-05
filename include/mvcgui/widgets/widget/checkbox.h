#pragma once
#include <mvcgui/widgets/widget/base/abstract_button.h>

namespace mvcgui {
class CheckBox : public AbstractButton
{
public:
	CheckBox(Widget* const parent, std::u8string_view label, bool show = true);

	void set_checked(bool b) { cur_checked_ = b; }

protected:
	void OnItemShowablePaintBegin() override;
};
}