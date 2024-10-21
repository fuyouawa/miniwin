#include "win/core/widgets_driver.h"
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

void Window::SetTitle(std::u8string_view title) const {
    SetName(title);
}

WindowFlags Window::Flags() const
{
    return impl_->flags_;
}

void Window::SetFlags(WindowFlags flags)
{
    impl_->flags_ = flags;
}

void Window::EnableTop(bool b) const
{
    impl_->top_sc_.set_control(b);
}

void Window::SetClosable(bool b) const
{
    impl_->is_closable_ = b;
}

bool Window::IsClosable() const {
	return impl_->is_closable_;
}

bool Window::IsDocking() const {
	return impl_->is_docking_;
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
