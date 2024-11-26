#include "window_impl.h"

#include "win/core/widget_impl.h"
#include <miniwin/core/io.h>
#include <miniwin/tools/graphic.h>

#include "miniwin/core/application.h"
#include "win/core/platform_window_impl.h"
#include "win/tools/debug.h"


namespace miniwin {
Window::Window() {
	impl_ = std::make_unique<Impl>(this);
}

Window::~Window() {}

String Window::Title() const {
	return Name();
}

void Window::SetTitle(const String& title) {
	auto prev = Name();
	SetName(title);
	OnTitleChanged(title, prev);
}

void Window::AlignWindow(Alignment alignment, WindowRelativeTo relative) {
	Invoke([this, alignment, relative]() {
		Vector2D pos;
		//TODO AlignWindow的alignment
		switch (relative) {
		case WindowRelativeTo::kMainWindow: {
			pos = io::DisplaySize() * 0.5f;
			break;
		}
		case WindowRelativeTo::kScene: {
			pos = graphic::GetSceneSize() * 0.5f;
			break;
		}
		}
		SetPosition(pos, relative);
		SetPivot({0.5f, 0.5f});
	});
}

bool Window::IsTopEnabled() const {
	return impl_->top_sc_.cur_value();
}

bool Window::IsCloseButtonEnabled() const {
	return impl_->is_close_btn_enabled_;
}

void Window::EnableCloseButton(bool b) {
	impl_->is_close_btn_enabled_ = b;
}

void Window::EnableTop(bool b) {
	impl_->top_sc_.SetControl(b);
}

void Window::SetCollapsed(bool b) {
	impl_->collapsed_sc_.SetControl(b);
}

Vector2D Window::Pivot() const {
	return impl_->pivot_sc_.cur_value();
}

void Window::SetPivot(Vector2D pivot) {
	impl_->pivot_sc_.SetControl(pivot);
}

bool Window::IsDocking() const {
	return impl_->is_docking_;
}

bool Window::IsCollapsed() const {
	return impl_->collapsed_sc_.cur_value();
}

bool Window::IsWindow() const {
	return true;
}

SharedPlatformWindow Window::PlatformWindow() const {
	auto w = OwnerWindow()->impl_->platform_win_.lock();
	MW_ASSERT(w, "Window must have a owner platform window");
	return w;
}

void* Window::PlatformHandle() const {
	return impl_->hwnd_;
}

void Window::SetPlatformWindow(const SharedPlatformWindow& win) {
	impl_->platform_win_ = win;
	dynamic_cast<PlatformWindowImpl*>(win.get())->RegisterSubWindow(shared_from_this());
}

Vector2D Window::Position(WindowRelativeTo relative) const {
	auto p = impl_->position_sc_.cur_value();
	switch (relative) {
	case WindowRelativeTo::kMainWindow: {
		if (p == Vector2D::kZero) {
			return p;
		}
		//TODO 预测位置
		return p - VecIntToVec(PlatformWindow()->ClientSize());
	}
	case WindowRelativeTo::kScene:
		return p;
	}
	MW_ASSERT_X(false);
	return p;
}

void Window::SetPosition(const Vector2D& pos, WindowRelativeTo relative) {
	auto p = pos;
	switch (relative) {
	case WindowRelativeTo::kMainWindow:
		p += VecIntToVec(PlatformWindow()->ClientPosition());
		break;
	case WindowRelativeTo::kScene:
		break;
	}
	impl_->position_sc_.SetControl(std::move(p));
}

Vector2D Window::Size() const {
	return impl_->size_sc_.cur_value();
}

void Window::SetSize(const Vector2D& size) {
	impl_->size_sc_.SetControl(size);
}

void Window::BeginUpdate(size_t index) {
	Widget::BeginUpdate(index);
	impl_->PaintBegin();
}

void Window::EndUpdate(size_t index) {
	impl_->PaintEnd();
	Widget::EndUpdate(index);
}

void Window::OnPaintWindowBegin() {
	impl_->OnPaintWindowBegin();
}

void Window::OnPaintWindowEnd() {
	impl_->OnPaintWindowEnd();
}
}
