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

wchar_t TextEdit::FilterInputChar(const FilterInputCharArgs& args) {
	if (args.cur_length > impl_->max_len_) {
		return 0;
	}
	return args.input_char;
}

size_t TextEdit::MaxLength() const {
	return impl_->max_len_;
}

void TextEdit::SetMaxLength(size_t len) {
	impl_->max_len_ = len;
}

void TextEdit::PaintBegin(size_t index) {
	AbstractMinimumControl::PaintBegin(index);

	imgui::InputText(RightLabel(), &impl_->text_buffer_, Flags(), Size(), [this](imgui::InputTextCallbackData data) {
		switch (data.EventFlag()) {
		case imgui::kInputTextCallbackEdit:
			OnTextChanged();
			break;
		case imgui::kInputTextCallbackCharFilter: {
			auto ch = FilterInputChar({ data.InputChar(), data.TextLength() });
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
