#pragma once
#include <miniwin/widgets/layout/box_layout.h>

namespace miniwin {
class BoxLayout::Impl {
public:
	Impl(BoxLayout* owner);

	BoxLayout* owner_;
	float spacing_ = 0;
};
}
