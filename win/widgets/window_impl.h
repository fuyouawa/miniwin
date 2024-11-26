#pragma once
#include <miniwin/widgets/window.h>

#include <miniwin/tools/scope_variable.h>

#include <imgui/imgui_internal.h>

namespace miniwin {
class Window::Impl
{
public:
    Impl(Window* owner);

    void PaintBegin();
    void PaintEnd();

    ImGuiWindow* GetImGuiWindow() const;

    void OnPaintWindowBegin();
    void OnPaintWindowEnd();

    mutable ImGuiWindow* imgui_win_cache_ = nullptr;

    ScopeCondition top_sc_{ false };
    ScopeCondition collapsed_sc_{ false };
    ScopeVariable<Vector2D> pivot_sc_;
    ScopeVariable<Vector2D> position_sc_;
    ScopeVariable<Vector2D> size_sc_;

    bool is_docking_ = false;
    bool is_close_btn_enabled_ = true;

    void* hwnd_ = nullptr;
    void* prev_hwnd_ = nullptr;

    std::weak_ptr<miniwin::PlatformWindow> platform_win_;
    Window* owner_;
};
}
