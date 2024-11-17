#include <miniwin/widgets/layout/box_layout.h>

#include <miniwin/core/imgui.h>

#include "win/tools/debug.h"

namespace miniwin {
class BoxLayout::Impl {
public:
	Impl(BoxLayout* owner) : owner_(owner) {}

	BoxLayout* owner_;
	float spacing_ = 0;
};

BoxLayout::BoxLayout() {
	impl_ = std::make_unique<Impl>(this);
}

BoxLayout::~BoxLayout() {}

float BoxLayout::Spacing() const {
	return impl_->spacing_;
}

void BoxLayout::SetSpacing(float size) {
	impl_->spacing_ = size;
}

HBoxLayout::HBoxLayout() {}

void HBoxLayout::OnLayoutWidgetBegin(const SharedWidget& widget) {
	BoxLayout::OnLayoutWidgetBegin(widget);

	auto idx = IndexOfWidget(widget);
	MW_ASSERT_X(idx != static_cast<size_t>(-1));

	if (idx != 0) {
		imgui::SameLine(0, Spacing());
	}
}

VBoxLayout::VBoxLayout() {}

void VBoxLayout::OnLayoutWidgetBegin(const SharedWidget& widget) {
	BoxLayout::OnLayoutWidgetBegin(widget);

	auto idx = IndexOfWidget(widget);
	MW_ASSERT_X(idx != static_cast<size_t>(-1));

	if (idx != 0) {
		imgui::Dummy({0, Spacing()});
	}
}
}
