#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class Button : public AbstractControl
{
public:
	Button(Widget* parent, std::u8string_view text);

	Vector2 Size() const override;
	void SetSize(const Vector2& size) override;

	MW_SIGNAL(OnClicked)

protected:
	void PaintBegin() override;

	_MW_IMPL
};
}
