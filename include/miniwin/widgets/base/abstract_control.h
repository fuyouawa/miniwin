#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class AbstractControl : public Widget
{
public:
	AbstractControl(Widget* parent, const String& text);
    ~AbstractControl() override;

    const String& Text() const;
    void SetText(const String& text);

    bool Visible() const override;

protected:
    void PaintBegin() override;
    void PaintEnd() override;

    _MW_IMPL
};
}
