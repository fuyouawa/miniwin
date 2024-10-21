#include "textedit_impl.h"

#include <miniwin/core/imgui_helper.h>


namespace miniwin {
TextEdit::TextEdit(Widget* const parent, std::u8string_view label, std::u8string_view initial_text)
	: Widget{ parent, u8"TextEdit" }
{
    impl_ = std::make_unique<Impl>(this);
    SetPlainText(initial_text);
    SetLabel(label);
}

TextEdit::~TextEdit()
{
}

std::u8string_view TextEdit::Label() const
{
    return impl_->label_;
}

void TextEdit::SetLabel(std::u8string_view label)
{
    impl_->label_ = label;
}

void TextEdit::SetPlainText(std::u8string_view text)
{
    impl_->text_buffer_ = text;
}

std::u8string_view TextEdit::PlainText() const
{
    return impl_->text_buffer_;
}

InputTextFlags TextEdit::Flags() const
{
    return impl_->flags_;
}

inline void TextEdit::SetFlags(InputTextFlags flags) const
{
    impl_->flags_ = flags;
}

void TextEdit::PaintBegin() {
    Widget::PaintBegin();
	ImGuiHelper::InputText(Label(), &impl_->text_buffer_, Flags(), Size());
}
}
