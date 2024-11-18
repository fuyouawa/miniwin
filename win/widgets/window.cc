#include "window_impl.h"

#include "win/core/widget_impl.h"
#include <miniwin/io/scene.h>
#include <miniwin/tools/graphic.h>


namespace miniwin {
Window::Window()
{
	impl_ = std::make_unique<Impl>(this);
	Widget::impl_->is_window_ = true;
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

void Window::CenterInScene() {
	Invoke([this]() {
		auto size = graphic::GetSceneSize();
		SetPosition(size * 0.5f, {0.5f, 0.5f});
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

void Window::SetSize(const Vector2D& size) {
	Widget::SetSize(size);
	impl_->size_to_set_ = size;
}

void Window::SetPosition(const Vector2D& pos) {
	SetPosition(pos, {});
}

void Window::SetPosition(const Vector2D& pos, const Vector2D& pivot) {
	Widget::SetPosition(pos);
	impl_->pos_and_pivot_to_set_ = std::pair(pos, pivot);
}

bool Window::IsDocking() const {
	return impl_->is_docking_;
}

bool Window::IsCollapsed() const {
	return impl_->collapsed_sc_.cur_value();
}

void* Window::PlatformHandle() const {
	return impl_->hwnd_;
}

void Window::Awake() {
	Widget::Awake();
	impl_->Awake();
}

void Window::PaintBegin() {
	Widget::PaintBegin();
	impl_->PaintBegin();
}

void Window::PaintEnd() {
	impl_->PaintEnd();
	Widget::PaintEnd();
}

void Window::OnPaintWindowBegin() {
	impl_->OnPaintWindowBegin();
}

void Window::OnPaintWindowEnd() {
	impl_->OnPaintWindowEnd();
}
}
