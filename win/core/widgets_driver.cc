#include "widgets_driver.h"

#include "object_impl.h"
#include "miniwin/core/application.h"
#include "miniwin/widgets/layout/layout.h"
#include "win/core/widget_impl.h"
#include "win/tools/debug.h"
#include "win/widgets/window_impl.h"

namespace miniwin {
WidgetsDriver::WidgetsDriver() {
}

WidgetsDriver::~WidgetsDriver() {
	CloseAll();
}

void WidgetsDriver::Update() {
	CallUpdateEarly();
	size_t i = 0;
	{
		windows_.EraseIf([](auto w) {
			return w->Orphaned();
			});
	}
	for (auto& win : windows_) {
		UpdateWidget(win, &i);
	}
}

void WidgetsDriver::CallUpdateEarly() const {
	for (auto& win : windows_) {
		CallUpdateEarlyRecursion(win);
	}
}

bool WidgetsDriver::IsDone() const {
	return windows_.empty();
}

void WidgetsDriver::CloseAll() {
	Application::Instance().PushPendingFunctor([this] {
		for (auto& w : windows_) {
			w->Close();
		}
		windows_.Clear();
	});
}

void WidgetsDriver::RegisterWindow(const SharedWindow& window) {
	Application::Instance().PushPendingFunctor([window, this] {
		windows_.PushBack(window);
	});
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
	if (!widget->IsStarted()) {
		widget->Start();
	}
	widget->PreparePaint();
	for (auto& w : widget->WidgetChildren()) {
		CallUpdateEarlyRecursion(w);
	}
}

const List<SharedWindow>& WidgetsDriver::Windows() {
	return windows_;
}
}
