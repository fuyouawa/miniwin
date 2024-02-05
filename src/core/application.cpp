#include <mvcgui/core/application.h>
#include <mvcgui/internal/framework/widget_engine.h>
#include <assert.h>
#include <mvcgui/io/font.h>

namespace mvcgui {
Application::Application()
    : internal::CoreApplication{},
    close_in_next_frame_{ false }
{
}

void Application::OnInitizlize() {
}

void Application::OnProcess() {
	internal::WidgetEngine::instance().Thinking();
    if (close_in_next_frame_) {
        assert(IsDone());
    }
}

bool Application::IsDone() {
	return internal::WidgetEngine::instance().IsEmpty();
}

void Application::OnAppExit() {
}

void Application::OnDpiScaleChanged()
{
    FontUtil::Clear();
    FontUtil::AddFont("C:/Windows/Fonts/msyh.ttc", cur_scale_.x * 16.0f);
    FontUtil::Rebuild();
}

void Application::WindowWannaClose() {
    internal::WidgetEngine::instance().CloseAll();
    close_in_next_frame_ = true;
}
}