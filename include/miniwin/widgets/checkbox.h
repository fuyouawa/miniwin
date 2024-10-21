#pragma once
#include <miniwin/widgets/base/abstract_button.h>

namespace miniwin {
class CheckBox : public AbstractButton
{
public:
	CheckBox(Widget* parent, std::u8string_view label);

    void SetChecked(bool b);

protected:
	void PaintBegin() override;
};
}
