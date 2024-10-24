#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class TextEdit : public Widget
{
public:
    TextEdit(Widget* parent, const String& initial_text, const String& right_label = u8"");
    ~TextEdit() override;

    const String& RightLabel() const;
    void SetRightLabel(const String& label);

    void SetPlainText(const String& text);
    const String& PlainText() const;

protected:
    void PaintBegin() override;

    _MW_IMPL
};
}
