#pragma once
#include <fugui/widgets/base/abstract_control.h>

namespace fugui {
class InputText : public AbstractControl
{
public:
    InputText(Widget* const parent, std::u8string_view label, bool show = true, size_t capacity = 256);

    void set_text(std::u8string_view text);
    auto text() const { return std::u8string_view{text_buf_.data()}; }
    auto capacity() const { return text_buf_.size(); }
    void set_capaity(size_t c) { text_buf_.resize(c); }
    
protected:
    void PaintBegin() override;

private:
    std::vector<char8_t> text_buf_;
};
}
