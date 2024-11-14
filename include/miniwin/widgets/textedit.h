#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class TextEdit : public AbstractControl
{
public:
    TextEdit(Widget* parent, const String& initial_text = {}, const String& right_label = {});
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
