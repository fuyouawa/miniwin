#include <miniwin/widgets/text_edit.h>

#include <miniwin/core/imgui.h>

namespace miniwin {
class TextEdit::Impl {
public:
	Impl(TextEdit* owner) : owner_(owner) {}

	TextEdit* owner_;
	String text_buffer_;
	String right_label_;
	size_t max_len_ = std::numeric_limits<uint64_t>::max();
};

TextEdit::TextEdit() {
	impl_ = std::make_unique<Impl>(this);
}

TextEdit::~TextEdit() {}

String TextEdit::RightLabel() const {
	return impl_->right_label_;
}

void TextEdit::SetRightLabel(const String& label) {
	impl_->right_label_ = label;
}

void TextEdit::SetTextBuffer(const String& text) {
	impl_->text_buffer_ = text;
}

const String& TextEdit::TextBuffer() const {
	return impl_->text_buffer_;
}

String& TextEdit::TextBuffer() {
	return impl_->text_buffer_;
}

void TextEdit::Awake() {
	AbstractControl::Awake();
	EnableFlags(imgui::kInputTextCallbackCharFilter | imgui::kInputTextCallbackResize, true);
}

bool TextEdit::FilterInput(FilterInputArgs& args) {
	if (args.cur_length > impl_->max_len_) {
		return false;
	}
	return true;
}

size_t TextEdit::MaxLength() const {
	return impl_->max_len_;
}

void TextEdit::SetMaxLength(size_t len) {
	impl_->max_len_ = len;
}

//TODO TextEdit::Size
Vector2D TextEdit::Size() const {
	return {};
}

void TextEdit::SetSize(const Vector2D& size) {
	
}

void TextEdit::PaintBegin(size_t index) {
	AbstractControl::PaintBegin(index);

	bool changed = imgui::InputText(RightLabel(), &impl_->text_buffer_, Flags(), [this](imgui::InputTextCallbackData data) {
		auto args = FilterInputArgs(data.InputChar(), data.InputKey(), data.TextLength());

		switch (data.EventFlag()) {
		case imgui::kInputTextCallbackCharFilter: {
			if (!FilterInput(args))
				return false;
			data.SetInputChar(args.input_char);
			break;
		}
		default:
			break;
		}
		return true;
	});
	if (changed) {
		OnTextChanged();
	}
}
}
