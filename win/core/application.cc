#include "application_impl.h"

#include <cassert>


namespace miniwin {
Application* Application::instance_ = nullptr;

const Application* Application::instance()
{
    return instance_;
}

Application::Application()
{
    assert(instance_ == nullptr);
    instance_ = this;
    impl_ = std::make_unique<Impl>(this);
}

Application::~Application()
{
    instance_ = nullptr;
}

bool Application::IsHideMainWindow() const
{
    return impl_->hide_main_window_;
}

void Application::SetHideMainWindow(bool b)
{
    impl_->hide_main_window_ = b;
}

std::u8string_view Application::MainWindowClassName() const
{
    return impl_->main_window_class_name_;
}

void Application::MainWindowClassName(std::u8string_view class_name)
{
    impl_->main_window_class_name_ = class_name;
}

std::u8string_view Application::MainWindowTitle() const
{
    return impl_->main_window_title_;
}

void Application::SetMainWindowTitle(std::u8string_view title) const
{
    impl_->main_window_title_ = title;
}

size_t Application::Fps() const
{
    return impl_->fps_;
}

void Application::SetFps(size_t fps)
{
    impl_->fps_ = fps;
}

bool Application::IsExecuting() const
{
    return impl_->is_executing_;
}
}
