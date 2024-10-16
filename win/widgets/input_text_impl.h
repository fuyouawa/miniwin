#pragma once
#include <miniwin/widgets/input_text.h>
#include <string>

namespace miniwin {
class InputText::Impl {
public:
    Impl(InputText* owner);

    InputText* owner_;
    std::u8string text_;
    InputTextFlags flags_ = InputTextFlags::kNone;
};
}
