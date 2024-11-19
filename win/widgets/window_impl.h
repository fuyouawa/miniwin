#pragma once
#include <miniwin/widgets/window.h>

#include <miniwin/tools/scope_variable.h>

#include <imgui/imgui_internal.h>

namespace miniwin {
class Window::Impl
{
public:
    Impl(Window* owner);

    void Awake();

    void PaintBegin();
    void PaintEnd();

    ImGuiWindow* GetImGuiWindow() const;

    void OnPaintWindowBegin();
    void OnPaintWindowEnd();

    mutable ImGuiWindow* imgui_win_cache_ = nullptr;

    ScopeCondition top_sc_{ false };
    ScopeCondition collapsed_sc_{ false };
    ScopeVariable<Vector2D> pivot_sc_;

    Vector2D prev_set_size_;
    Vector2D prev_set_pos_;
    Vector2D calc_size_;
    Vector2D calc_pos_;

    bool is_docking_ = false;
    bool is_close_btn_enabled_ = true;

    void* hwnd_ = nullptr;
    void* prev_hwnd_ = nullptr;

    Window* owner_;
};
}
