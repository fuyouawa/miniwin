#include "window_impl.h"

#include "win/core/widget_impl.h"
#include <miniwin/core/io.h>
#include <miniwin/tools/graphic.h>
#include "win/core/main_window_impl.h"
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

SharedMainWindow Window::OwnerMainWindow() const {
	auto p = impl_->main_window_.lock();
	MW_ASSERT_X(p);
	return p;
}

void Window::SetMainWindow(const SharedMainWindow& win) {
	auto w = dynamic_cast<MainWindowImpl*>(win.get());
	MW_ASSERT_X(w);
	w->RegisterSubWindow(shared_from_this());
	impl_->main_window_ = win;
}

void Window::AlignWindow(Alignment alignment, WindowRelativeTo relative) {
	Invoke([this, alignment, relative]() {
		Vector2D pos;
		//TODO AlignWindow的alignment
		switch (relative) {
		case WindowRelativeTo::kMainWindow: {
			pos = VecIntToVec(OwnerMainWindow()->ClientSize()) * 0.5f;
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

void* Window::PlatformHandle() const {
	return impl_->hwnd_;
}

Vector2D Window::Position(WindowRelativeTo relative) const {
	auto p = impl_->position_sc_.cur_value();
	switch (relative) {
	case WindowRelativeTo::kMainWindow: {
		if (p == Vector2D::kZero) {
			return p;
		}
		//TODO 预测位置
		return p - VecIntToVec(OwnerMainWindow()->ClientPosition());
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
		p += VecIntToVec(OwnerMainWindow()->ClientPosition());
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

void Window::PaintBegin(size_t index) {
	Widget::PaintBegin(index);
	impl_->PaintBegin();
}

void Window::PaintEnd(size_t index) {
	impl_->PaintEnd();
	Widget::PaintEnd(index);
}

void Window::OnPaintWindowBegin() {
	impl_->OnPaintWindowBegin();
}

void Window::OnPaintWindowEnd() {
	impl_->OnPaintWindowEnd();
}
}
