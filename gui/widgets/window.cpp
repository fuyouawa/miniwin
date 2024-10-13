#include "gui/core/widgets_driver.h"
#include "gui/widgets/window_impl.h"

namespace fugui {

Window::Window(std::u8string_view title, bool show)
	: Widget(nullptr, title, show, WidgetType::kWindow)
{
    impl_ = std::make_unique<Impl>(this);
}

Window::~Window()
{
}

std::u8string_view Window::title() const {
    return name();
}

void Window::set_title(std::u8string_view title) const {
    set_name(title);
}

void Window::EnableTop(bool b) const
{
    impl_->top_sc_.set_control(b);
}

void Window::EnableCloseButton(bool b) const
{
    impl_->has_close_button_ = b;
}

bool Window::has_close_button() const {
	return impl_->has_close_button_;
}

bool Window::is_docking() const {
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
