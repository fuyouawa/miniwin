#include "window_impl.h"

#include <miniwin/io/scene.h>
#include <miniwin/tools/graphic.h>


namespace miniwin {
Window::Window(const String& title)
	: Widget(nullptr, title)
{
    impl_ = std::make_unique<Impl>(this);
}

Window::~Window()
{
}

const String& Window::Title() const {
    return Name();
}

void Window::SetTitle(const String& title) {
    SetName(title);
}

void Window::CenterWindow() {
    Invoke([this]() {
        auto size = graphic::GetSceneSize();
        SetPosition(size * 0.5f, {0.5f, 0.5f});
        });
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
