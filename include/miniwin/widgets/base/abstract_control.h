#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class AbstractControl : public Widget {
	MW_OBJECT
public:
	AbstractControl();
	~AbstractControl() override;

	bool Visible() const override;

	void Initialize(const SharedObject& parent) override;
protected:
	void PaintBegin() override;
	void PaintEnd() override;
};


class AbstractTextualControl : public AbstractControl {
	MW_OBJECT
public:
	AbstractTextualControl();

	String Text() const;
	void SetText(const String& text);

	MW_SIGNAL(OnTextChanged, (String) text, (String) prev_text)
};
}
