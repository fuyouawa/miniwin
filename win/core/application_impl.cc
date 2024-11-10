#include "application_impl.h"

#include <thread>

#include <miniwin/tools/mathf.h>
#include "widgets_driver.h"
#include "win/tools/debug.h"

namespace miniwin {
Application* Application::Impl::instance_ = nullptr;

Application::Impl::Impl(Application* owner)
    : owner_(owner)
{
    MW_ASSERT_X(instance_ == nullptr);
    instance_ = owner_;
}

Application::Impl::~Impl() {
    instance_ = nullptr;
}

void Application::Impl::OnAppStart()
{
    is_executing_ = true;
}

void Application::Impl::OnProcess()
{
    WidgetsDriver::instance().Update();
    ++frame_count_;
    if (close_in_next_frame_)
    {
        MW_ASSERT_X(IsDone());
    }
}

bool Application::Impl::IsDone()
{
    return WidgetsDriver::instance().IsDone();
}

void Application::Impl::OnAppExit()
{
    is_executing_ = false;
}

bool Application::Impl::SetDpiScale(float scale)
{
    cur_dpi_scale_ = scale > 1.0f ? scale : 1.0f;
    bool changed = !Mathf::Approximately(cur_dpi_scale_, prev_dpi_scale_);
    prev_dpi_scale_ = cur_dpi_scale_;
    return changed;
}

void Application::Impl::WindowWannaClose()
{
    WidgetsDriver::instance().CloseAll();
    close_in_next_frame_ = true;
}

void Application::Impl::DoFps() const
{
    auto sleep_time = 1000 / fps_;
    if (sleep_time > delta_time_) {
        std::this_thread::sleep_for(std::chrono::milliseconds{ sleep_time - delta_time_ });
    }
}
}

