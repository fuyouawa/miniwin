#pragma once
#include <miniwin/widgets/window.h>
#include <miniwin/tools/scope_variable.h>

namespace miniwin {
class Window::Impl
{
public:
    Impl(Window* owner);

    void PaintBegin();
    void PaintEnd();

    void OnDockingChanged();

    WindowFlags flags_ = WindowFlags::kNone;
    ScopeCondition top_sc_{ false };
    void* hwnd_ = nullptr;
    void* prev_hwnd_ = nullptr;
    bool is_docking_ = false;
    bool has_close_button_ = true;
    Window* owner_;
};
}
