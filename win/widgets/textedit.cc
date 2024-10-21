#include "textedit_impl.h"

#include <miniwin/core/imgui_helper.h>


namespace miniwin {
TextEdit::TextEdit(Widget* const parent, std::u8string_view label, std::u8string_view initial_text)
	: AbstractControl{ parent, label }
{
    impl_ = std::make_unique<Impl>(this);
    set_text(initial_text);
}

TextEdit::~TextEdit()
{
}

void TextEdit::set_text(std::u8string_view text)
{
    impl_->text_ = text;
}

std::u8string_view TextEdit::text() const
{
    return impl_->text_;
}

InputTextFlags TextEdit::flags() const
{
    return impl_->flags_;
}

inline void TextEdit::set_flags(InputTextFlags flags) const
{
    impl_->flags_ = flags;
}

void TextEdit::PaintBegin() {
    AbstractControl::PaintBegin();
	ImGuiHelper::InputText(label(), &impl_->text_, flags(), size());
}
}
