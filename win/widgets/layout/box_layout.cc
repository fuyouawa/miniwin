#include <miniwin/widgets/layout/box_layout.h>

#include <miniwin/core/imgui.h>
#include <miniwin/tools/mathf.h>
#include "win/tools/debug.h"

namespace miniwin {
class BoxLayout::Impl {
public:
	Impl(BoxLayout* owner) : owner_(owner) {
	}

	BoxLayout* owner_;
	float spacing_ = 0;
	float alignment_ = 0;
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

float BoxLayout::Alignment() const {
	return impl_->alignment_;
}

void BoxLayout::SetAlignment(float alignment) {
	impl_->alignment_ = alignment;
}


HBoxLayout::HBoxLayout() {
	SetSpacing(imgui::style::ItemSpacing().x());
}

float HBoxLayout::TotalWidth() const {
	float width = 0;
	for (auto& w : Widgets()) {
		width += w->CalcSize().x() + Spacing();
	}
	return width;
}

void HBoxLayout::OnLayoutWidgetBegin(const SharedWidget& widget, size_t index) {
	BoxLayout::OnLayoutWidgetBegin(widget, index);

	if (index == 0) {
		auto avail = imgui::GetContentRegionAvail().x();
		auto width = TotalWidth();
		auto off = (avail - width) * Alignment();
		if (off > 0)
			imgui::SetCursorPosX(imgui::GetCursorPosX() + off);
	}

	if (index != 0) {
		imgui::SameLine(0, Spacing());
	}
}

VBoxLayout::VBoxLayout() {
	SetSpacing(imgui::style::ItemSpacing().y());
}

void VBoxLayout::OnLayoutWidgetBegin(const SharedWidget& widget, size_t index) {
	BoxLayout::OnLayoutWidgetBegin(widget, index);

	if (index != 0) {
		imgui::Dummy({0, Spacing()});
	}
}
}
