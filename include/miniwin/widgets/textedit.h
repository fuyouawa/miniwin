#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class TextEdit : public AbstractControl
{
public:
    TextEdit(Widget* parent, std::u8string_view label, std::u8string_view initial_text = u8"");
    ~TextEdit() override;

    void set_text(std::u8string_view text);
    std::u8string_view text() const;

    InputTextFlags flags() const;
    void set_flags(InputTextFlags flags) const;
    
protected:
    void PaintBegin() override;

    _MW_IMPL
};
}
