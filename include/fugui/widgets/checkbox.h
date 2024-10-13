#pragma once
#include <fugui/widgets/base/abstract_button.h>

namespace fugui {
class CheckBox : public AbstractButton
{
public:
	CheckBox(Widget* parent, std::u8string_view label, bool show = true);

    void set_checked(bool b);

protected:
	void PaintBegin() override;
};
}
