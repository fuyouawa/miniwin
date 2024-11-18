#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class AbstractMinimumControl : public Widget {
	MW_OBJECT
public:
	AbstractMinimumControl();
	~AbstractMinimumControl() override;

	bool Visible() const override;

protected:
	void PaintBegin() override;
	void PaintEnd() override;
};


class AbstractControl : public AbstractMinimumControl {
	MW_OBJECT
public:
	AbstractControl();

	String Text() const;
	void SetText(const String& text);

	MW_SIGNAL(OnTextChanged, (String) text, (String) prev_text)
};
}
