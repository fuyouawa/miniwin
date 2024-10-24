#include "textedit_impl.h"

#include <miniwin/core/imgui_helper.h>


namespace miniwin {
TextEdit::TextEdit(Widget* const parent, const String& initial_text, const String& right_label)
	: Widget{ parent, u8"TextEdit" }
{
    impl_ = std::make_unique<Impl>(this);
    SetPlainText(initial_text);
    SetRightLabel(right_label);
}

TextEdit::~TextEdit()
{
}

const String& TextEdit::RightLabel() const
{
    return impl_->right_label_;
}

void TextEdit::SetRightLabel(const String& label)
{
    impl_->right_label_ = label;
}

void TextEdit::SetPlainText(const String& text)
{
    impl_->text_buffer_ = text;
}

const String& TextEdit::PlainText() const
{
    return impl_->text_buffer_;
}

void TextEdit::PaintBegin() {
    Widget::PaintBegin();
	ImGuiHelper::InputText(RightLabel(), &impl_->text_buffer_);
}
}
