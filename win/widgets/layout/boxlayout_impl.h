#pragma once
#include <miniwin/widgets/layout/boxlayout.h>

namespace miniwin {
class BoxLayout::Impl {
public:
	Impl(BoxLayout* owner);

	BoxLayout* owner_;
	size_t spacing_ = 0;
};
}
