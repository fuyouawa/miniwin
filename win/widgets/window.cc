#include "window_impl.h"

namespace miniwin {
Window::Window(std::u8string_view title)
	: Widget(nullptr, title)
{
    impl_ = std::make_unique<Impl>(this);
}

Window::~Window()
{
}

std::u8string_view Window::Title() const {
    return Name();
}

void Window::SetTitle(std::u8string_view title) {
    SetName(title);
}

void Window::EnableTop(bool b)
{
    impl_->top_sc_.SetControl(b);
}

void Window::SetClosable(bool b)
{
    impl_->is_closable_ = b;
}

void Window::SetCollapsed(bool b)
{
    impl_->collapsed_sc_.SetControl(b);
}

bool Window::IsClosable() const {
	return impl_->is_closable_;
}

bool Window::IsDocking() const {
	return impl_->is_docking_;
}

bool Window::IsCollapsed() const
{
    return *impl_->collapsed_sc_;
}

void Window::PaintBegin()
{
	Widget::PaintBegin();
    impl_->PaintBegin();
}

void Window::PaintEnd()
{
    impl_->PaintEnd();
	Widget::PaintEnd();
}
}
