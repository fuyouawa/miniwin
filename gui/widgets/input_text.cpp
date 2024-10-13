#include <fugui/widgets/input_text.h>
#include <gui/core/drawer.h>

namespace fugui {
InputText::InputText(Widget* const parent, std::u8string_view label, bool show, size_t capacity)
	: AbstractControl{ parent, label, show },
	text_buf_(capacity)
{
}

void InputText::set_text(std::u8string_view text)
{
	if (text_buf_.size() <= text.size()) {
        text_buf_.resize(text_buf_.size());
	}
    std::ranges::copy(text, text_buf_.begin());
}

void InputText::PaintBegin() {
    AbstractControl::PaintBegin();
	Drawer::InputText(label(), text_buf_, [this](auto& data) {
		return 0;
	}, flags(), size());
}
}
