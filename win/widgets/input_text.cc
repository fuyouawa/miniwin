#include "win/widgets/input_text_impl.h"
#include <miniwin/core/imgui_helper.h>

namespace miniwin {
InputText::InputText(Widget* const parent, std::u8string_view label, std::u8string_view initial_text)
	: AbstractControl{ parent, label }
{
    impl_ = std::make_unique<Impl>(this);
    set_text(initial_text);
}

void InputText::set_text(std::u8string_view text)
{
    impl_->text_ = text;
}

std::u8string_view InputText::text() const
{
    return impl_->text_;
}

InputTextFlags InputText::flags() const
{
    return impl_->flags_;
}

inline void InputText::set_flags(InputTextFlags flags) const
{
    impl_->flags_ = flags;
}

void InputText::PaintBegin() {
    AbstractControl::PaintBegin();
	ImGuiHelper::InputText(label(), &impl_->text_, flags(), size());
}
}
