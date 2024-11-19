#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class AbstractMinimumControl : public Widget {
	MW_OBJECT
public:
	AbstractMinimumControl();
	~AbstractMinimumControl() override;

	Vector2D CalcSize() const override;
	bool Visible() const override;

protected:
	void PaintBegin(size_t index) override;
	void PaintEnd(size_t index) override;

	_MW_IMPL
};


class AbstractControl : public AbstractMinimumControl {
	MW_OBJECT
public:
	AbstractControl();

	String Text() const;
	void SetText(const String& text);

	Vector2D CalcSize() const override;

	MW_SIGNAL(OnTextChanged, (String) text, (String) prev_text)
};
}
