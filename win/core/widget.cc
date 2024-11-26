#include <win/core/widget_impl.h>

#include <format>

#include <miniwin/core/widget.h>
#include <miniwin/tools/vector2d.h>
#include <miniwin/tools/scope_variable.h>
#include <miniwin/core/platform_window.h>
#include <miniwin/widgets/window.h>

#include "object_impl.h"
#include "widgets_driver.h"
#include "miniwin/core/application.h"
#include "win/tools/debug.h"

namespace miniwin {
Widget::Widget() {
	impl_ = std::make_unique<Impl>(this);
}

Widget::~Widget() {}

void Widget::Close() {
	impl_->Close();
}

bool Widget::IsWidget() const {
	return true;
}

bool Widget::IsWindow() const {
	return false;
}

bool Widget::IsControl() const {
	return false;
}

SharedWindow Widget::OwnerWindow() const {
	return impl_->OwnerWindow();
}

SharedWidget Widget::WidgetParent() const {
	return impl_->WidgetParent();
}

void Widget::SetWidgetParent(const SharedWidget& parent) {
	if (parent) {
		if (!parent->IsWidget()) {
			MW_THROW_EX(std::invalid_argument, "The parent of a widget must also be a widget");
		}
		auto w = std::dynamic_pointer_cast<Widget>(parent);

		Invoke([self = shared_from_this(), parent]() {
			self->SetParent(parent);
		}, InvokeType::kEarlyQueued);
	}
	else {
		if (!IsWindow()) {
			MW_THROW_EX(std::invalid_argument, "The parent of a widget cannot be null");
		}

		Invoke([self = shared_from_this()]() {
			self->SetParent(nullptr);
		}, InvokeType::kEarlyQueued);
	}
}

List<SharedWidget> Widget::WidgetChildren() const {
	List<SharedWidget> total;
	for (auto& c : Children()) {
		if (c->IsWidget()) {
			auto w = std::dynamic_pointer_cast<Widget>(c);
			MW_ASSERT_X(w);
			total.PushBack(std::move(w));
		}
	}
	return total;
}

void Widget::SetEnable(bool b) {
	impl_->SetEnable(b);
}

bool Widget::IsStarted() const {
	return impl_->started_;
}

bool Widget::IsUpdated() const {
	return impl_->updated_;
}

void Widget::SetWidth(float width) {
	auto tmp = Size();
	tmp.set_x(width);
	SetSize(tmp);
}

void Widget::SetHeight(float height) {
	auto tmp = Size();
	tmp.set_y(height);
	SetSize(tmp);
}

float Widget::Alpha() const {
	return impl_->alpha_;
}

float Widget::BgAlpha() const {
	return impl_->bg_alpha_;
}

void Widget::SetAlpha(float alpha) {
	impl_->alpha_ = alpha;
}

void Widget::SetBgAlpha(float alpha) {
	impl_->bg_alpha_ = alpha;
}

WidgetId Widget::Id() const {
	return impl_->id_;
}

bool Widget::Enabled() const {
	return impl_->Enabled();
}

bool Widget::Visible() const {
	return impl_->Visible() && !Orphaned();
}

void Widget::SetVisible(bool b) {
	impl_->SetVisible(b);
}

FlagsType Widget::GetDrawFlags() const {
	return impl_->draw_flags_;
}

void Widget::SetDrawFlags(FlagsType flags) {
	impl_->draw_flags_ = flags;
}

bool Widget::Invoke(std::function<void()> func, InvokeType invoke_type) const {
	invoke_type = invoke_type == InvokeType::kAuto ? InvokeType::kQueued : invoke_type;

	switch (invoke_type) {
	case InvokeType::kDirect:
		func();
		return true;
	case InvokeType::kQueued:
		impl_->PushPendingFunctor(std::move(func));
		return true;
	case InvokeType::kEarlyQueued: {
		Application::Instance().PushPendingFunctor(std::move(func));
		return true;
	}
	}
	MW_ASSERT_X(false);
	return false;
}

void Widget::Initialize(const SharedObject& parent) {
	if (parent) {
		if (!parent->IsWidget()) {
			MW_THROW_EX(std::invalid_argument, "The parent of a widget must also be a widget");
		}
		auto w = std::dynamic_pointer_cast<Widget>(parent);
		SetWidgetParent(w);
	}
	else {
		if (!IsWindow()) {
			MW_THROW_EX(std::invalid_argument, "The parent of a widget cannot be null");
		}
		SetWidgetParent(nullptr);
	}

	Awake();
}

void Widget::Awake() {}

void Widget::Start() {
	MW_ASSERT_X(!impl_->started_);
	impl_->started_ = true;
}

bool Widget::IsInUiThread() const {
	return std::this_thread::get_id() == Application::Instance().ThreadId();
}

void Widget::Show() {
	SetVisible(true);
}

void Widget::Hide() {
	SetVisible(false);
}

void Widget::PreparePaint() {
	impl_->DoPendingFunctors();
}

void Widget::PaintBegin(size_t index) {
	impl_->PaintBegin();
}

void Widget::PaintEnd(size_t index) {
	impl_->PaintEnd();
}

void Widget::SetParent(const SharedObject& parent) const {
	if (parent) {
		MW_ASSERT_X(parent->IsWidget());
	}
	Object::SetParent(parent);
}
}
