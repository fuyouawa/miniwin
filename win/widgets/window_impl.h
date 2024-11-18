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
    std::optional<std::pair<Vector2D, Vector2D>> pos_and_pivot_to_set_;
    std::optional<Vector2D> size_to_set_;

    bool is_docking_ = false;
    bool is_close_btn_enabled_ = true;

    void* hwnd_ = nullptr;
    void* prev_hwnd_ = nullptr;
    Window* owner_;
};
}
