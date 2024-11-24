#include <miniwin/widgets/layout/box_layout.h>

#include <miniwin/core/imgui.h>
#include <miniwin/tools/mathf.h>
#include "win/tools/debug.h"

namespace miniwin {
class BoxLayout::Impl {
public:
	struct WidgetItem {
		WeakWidget widget;
		float spacing = 0;
	};

	Impl(BoxLayout* owner) : owner_(owner) {
	}

	WidgetItem& GetItemWithClear(const SharedWidget& widget) {
		MW_ASSERT_X(widget);
		if (items_.size() > 10) {
			items_.EraseIf([](const WidgetItem& i) { return !!i.widget.lock(); });
		}
		auto i = items_.FindIf([&widget](const WidgetItem& i) { return i.widget.lock() == widget; });
		if (i.IsEnd()) {
			return items_.EmplaceBack(widget);
		}
		return *i;
	}

	BoxLayout* owner_;
	float spacing_ = 0;
	float alignment_ = 0;
	List<WidgetItem> items_;
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

float BoxLayout::AdditionSpacing(const SharedWidget& widget) const {
	return impl_->GetItemWithClear(widget).spacing;
}

void BoxLayout::SetAdditionSpacing(const SharedWidget& widget, float spacing) {
	impl_->GetItemWithClear(widget).spacing = spacing;
}


HBoxLayout::HBoxLayout() {
	SetSpacing(imgui::style::ItemSpacing().x());
}

float HBoxLayout::TotalWidth() const {
	float width = 0;
	for (auto& w : Widgets()) {
		width += w->Size().x() + Spacing() + AdditionSpacing(w);
	}
	return width;
}

void HBoxLayout::OnBeginLayout() {
	BoxLayout::OnBeginLayout();

	auto avail = imgui::GetContentRegionAvail().x();
	auto width = TotalWidth();
	auto off = (avail - width) * Alignment();
	if (off > 0)
		imgui::SetCursorPosX(imgui::GetCursorPosX() + off);
}

void HBoxLayout::OnLayoutWidgetBegin(const SharedWidget& widget, size_t index) {
	BoxLayout::OnLayoutWidgetBegin(widget, index);

	if (index != 0) {
		imgui::SameLine(0, Spacing() + AdditionSpacing(WidgetByIndex(index - 1)));
	}
}

VBoxLayout::VBoxLayout() {
	SetSpacing(imgui::style::ItemSpacing().y());
}

float VBoxLayout::TotalHeight() const {
	float height = 0;
	for (auto& w : Widgets()) {
		height += w->Size().y() + Spacing() + AdditionSpacing(w);
	}
	return height;
}

void VBoxLayout::OnLayoutWidgetBegin(const SharedWidget& widget, size_t index) {
	BoxLayout::OnLayoutWidgetBegin(widget, index);

	if (index != 0) {
		imgui::Dummy({0, Spacing() + AdditionSpacing(widget) });
	}
}
}
