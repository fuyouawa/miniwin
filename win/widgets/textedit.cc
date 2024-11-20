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

TextEdit::TextEdit() {
	impl_ = std::make_unique<Impl>(this);
}

TextEdit::~TextEdit() {}

const String& TextEdit::RightLabel() const {
	return impl_->right_label_;
}

void TextEdit::SetRightLabel(const String& label) {
	impl_->right_label_ = label;
}

void TextEdit::SetPlainText(const String& text) {
	impl_->text_buffer_ = text;
}

const String& TextEdit::PlainText() const {
	return impl_->text_buffer_;
}

void TextEdit::Awake() {
	AbstractMinimumControl::Awake();
	EnableFlags(imgui::kInputTextCallbackEdit
	            | imgui::kInputTextCallbackCharFilter, true);
}

wchar_t TextEdit::OnFilterInputChar(wchar_t ch) {
	return ch;
}

void TextEdit::PaintBegin(size_t index) {
	AbstractMinimumControl::PaintBegin(index);

	imgui::InputText(RightLabel(), &impl_->text_buffer_, Flags(), Size(), [this](imgui::InputTextCallbackData data) {
		switch (data.EventFlag()) {
		case imgui::kInputTextCallbackEdit:
			OnTextChanged();
			break;
		case imgui::kInputTextCallbackCharFilter: {
			auto ch = OnFilterInputChar(data.InputChar());
			data.SetInputChar(ch);
			break;
		}
		default:
			break;
		}
		return true;
	});
}
}
