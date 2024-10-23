#include "textedit_impl.h"

#include <miniwin/core/imgui_helper.h>


namespace miniwin {
TextEdit::TextEdit(Widget* const parent, std::u8string_view initial_text, std::u8string_view right_label)
	: Widget{ parent, u8"TextEdit" }
{
    impl_ = std::make_unique<Impl>(this);
    SetPlainText(initial_text);
    SetRightLabel(right_label);
}

TextEdit::~TextEdit()
{
}

std::u8string_view TextEdit::RightLabel() const
{
    return impl_->right_label_;
}

void TextEdit::SetRightLabel(std::u8string_view label)
{
    impl_->right_label_ = label;
}

void TextEdit::SetPlainText(std::u8string_view text)
{
    impl_->text_buffer_ = text;
}

std::u8string_view TextEdit::PlainText() const
{
    return impl_->text_buffer_;
}

void TextEdit::PaintBegin() {
    Widget::PaintBegin();
	ImGuiHelper::InputText(RightLabel(), &impl_->text_buffer_);
}
}
