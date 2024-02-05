#include <mvcgui/widgets/widget/input_text.h>
#include <mvcgui/core/drawer.h>
#include <mvcgui/tools/algorithm.h>

namespace mvcgui {
InputText::InputText(Widget* const parent, std::u8string_view label, bool show, size_t capacity)
	: AbstractMinimumControl{ parent, label, show },
	text_buf_(capacity)
{
}

void InputText::set_text(std::u8string_view text)
{
	if (text_buf_.size() <= text.size()) {
		std::copy(text.begin(), text.begin() + text_buf_.size(), text_buf_.begin());
	}
	else {
		std::copy(text.begin(), text.end(), text_buf_.begin());
	}
}

void InputText::OnItemShowablePaintBegin() {
	Drawer::InputText(label_, text_buf_, [this](auto& data) {
		return 0;
	}, flags_, size_);
}
}