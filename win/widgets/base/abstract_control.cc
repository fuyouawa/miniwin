#include <miniwin/widgets/base/abstract_control.h>

#include <imgui/imgui_internal.h>
#include <miniwin/core/imgui.h>
#include <miniwin/tools/scope_variable.h>

#include "win/tools/debug.h"

namespace miniwin {
class AbstractControl::Impl {
public:
	Impl() = default;

	Vector2D GetPos(const Vector2D& pos) {
		switch (relative_to_) {
		case ControlRelativeTo::kWindow:
			return pos;
		case ControlRelativeTo::kCursor:
			return pos + imgui::GetCursorPos();
		}
		MW_ASSERT_X(false);
		return pos;
	}

	Vector2D position_to_set_;
	Vector2D really_pos_;
	Vector2D origin_pos_;
	ControlRelativeTo relative_to_ = ControlRelativeTo::kWindow;
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

Vector2D AbstractControl::Position(ControlRelativeTo relative) const {
	switch (relative) {
	case ControlRelativeTo::kWindow:
		return impl_->really_pos_;
	case ControlRelativeTo::kCursor: {
		if (impl_->relative_to_ == ControlRelativeTo::kCursor) {
			return impl_->position_to_set_;
		}
		return impl_->really_pos_ - impl_->origin_pos_;
	}
	}
	MW_ASSERT_X(false);
	return impl_->really_pos_;
}

void AbstractControl::SetPosition(const Vector2D& pos, ControlRelativeTo relative) {
	impl_->position_to_set_ = pos;
	impl_->relative_to_ = relative;
}

void AbstractControl::BeginUpdate(size_t index) {
	Widget::BeginUpdate(index);

	impl_->origin_pos_ = imgui::GetCursorPos();

	bool is_custom_pos = impl_->position_to_set_ != Vector2D::kZero;
	if (is_custom_pos) {
		imgui::SetCursorPos(impl_->GetPos(impl_->position_to_set_));
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

void AbstractControl::EndUpdate(size_t index) {
	Widget::EndUpdate(index);
}
}
