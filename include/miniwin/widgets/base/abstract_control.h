#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class AbstractControl : public Widget
{
public:
	AbstractControl(Widget* parent, const String& name);
    ~AbstractControl() override;

    bool Visible() const override;

protected:
    void PaintBegin() override;
    void PaintEnd() override;
};


class AbstractTextualControl : public AbstractControl
{
public:
    AbstractTextualControl(Widget* parent, const String& text);

    const String& Text() const;
    void SetText(const String& text);

    MW_SIGNAL(OnTextChanged, (String) text, (String) prev_text)
};
}
