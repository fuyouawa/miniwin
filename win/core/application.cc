#include "application_impl.h"

#include "win/tools/debug.h"
#include <imgui/imgui.h>

namespace miniwin {
const Application* Application::instance()
{
    return Impl::instance_;
}

Application::Application()
{
    impl_ = std::make_unique<Impl>(this);
    SetIniFileName("miniwin.ini");
}

Application::~Application()
{
}

bool Application::IsHideMainWindow() const
{
    return impl_->hide_main_window_;
}

void Application::SetHideMainWindow(bool b)
{
    impl_->hide_main_window_ = b;
}

const String& Application::MainWindowClassName() const
{
    return impl_->main_window_class_name_;
}

void Application::MainWindowClassName(const String& class_name)
{
    impl_->main_window_class_name_ = class_name;
}

const String& Application::MainWindowTitle() const
{
    return impl_->main_window_title_;
}

void Application::SetMainWindowTitle(const String& title) const
{
    impl_->main_window_title_ = title;
}

const String& Application::IniFileName() const {
    return impl_->ini_filename_;
}

bool Application::IsIniFileEnabled() const {
    return impl_->ini_filename_.data() == nullptr;
}

void Application::EnabledIniFile(bool b) {
    ImGui::GetIO().IniFilename = b ? impl_->ini_filename_.data() : nullptr;
}

void Application::SetIniFileName(const String& filename) {
    impl_->ini_filename_ = filename;
    ImGui::GetIO().IniFilename = impl_->ini_filename_.data();
}

size_t Application::Fps() const
{
    return impl_->fps_;
}

void Application::SetFps(size_t fps)
{
    impl_->fps_ = fps;
}

uint64_t Application::FrameCount() const {
    return impl_->frame_count_;
}

bool Application::IsExecuting() const
{
    return impl_->is_executing_;
}
}
