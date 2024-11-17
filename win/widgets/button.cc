#include <miniwin/widgets/button.h>

#include <miniwin/core/imgui.h>

namespace miniwin {
class Button::Impl {
public:
	Impl(Button* owner) : owner_(owner) {}

	Button* owner_;
};

Button::Button() {
	impl_ = std::make_unique<Impl>(this);
}

Button::~Button() {}

void Button::PaintBegin() {
	AbstractTextualControl::PaintBegin();
	if (imgui::Button(Text(), Size())) {
		OnClicked();
	}
}
}
