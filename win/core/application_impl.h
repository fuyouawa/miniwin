#pragma once
#include <miniwin/core/application.h>

#include <string>

namespace miniwin {
class Application::Impl {
public:
    Impl(Application* owner);

    void OnAppStart();
    void OnProcess();
    bool IsDone();
    void OnAppExit();

    bool SetDpiScale(float scale);

    void WindowWannaClose();

    void DoFps() const;

    bool hide_main_window_ = false;
    std::u8string main_window_class_name_ = u8"Miniwin";
    std::u8string main_window_title_ = u8"Miniwin App";
    size_t fps_ = 60;
    float cur_dpi_scale_ = 0;
    float prev_dpi_scale_ = 0;
    void* origin_hwnd_ = nullptr;

    bool close_in_next_frame_ = false;
    bool is_executing_ = false;
    size_t delta_time_ = 0;
    Application* owner_;
};
}
