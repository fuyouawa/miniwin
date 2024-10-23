#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class CheckBox : public AbstractControl
{
public:
	CheckBox(Widget* parent, std::u8string_view label);

    void SetChecked(bool b);

	MW_SIGNAL(OnToggled, (bool) checked)

protected:
	void PaintBegin() override;

	_MW_IMPL
};
}
