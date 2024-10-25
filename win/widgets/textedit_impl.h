#pragma once
#include <miniwin/widgets/textedit.h>

#include <string>

namespace miniwin {
class TextEdit::Impl {
public:
    Impl(TextEdit* owner);

    TextEdit* owner_;
    String text_buffer_;
    String right_label_;
};
}
