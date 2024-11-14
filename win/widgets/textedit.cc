#include <miniwin/widgets/textedit.h>

#include <miniwin/core/imgui.h>

namespace miniwin {
class TextEdit::Impl {
public:
    Impl(TextEdit* owner) : owner_(owner) {}

    TextEdit* owner_;
    String text_buffer_;
    String right_label_;
};

TextEdit::TextEdit(Widget* const parent, const String& initial_text, const String& right_label)
	: AbstractControl{ parent, "TextEdit" }
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
    AbstractControl::PaintBegin();
	imgui::InputText(RightLabel(), &impl_->text_buffer_, Flags(), Size());
}
}
