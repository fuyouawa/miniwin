#pragma once
#include <fugui/widgets/base/abstract_control.h>
#include <string>

namespace fugui {
class InputText : public AbstractControl
{
public:
    InputText(Widget* parent, std::u8string_view label, std::u8string_view initial_text = u8"", bool show = true);

    void set_text(std::u8string_view text);
    std::u8string_view text() const;
    
protected:
    void PaintBegin() override;

private:
    std::u8string text_;
};
}
