#include <miniwin/widgets/base/abstract_control.h>

#include <imgui/imgui_internal.h>
#include <miniwin/core/imgui.h>
#include <miniwin/tools/scope_variable.h>

namespace miniwin {
class AbstractMinimumControl::Impl {
public:
	Impl() = default;

	ScopeVariable<Vector2D> position_sc_;
};

AbstractMinimumControl::AbstractMinimumControl() {
	impl_ = std::make_unique<Impl>();
}

AbstractMinimumControl::~AbstractMinimumControl() = default;

bool AbstractMinimumControl::Visible() const {
	//TODO ImGui::GetCurrentWindow
	return Widget::Visible() && !ImGui::GetCurrentWindow()->SkipItems;
}

Vector2D AbstractMinimumControl::Position() const {
	return impl_->position_sc_.cur_value();
}
void AbstractMinimumControl::SetPosition(const Vector2D& pos) {
	impl_->position_sc_.SetControl(pos);
}

void AbstractMinimumControl::PaintBegin(size_t index) {
	Widget::PaintBegin(index);

	impl_->position_sc_.Enter();

	if (impl_->position_sc_.HasChange()) {
		OnPositionChanged(impl_->position_sc_.cur_value(), impl_->position_sc_.prev_value());
		imgui::SetCursorPos(impl_->position_sc_.cur_value());
	}
	else {
		auto cur_pos = imgui::GetCursorPos();
		if (cur_pos != impl_->position_sc_.cur_value()) {
			OnPositionChanged(cur_pos, impl_->position_sc_.cur_value());
			impl_->position_sc_.SetValueDirectly(cur_pos);
		}
	}
}

void AbstractMinimumControl::PaintEnd(size_t index) {
	impl_->position_sc_.Exit();

	Widget::PaintEnd(index);
}

AbstractControl::AbstractControl() {}

String AbstractControl::Text() const {
	return Name();
}

void AbstractControl::SetText(const String& text, bool adjust_size) {
	auto prev = Name();
	SetName(text);
	OnTextChanged(text, std::move(prev));
}
}
