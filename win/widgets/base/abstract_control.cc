#include <miniwin/widgets/base/abstract_control.h>

#include <imgui/imgui_internal.h>
#include <miniwin/core/imgui.h>
#include <miniwin/tools/scope_variable.h>

#include "win/tools/debug.h"

namespace miniwin {
class AbstractControl::Impl {
public:
	Impl() = default;

	Vector2D position_to_set_;
	Vector2D really_pos_;
	Vector2D origin_pos_;
	bool is_relative_ = false;
};

AbstractControl::AbstractControl() {
	impl_ = std::make_unique<Impl>();
}

AbstractControl::~AbstractControl() = default;

bool AbstractControl::Visible() const {
	//TODO ImGui::GetCurrentWindow
	return Widget::Visible() && !ImGui::GetCurrentWindow()->SkipItems;
}

bool AbstractControl::IsControl() const {
	return true;
}

Vector2D AbstractControl::Position() const {
	return impl_->really_pos_;
}

void AbstractControl::SetPosition(const Vector2D& pos) {
	impl_->position_to_set_ = pos;
	impl_->is_relative_ = false;
}

Vector2D AbstractControl::RelativePosition() const {
	if (impl_->is_relative_)
		return impl_->position_to_set_;

	return impl_->really_pos_ - impl_->origin_pos_;
}

void AbstractControl::SetRelativePosition(const Vector2D& pos) {
	impl_->position_to_set_ = pos;
	impl_->is_relative_ = true;
}

void AbstractControl::SetRelativePositionX(float x) {
	auto p = RelativePosition();
	p.set_x(x);
	SetRelativePosition(p);
}

void AbstractControl::SetRelativePositionY(float y) {
	auto p = RelativePosition();
	p.set_y(y);
	SetRelativePosition(p);
}

void AbstractControl::PaintBegin(size_t index) {
	Widget::PaintBegin(index);

	impl_->origin_pos_ = imgui::GetCursorPos();

	bool is_custom_pos = impl_->position_to_set_ != Vector2D::kZero;
	if (is_custom_pos) {
		auto target_pos = impl_->position_to_set_;
		if (impl_->is_relative_) {
			target_pos += impl_->origin_pos_;
		}
		imgui::SetCursorPos(target_pos);
	}

	auto cur_pos = imgui::GetCursorPos();
	if (cur_pos != impl_->really_pos_) {
		if (IsUpdated()) {
			OnPositionChanged(cur_pos, impl_->really_pos_);
		}
		else {
			// 如果是第一次更新前，并且是自定义位置，则依然发送信号
			if (is_custom_pos) {
				OnPositionChanged(cur_pos, impl_->origin_pos_);
			}
		}
		impl_->really_pos_ = cur_pos;
	}
}

void AbstractControl::PaintEnd(size_t index) {
	Widget::PaintEnd(index);
}
}
