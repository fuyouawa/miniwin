#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class CheckBox : public AbstractTextualControl
{
public:
	CheckBox(Widget* parent, const String& label);

    void SetChecked(bool b);

	MW_SIGNAL(OnToggled, (bool) checked)

protected:
	void PaintBegin() override;
	void PaintEnd() override;

private:
	void SetSize(const Vector2D& size) override;

	_MW_IMPL
};
}
