#pragma once
#include <miniwin/widgets/button.h>

namespace miniwin {
class Button::Impl
{
public:
	Impl(Button* owner);

	Button* owner_;
	std::optional<Vector2D> size_to_set_;
};
}
