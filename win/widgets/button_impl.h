#pragma once
#include <miniwin/widgets/button.h>

namespace miniwin {
class Button::Impl
{
public:
	Impl(Button* owner);

	Button* owner_;
};
}
