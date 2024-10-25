#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class Button : public AbstractControl
{
public:
	Button(Widget* parent, const String& text);

	Vector2D Size() const override;
	void SetSize(const Vector2D& size) override;

	MW_SIGNAL(OnClicked)

protected:
	void PaintBegin() override;

	_MW_IMPL
};
}
