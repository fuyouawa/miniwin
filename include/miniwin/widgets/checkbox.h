#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class CheckBox : public AbstractControl
{
public:
	CheckBox(Widget* parent, const String& label);

    void SetChecked(bool b);

	MW_SIGNAL(OnToggled, (bool) checked)

protected:
	void PaintBegin() override;
	void PaintEnd() override;

	_MW_IMPL
};
}
