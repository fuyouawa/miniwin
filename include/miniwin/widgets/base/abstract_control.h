#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class AbstractControl : public Widget
{
public:
	AbstractControl(Widget* parent, std::u8string_view text);
    ~AbstractControl() override;

    std::u8string_view Text() const;
    void SetText(std::u8string_view text);

    bool Visible() const override;

protected:
    void PaintBegin() override;
    void PaintEnd() override;

    _MW_IMPL
};
}
