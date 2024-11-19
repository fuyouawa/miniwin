#include <miniwin/widgets/base/abstract_control.h>

#include <imgui/imgui_internal.h>
#include <miniwin/core/imgui.h>

namespace miniwin {
class AbstractMinimumControl::Impl {
public:
	Impl() {}

	Vector2D calc_size_;
};

AbstractMinimumControl::AbstractMinimumControl() {
	impl_ = std::make_unique<Impl>();
}

AbstractMinimumControl::~AbstractMinimumControl() {}

Vector2D AbstractMinimumControl::CalcSize() const {
	return impl_->calc_size_;
}

bool AbstractMinimumControl::Visible() const {
	//TODO ImGui::GetCurrentWindow
	return Widget::Visible() && !ImGui::GetCurrentWindow()->SkipItems;
}

void AbstractMinimumControl::PaintBegin(size_t index) {
	Widget::PaintBegin(index);
}

void AbstractMinimumControl::PaintEnd(size_t index) {
	impl_->calc_size_ = imgui::GetItemRectSize();
	Widget::PaintEnd(index);
}

AbstractControl::AbstractControl() {}

String AbstractControl::Text() const {
	return Name();
}

void AbstractControl::SetText(const String& text) {
	auto prev = Name();
	SetName(text);
	OnTextChanged(text, std::move(prev));
}

Vector2D AbstractControl::CalcSize() const {
	auto s = AbstractMinimumControl::CalcSize();
	return s == Vector2D::kZero ? imgui::CalcTextSize(Text()) : s;
}
}
