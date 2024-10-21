#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class TextEdit : public Widget
{
public:
    TextEdit(Widget* parent, std::u8string_view label, std::u8string_view initial_text = u8"");
    ~TextEdit() override;

    std::u8string_view Label() const;
    void SetLabel(std::u8string_view label);

    void SetPlainText(std::u8string_view text);
    std::u8string_view PlainText() const;

    InputTextFlags Flags() const;
    void SetFlags(InputTextFlags flags) const;
    
protected:
    void PaintBegin() override;

    _MW_IMPL
};
}
