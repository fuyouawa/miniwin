#include "widgets_driver.h"

#include "object_impl.h"
#include "miniwin/core/application.h"
#include "miniwin/widgets/layout/layout.h"
#include "win/core/widget_impl.h"
#include "win/tools/debug.h"
#include "win/widgets/window_impl.h"

namespace miniwin {
WidgetsDriver& WidgetsDriver::instance() {
	static WidgetsDriver inst;
	static bool initialized = false;
	if (!initialized) {
		inst.ui_thread_id_ = std::this_thread::get_id();
		initialized = true;
	}
	return inst;
}

WidgetsDriver::~WidgetsDriver() {
	CloseAll();
}

void WidgetsDriver::Update() {
	Prepare();
	DoPending();
	CallUpdateEarly();
	for (auto& win : windows_) {
		if (!win->Orphaned() && win->Visible()) {
			UpdateRecursion(win, win->IsCollapsed());
		}
	}
}

void WidgetsDriver::Prepare() {
	{
		windows_.EraseIf([](auto w) {
			return w->Orphaned();
		});
	}
	for (auto& win : windows_) {
		MW_ASSERT_X(!win->Orphaned());

		// 因为只有Widget是有权限调用的，所以得转成Widget
		auto w = dynamic_cast<Widget*>(win.get());
		if (!w->impl_->awaked_) {
			w->Awake();
			w->impl_->awaked_ = true;
		}
		PrepareRecursion(win);
	}
}

void WidgetsDriver::CallUpdateEarly() const {
	for (auto& win : windows_) {
		CallUpdateEarlyRecursion(win);
	}
}

void WidgetsDriver::DoPending() {
	List<std::function<void()>> functors;
	{
		std::lock_guard lk(mutex_);
		functors.Swap(pending_functors_);
	}
	for (auto& f : functors) {
		f();
	}
	functors.Clear();
}

bool WidgetsDriver::IsDone() const {
	return windows_.empty() && pending_functors_.empty();
}

void WidgetsDriver::CloseAll() {
	PushPendingFunctor([this] {
		windows_.Clear();
	});
}

void WidgetsDriver::RegisterWindow(const SharedWindow& window) {
	PushPendingFunctor([window, this] {
		windows_.PushBack(window);
	});
}

std::thread::id WidgetsDriver::UiThreadId() const {
	return ui_thread_id_;
}

WidgetId WidgetsDriver::AllocId() {
	MW_ASSERT_X(cur_max_id_ < std::numeric_limits<WidgetId>::max());
	if (id_pool_seek_ > 0) {
		return id_pool_[--id_pool_seek_];
	}
	return cur_max_id_++;
}

bool WidgetsDriver::RecycleId(WidgetId id) {
	MW_ASSERT_X(id != 0);
	if (id_pool_seek_ < sizeof(id_pool_) / sizeof(WidgetId)) {
		id_pool_[id_pool_seek_++] = id;
		return true;
	}
	return false;
}

void WidgetsDriver::UpdateRecursion(const SharedWidget& widget, bool force_ignore_children) {
	if (!widget->Visible())
		return;

	auto ignore_self = (widget->GetDrawFlags() & Widget::kDrawIgnoreSelf) != 0;
	auto ignore_children = (widget->GetDrawFlags() & Widget::kDrawIgnoreChildren) != 0;

	if (!ignore_self) {
		if (widget->impl_->layout_)
			widget->impl_->layout_->OnLayoutWidgetBegin(widget);
		widget->PaintBegin();
	}

	if (!ignore_children || force_ignore_children) {
		size_t i = 0;
		for (auto w : widget->WidgetChildren()) {
			if (!w->Orphaned()) {
				widget->OnBeforePaintChild(i);
				UpdateRecursion(w);
				widget->OnAfterPaintChild(i);
				++i;
			}
		}
	}

	if (!ignore_self) {
		widget->PaintEnd();
		if (widget->impl_->layout_)
			widget->impl_->layout_->OnLayoutWidgetEnd(widget);
	}
}

void WidgetsDriver::CallUpdateEarlyRecursion(const SharedWidget& widget) {
	widget->PreparePaint();
	for (auto& w : widget->WidgetChildren()) {
		CallUpdateEarlyRecursion(w);
	}
}

void WidgetsDriver::PrepareRecursion(const SharedWidget& widget) {
	for (auto& w : widget->WidgetChildren()) {
		if (!w->impl_->awaked_) {
			w->Awake();
			w->impl_->awaked_ = true;
		}
	}
}

void WidgetsDriver::PushPendingFunctor(std::function<void()> func) {
	std::lock_guard lk(mutex_);
	pending_functors_.PushBack(std::move(func));
}
}
