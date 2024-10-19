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
    ScopeCondition top_sc_;
    void* hwnd_;
    void* prev_hwnd_;
    bool is_docking_;
    bool has_close_button_ = true;
    Window* owner_;
};
}
