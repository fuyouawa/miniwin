#include "window_impl.h"
#include <miniwin/core/imgui.h>

#include <miniwin/io/scene.h>
#include "win/core/widgets_driver.h"
#include <miniwin/tools/graphic.h>

#include "win/tools/debug.h"

namespace miniwin {
Window::Impl::Impl(Window* owner)
    : owner_(owner)
{
}

void Window::Impl::Awake() {
    if (!owner_->WidgetParent()) {
        WidgetsDriver::Instance().RegisterWindow(owner_->shared_from_this());
    }
}

void Window::Impl::PaintBegin()
{
    top_sc_.Enter();
    collapsed_sc_.Enter();
    pivot_sc_.Enter();

    auto pos = owner_->Position();
    if (pos != prev_set_pos_ || pivot_sc_.HasChange()) {
        imgui::SetNextWindowPos(pos, imgui::kCondAlways, pivot_sc_.cur_value());
        prev_set_pos_ = pos;
    }

    auto size = owner_->Size();
    if (size != prev_set_size_) {
        imgui::SetNextWindowSize(size, imgui::kCondAlways);
        prev_set_size_ = size;
    }
    imgui::SetNextWindowBgAlpha(owner_->BgAlpha());
    owner_->OnPaintWindowBegin();

    calc_size_ = imgui::GetWindowSize();
    calc_pos_ = imgui::GetWindowPos();

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
