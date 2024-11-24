#include "window_impl.h"
#include <miniwin/core/imgui.h>

#include <miniwin/tools/graphic.h>
#include <miniwin/core/io.h>
#include "win/core/widgets_driver.h"
#include "win/tools/debug.h"

namespace miniwin {
Window::Impl::Impl(Window* owner)
    : owner_(owner)
{
}
void Window::Impl::PaintBegin()
{
    top_sc_.Enter();
    collapsed_sc_.Enter();
    pivot_sc_.Enter();
    position_sc_.Enter();
    size_sc_.Enter();

    if (position_sc_.HasChange() || pivot_sc_.HasChange()) {
        imgui::SetNextWindowPos(position_sc_.cur_value(), imgui::kCondAlways, pivot_sc_.cur_value());
        if (position_sc_.HasChange()) {
            owner_->OnPositionChanged(position_sc_.cur_value(), position_sc_.prev_value());
        }
    }

    if (size_sc_.HasChange()) {
        imgui::SetNextWindowSize(size_sc_.cur_value(), imgui::kCondAlways);
        owner_->OnSizeChanged(size_sc_.cur_value(), size_sc_.prev_value());
    }
    imgui::SetNextWindowBgAlpha(owner_->BgAlpha());
    owner_->OnPaintWindowBegin();

    auto cur_size = imgui::GetWindowSize();
    if (cur_size != size_sc_.cur_value()) {
        owner_->OnSizeChanged(cur_size, size_sc_.cur_value());
        size_sc_.SetValueDirectly(cur_size);
    }

    auto cur_pos = imgui::GetWindowPos();
    if (cur_pos != position_sc_.cur_value()) {
        owner_->OnPositionChanged(cur_pos, position_sc_.cur_value());
        position_sc_.SetValueDirectly(cur_pos);
    }

    if (collapsed_sc_.HasChange())
    {
        imgui::SetWindowCollapsed(collapsed_sc_.cur_value());
        owner_->OnCollapseChanged(collapsed_sc_.cur_value());
    }
    else
    {
        auto c = imgui::IsWindowCollapsed();
        if (c != collapsed_sc_.cur_value())
        {
            collapsed_sc_.SetValueDirectly(c);
            owner_->OnCollapseChanged(c);
        }
    }

    is_docking_ = imgui::IsWindowDocked();
    // 获取当前窗体句柄, 然后判断是否改变
    // 如果改变则说明当前窗体脱离或者停靠到了某个窗体
    hwnd_ = GetImGuiWindow() ? GetImGuiWindow()->Viewport->PlatformHandle : nullptr;

    if (hwnd_ && hwnd_ != prev_hwnd_) {
        // 如果当前窗体非停靠窗, 说明是从默认窗体上剥离出来, 或者从停靠状态取消的窗体, 需要重设置顶状态
        // 如果当前窗体是停靠窗, 则不改变置顶状态
        if (!is_docking_) {
            graphic::EnableWindowTop(hwnd_, top_sc_.cur_value());
        }
        prev_hwnd_ = hwnd_;
        owner_->OnDockingChanged();
    }
    if (top_sc_.HasChange() && hwnd_) {
        graphic::EnableWindowTop(hwnd_, top_sc_.cur_value());
    }
}

void Window::Impl::PaintEnd()
{
    owner_->OnPaintWindowEnd();

    top_sc_.Exit();
    collapsed_sc_.Exit();
    pivot_sc_.Exit();
    position_sc_.Exit();
    size_sc_.Exit();
}

ImGuiWindow* Window::Impl::GetImGuiWindow() const {
    if (imgui_win_cache_ == nullptr) {
        imgui_win_cache_ = ImGui::FindWindowByID(owner_->Id());
    }
    return imgui_win_cache_;
}

void Window::Impl::OnPaintWindowBegin() {
    bool open = true;
    imgui::BeginWindow(owner_->Title(), owner_->Id(), is_close_btn_enabled_ ? &open : nullptr);

    if (!open) {
        owner_->Close();
    }
}

void Window::Impl::OnPaintWindowEnd() {
    imgui::EndWindow();
}
}
