#include "box_layout_impl.h"

#include <miniwin/core/imgui.h>

#include "win/tools/debug.h"

namespace miniwin {
BoxLayout::BoxLayout(Widget* parent)
	: Layout(parent) {
	impl_ = std::make_unique<Impl>(this);
}

BoxLayout::~BoxLayout() {}

float BoxLayout::Spacing() const {
	return impl_->spacing_;
}

void BoxLayout::SetSpacing(float size) {
	impl_->spacing_ = size;
}

HBoxLayout::HBoxLayout(Widget* parent)
	: BoxLayout(parent) {}

void HBoxLayout::OnLayoutWidgetBegin(Widget* widget) {
	BoxLayout::OnLayoutWidgetBegin(widget);

	auto idx = IndexOfWidget(widget);
	MW_ASSERT_X(idx != static_cast<size_t>(-1));

	if (idx != 0) {
		imgui::SameLine(0, Spacing());
	}
}

VBoxLayout::VBoxLayout(Widget* parent)
	: BoxLayout(parent) {}

void VBoxLayout::OnLayoutWidgetBegin(Widget* widget) {
	BoxLayout::OnLayoutWidgetBegin(widget);

	auto idx = IndexOfWidget(widget);
	MW_ASSERT_X(idx != static_cast<size_t>(-1));

	if (idx != 0) {
		imgui::Dummy({0, Spacing()});
	}
}
}
