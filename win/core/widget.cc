#include <win/core/widget_impl.h>

#include <format>

#include <miniwin/core/widget.h>
#include <miniwin/tools/vector2d.h>
#include <miniwin/tools/scope_variable.h>

#include "object_impl.h"
#include "widgets_driver.h"
#include "miniwin/core/application.h"
#include "win/tools/debug.h"

namespace miniwin {
Widget::Widget(Widget* parent, const String& name, const String& id)
	: Object(parent, name) {
	impl_ = std::make_unique<Impl>(this);
	impl_->id_ = id;
	Object::impl_->is_widget_ = true;
}

Widget::~Widget() {
}

void Widget::Close() {
	impl_->Close();
}

Widget* Widget::WidgetParent() const {
	return impl_->WidgetParent();
}

void Widget::SetWidgetParent(Widget* parent) {
	impl_->SetWidgetParent(parent);
}

List<Widget*> Widget::WidgetChildren() const {
	List<Widget*> total;
	for (auto c : Children()) {
		if (c->IsWidget()) {
			auto w = dynamic_cast<Widget*>(c);
			MW_ASSERT_X(w != nullptr);
			total.PushBack(w);
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

Vector2D Widget::Position() const {
	return impl_->pos_sc_.cur_value();
}

void Widget::SetPosition(const Vector2D& pos) {
	impl_->pos_sc_.SetControl(pos);
}

const String& Widget::Id() const {
	return impl_->id_;
}

void Widget::SetId(const String& id) {
	impl_->id_ = id;
}

bool Widget::Orphaned() const {
	return impl_->orphaned_;
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

void Widget::Invoke(std::function<void()>&& func, InvokeType invoke_type) const {
	if (IsInUIThread()
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

bool Widget::IsInUIThread() {
	return std::this_thread::get_id() == WidgetsDriver::instance().UiThreadId();
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
