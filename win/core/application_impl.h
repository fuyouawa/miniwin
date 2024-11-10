#pragma once
#include <miniwin/core/application.h>

#include <string>

namespace miniwin {
class Application::Impl {
public:
    static Application* instance_;

    Impl(Application* owner);
    ~Impl();

    void OnAppStart();
    void OnProcess();
    bool IsDone();
    void OnAppExit();

    bool SetDpiScale(float scale);

    void WindowWannaClose();

    void DoFps() const;

    bool hide_main_window_ = false;
    String main_window_class_name_ = "Miniwin";
    String main_window_title_ = "Miniwin App";
    size_t fps_ = 60;
    float cur_dpi_scale_ = 0;
    float prev_dpi_scale_ = 0;
    void* origin_hwnd_ = nullptr;

    bool close_in_next_frame_ = false;
    bool is_executing_ = false;
    size_t delta_time_ = 0;
    uint64_t frame_count_ = 0;
    Application* owner_;
};
}
