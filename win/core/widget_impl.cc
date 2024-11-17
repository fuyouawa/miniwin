#include "widget_impl.h"

#include <ranges>

#include <miniwin/widgets/window.h>
#include <miniwin/core/imgui.h>

#include "object_impl.h"
#include "widgets_driver.h"
#include "win/tools/debug.h"

namespace miniwin {
Widget::Impl::Impl(Widget* owner)
	: owner_(owner) {
	id_ = WidgetsDriver::instance().AllocId();
}

Widget::Impl::~Impl() {
	WidgetsDriver::instance().RecycleId(id_);
}

void Widget::Impl::Close() {
	owner_->Object::impl_->orphaned_ = true;
	auto p = WidgetParent();
	if (p) {
		p->Object::impl_->dirty_ = true;
	}
	owner_->OnClosed();
}

void Widget::Impl::PaintBegin() {
	enable_sc_.Enter();
	size_sc_.Enter();
	pos_sc_.Enter();

	if (enable_sc_.HasChange()) {
		owner_->OnEnableChanged(enable_sc_.cur_value());
	}

	if (size_sc_.HasChange()) {
		owner_->OnSizeChanged(size_sc_.cur_value(), size_sc_.prev_value());
	}

	if (pos_sc_.HasChange()) {
		owner_->OnPositionChanged(pos_sc_.cur_value(), pos_sc_.prev_value());
	}

	imgui::BeginDisabled(!enable_sc_.cur_value());

	// 如果是window，需要自己管理id
	if (!is_window_) {
		imgui::PushID(owner_->Id());
	}
}

void Widget::Impl::PaintEnd() {
	if (!is_window_) {
		imgui::PopID();
	}
	imgui::EndDisabled();
	enable_sc_.Exit();
	size_sc_.Exit();
	pos_sc_.Exit();
}

void Widget::Impl::Awake() {
	MW_ASSERT_X(!awaked_);
	awaked_ = true;
}

SharedWindow Widget::Impl::OwnerWindow() const {
	if (is_window_) {
		auto w = std::dynamic_pointer_cast<Window>(owner_->shared_from_this());
		MW_ASSERT_X(w);
		return w;
	}
	auto p = WidgetParent();
	if (p) {
		return p->impl_->OwnerWindow();
	}
	return {};
}

SharedWidget Widget::Impl::WidgetParent() const {
	if (auto p = owner_->Parent()) {
		return std::dynamic_pointer_cast<Widget>(p);
	}
	return {};
}

void Widget::Impl::SetWidgetParent(const SharedWidget& parent) {
	if (parent == WidgetParent())
		return;
	WidgetsDriver::instance().PushPendingFunctor([this, parent] {
		owner_->Object::SetParent(parent);
	});
}


void Widget::Impl::PushPendingFunctor(std::function<void()>&& func) {
	std::lock_guard lk(pending_functors_mutex_);
	pending_functors_.EmplaceBack(std::move(func));
}

void Widget::Impl::DoPendingFunctors() {
	List<std::function<void()>> functors;
	{
		std::lock_guard lk(pending_functors_mutex_);
		functors.Swap(pending_functors_);
	}
	for (auto& f : functors) {
		f();
	}
	functors.Clear();
}

bool Widget::Impl::Visible() const {
	if (!visible_) {
		return false;
	}
	auto p = owner_->WidgetParent();
	if (!p) {
		return visible_;
	}
	return p->Visible();
}

void Widget::Impl::SetVisible(bool b) {
	auto v = visible_;
	visible_ = b;

	if (v != b) {
		owner_->OnVisbleChanged(visible_);
	}
}

bool Widget::Impl::Enabled() const {
	auto v = enable_sc_.cur_value();
	if (!v) {
		return false;
	}
	auto p = owner_->WidgetParent();
	if (!p) {
		return v;
	}
	return p->Enabled();
}

void Widget::Impl::SetEnable(bool b) {
	enable_sc_.SetControl(b);
}
}
