#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class AbstractMinimumControl : public Widget {
	MW_OBJECT
public:
	AbstractMinimumControl();
	~AbstractMinimumControl() override;

	bool Visible() const override;

	Vector2D Position() const override;
	void SetPosition(const Vector2D& pos) override;

protected:
	void PaintBegin(size_t index) override;
	void PaintEnd(size_t index) override;

	_MW_IMPL
};


class AbstractControl : public AbstractMinimumControl {
	MW_OBJECT
public:
	AbstractControl();

	virtual String Text() const;
	virtual void SetText(const String& text, bool adjust_size = true);

	MW_SIGNAL(OnTextChanged, (String) text, (String) prev_text)
};
}
