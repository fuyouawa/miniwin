#pragma once
#include <miniwin/widgets/window.h>
#include "miniwin/tools/scope_variable.h"

namespace miniwin {
class Window::Impl
{
public:
    ScopeCondition top_sc_;
    void* hwnd_;
    void* prev_hwnd_;
    bool is_docking_;
    bool has_close_button_ = true;
    Window* owner_;

    void PaintBegin();
    void PaintEnd();

    void OnDockingChanged();

    Impl(Window* owner);
};
}
