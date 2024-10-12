#pragma once
#include <fugui/core/application.h>
#include "fugui/tools/container.h"

namespace fugui {
class Application::Impl {
public:
    Impl(Application* owner);

    void OnAppStart();
    void OnProcess();
    bool IsDone();
    void OnDpiScaleChanged();
    void OnAppExit();

    void WindowWannaClose();

    void DoFps() const;

    bool close_in_next_frame_;
    bool is_executing_;
    uint32_t fps_ = 60;
    size_t delta_time_;
    Vector2 cur_scale_;
    Vector2 prev_scale_;
    Application* owner_;
};
}
