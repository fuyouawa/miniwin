#include <miniwin/widgets/layout/layout.h>

#include <miniwin/core/imgui.h>
#include <miniwin/core/application.h>
#include <miniwin/core/event_mgr.h>

#include "win/core/object_impl.h"
#include "win/core/widget_impl.h"

namespace miniwin {
class Layout::Impl {
public:
	Impl(Layout* owner) : owner_(owner) {}
	
	Layout* owner_;
	List<WeakWidget> widgets_;
};

Layout::Layout() {
	impl_ = std::make_unique<Impl>(this);
}

Layout::~Layout() {}

bool Layout::AddWidget(const SharedWidget& widget) {
	//TODO widget检查
	if (widget->impl_->layout_ == this)
		return false;

	if (widget->impl_->layout_ != nullptr) {
		widget->impl_->layout_->RemoveWidget(widget);
	}

	if (!impl_->widgets_.FindIf([&widget](const WeakWidget& w) {
		return w.lock() == widget;
	}).IsEnd()) {
		return false;
	}
	impl_->widgets_.PushBack(widget);
	widget->impl_->layout_ = this;
	return true;
}

bool Layout::RemoveWidget(const SharedWidget& widget) {
	if (impl_->widgets_.EraseIf([&widget](const WeakWidget& w) {
		return w.lock() == widget;
	}) > 0) {
		widget->impl_->layout_ = nullptr;
		return true;
	}
	return false;
}

void Layout::ClearWidget() {
	impl_->widgets_.Clear();
}

bool Layout::IsLayout() const {
	return true;
}

SharedWidget Layout::WidgetByIndex(size_t index) const {
	return impl_->widgets_[index].lock();
}

List<SharedWidget> Layout::Widgets() const {
	List<SharedWidget> total;
	for (auto& w : impl_->widgets_) {
		if (auto w2 = w.lock()) {
			total.PushBack(w2);
		}
	}
	return total;
}

bool Layout::SetWidgetIndex(const SharedWidget& widget, size_t index) {
	if (index > impl_->widgets_.size())
		return false;
	auto old = impl_->widgets_.FindIf([&widget](const WeakWidget& w) {
		return w.lock() == widget;
	});
	if (old.IsEnd())
		return false;
	auto old_idx = old.index();
	impl_->widgets_.Erase(old);
	if (index > old_idx)
		--index;
	impl_->widgets_.Insert(impl_->widgets_.begin() + static_cast<intptr_t>(index), widget);
	return true;
}

size_t Layout::IndexOfWidget(const SharedWidget& widget) const {
	for (size_t i = 0; i < impl_->widgets_.size(); ++i) {
		if (impl_->widgets_[i].lock() == widget)
			return i;
	}
	return static_cast<size_t>(-1);
}

size_t Layout::AdvanceWidget(const SharedWidget& widget, size_t count) {
	auto idx = IndexOfWidget(widget);
	if (idx != static_cast<size_t>(-1))
		return static_cast<size_t>(-1);

	size_t c = Count();
	size_t end_idx = idx + count;
	if (end_idx >= c) {
		end_idx = c - 1;
	}
	count = end_idx - idx;
	if (count > 0) {
		if (SetWidgetIndex(widget, end_idx)) {
			return count;
		}
		return static_cast<size_t>(-1);
	}
	return 0;
}

size_t Layout::Count() const {
	return impl_->widgets_.size();
}

bool Layout::IsEmpty() const {
	return Count() == 0;
}

void Layout::Initialize(const SharedObject& parent) {
	Application::Instance().PushPendingFunctor([self = shared_from_this(), parent]() {
		self->SetParent(parent);
		});
}

void Layout::OnPrepareLayout() {
	imgui::BeginGroup();
}

void Layout::OnBeginLayoutWidget(const SharedWidget& widget, size_t index) {}

void Layout::OnEndLayoutWidget(const SharedWidget& widget, size_t index) {}

void Layout::OnFinishedLayout() {
	imgui::EndGroup();
}
}
