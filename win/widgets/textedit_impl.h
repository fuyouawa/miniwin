#pragma once
#include <miniwin/widgets/textedit.h>
#include <string>

namespace miniwin {
class TextEdit::Impl {
public:
    Impl(TextEdit* owner);

    TextEdit* owner_;
    std::u8string text_;
    InputTextFlags flags_ = InputTextFlags::kNone;
};
}
