#pragma once
#include <fugui/widgets/window.h>
#include "fugui/tools/scope_variable.h"

namespace fugui {
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
