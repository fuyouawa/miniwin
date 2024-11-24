#include "widgets_driver.h"

#include "object_impl.h"
#include "miniwin/core/application.h"
#include "miniwin/widgets/layout/layout.h"
#include "win/core/widget_impl.h"
#include "win/tools/debug.h"
#include "win/widgets/window_impl.h"

namespace miniwin {
WidgetsDriver::WidgetsDriver() {
	ui_thread_id_ = std::this_thread::get_id();
}

WidgetsDriver::~WidgetsDriver() {
	CloseAll();
}

void WidgetsDriver::Update() {
	DoPending();
	Prepare();
	CallUpdateEarly();
	size_t i = 0;
	for (auto& win : windows_) {
		UpdateWidget(win, &i);
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
		PrepareRecursion(win);

		// 因为只有Widget是有权限调用的，所以得转成Widget
		auto w = dynamic_cast<Widget*>(win.get());
		if (!w->impl_->started_) {
			w->Start();
		}
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

void WidgetsDriver::UpdateChildrenRecursion(const SharedWidget& widget) {
	MW_ASSERT_X(widget->impl_->started_ && widget->Visible());

	auto ignore_children = (widget->GetDrawFlags() & Widget::kDrawIgnoreChildren) != 0;

	if (!ignore_children) {
		size_t i = 0;
		for (auto& o : widget->Children()) {
			if (o->IsLayout()) {
				auto l = std::dynamic_pointer_cast<Layout>(o);
				UpdateLayout(l, &i);
				continue;
			}
			if (o->IsWidget()) {
				auto w = std::dynamic_pointer_cast<Widget>(o);
				if (w->impl_->layout_)
					continue;
				UpdateWidget(w, &i);
			}
		}
	}
}

void WidgetsDriver::UpdateWidget(const SharedWidget& widget, size_t* index) {
	MW_ASSERT_X(widget->impl_->started_ && widget->Visible());

	// 判断是否要忽略自己
	auto ignore_self = (widget->GetDrawFlags() & Widget::kDrawIgnoreSelf) != 0;
	if (!ignore_self) {
		widget->PaintBegin(*index);
		++*index;
	}

	bool can_update_children = true;
	// 如果是窗体并且折叠了，那就不绘制子控件
	if (widget->IsWindow()) {
		auto w = std::dynamic_pointer_cast<Window>(widget);
		can_update_children = !w->IsCollapsed();
	}

	if (can_update_children && widget->Visible()) {
		UpdateChildrenRecursion(widget);
	}

	if (!ignore_self)
		widget->PaintEnd(*index);
}

void WidgetsDriver::UpdateLayout(const SharedLayout& layout, size_t* index) {
	size_t i = 0;
	for (auto& w : layout->Widgets()) {
		MW_ASSERT_X(w->impl_->layout_ == layout.get());
		if (w->Visible()) {
			if (i == 0) {
				layout->OnBeginLayout();
			}
			layout->OnLayoutWidgetBegin(w, i);
			UpdateWidget(w, index);
			layout->OnLayoutWidgetEnd(w, i);
			++i;
		}
	}
	if (i != 0) {
		layout->OnEndLayout();
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
		if (!w->impl_->started_) {
			PrepareRecursion(w);
			w->Start();
		}
	}
}

void WidgetsDriver::PushPendingFunctor(std::function<void()> func) {
	std::lock_guard lk(mutex_);
	pending_functors_.PushBack(std::move(func));
}

const List<SharedWindow>& WidgetsDriver::Windows() {
	return windows_;
}
}
