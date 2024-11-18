#include <win/core/widget_impl.h>

#include <format>

#include <miniwin/core/widget.h>
#include <miniwin/tools/vector2d.h>
#include <miniwin/tools/scope_variable.h>

#include <miniwin/widgets/window.h>
#include <miniwin/core/application.h>
#include "object_impl.h"
#include "widgets_driver.h"
#include "win/tools/debug.h"

namespace miniwin {
Widget::Widget() {
	impl_ = std::make_unique<Impl>(this);
	Object::impl_->is_widget_ = true;
}

Widget::~Widget() {}

void Widget::Close() {
	impl_->Close();
}

bool Widget::IsWindow() const {
	return impl_->is_window_;
}

SharedWindow Widget::OwnerWindow() const {
	return impl_->OwnerWindow();
}

SharedWidget Widget::WidgetParent() const {
	return impl_->WidgetParent();
}

void Widget::SetWidgetParent(const SharedWidget& parent) {
	impl_->SetWidgetParent(parent);
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


Vector2D Widget::Size() const {
	return impl_->size_sc_.cur_value();
}

void Widget::SetSize(const Vector2D& size) {
	impl_->size_sc_.SetControl(size);
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

Vector2D Widget::Position() const {
	return impl_->pos_sc_.cur_value();
}

void Widget::SetPosition(const Vector2D& pos) {
	impl_->pos_sc_.SetControl(pos);
}

WidgetId Widget::Id() const {
	return impl_->id_;
}

bool Widget::Enabled() const {
	return impl_->Enabled();
}

bool Widget::Visible() const {
	return impl_->Visible();
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

void Widget::Invoke(std::function<void()> func, InvokeType invoke_type) const {
	if (IsInUiThread()
		&& invoke_type == InvokeType::kAuto
		&& Application::instance()->IsExecuting()) {
		invoke_type = InvokeType::kDirect;
	}
	else {
		invoke_type = invoke_type == InvokeType::kAuto ? InvokeType::kQueued : invoke_type;
	}

	switch (invoke_type) {
	case InvokeType::kDirect:
		func();
		break;
	case InvokeType::kQueued:
		impl_->PushPendingFunctor(std::move(func));
		break;
	default:
		MW_ASSERT_X(invoke_type == InvokeType::kDirect || invoke_type == InvokeType::kQueued);
		break;
	}
}

void Widget::Initialize(const SharedObject& parent) {
	Object::Initialize(parent);
	if (parent)
		MW_ASSERT(parent->IsWidget(), "The parent of a widget must also be a widget");
	Awake();
}

void Widget::Awake() {
}

void Widget::Start() {
	MW_ASSERT_X(!impl_->started_);
	impl_->started_ = true;
}

bool Widget::IsInUiThread() {
	return std::this_thread::get_id() == WidgetsDriver::Instance().UiThreadId();
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

void Widget::PaintBegin() {
	impl_->PaintBegin();
}

void Widget::PaintEnd() {
	impl_->PaintEnd();
}

void Widget::OnBeforePaintChild(size_t child_index) {}

void Widget::OnAfterPaintChild(size_t child_index) {}
}
