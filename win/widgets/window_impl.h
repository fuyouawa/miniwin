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

    ScopeCondition top_sc_{ false };
    ScopeCondition collapsed_sc_{ false };
    bool is_closable_ = true;
    void* hwnd_ = nullptr;
    void* prev_hwnd_ = nullptr;
    bool is_docking_ = false;
    Window* owner_;
};
}
