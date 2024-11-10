#include "window_impl.h"

#include <miniwin/core/imgui_helper.h>

#include "win/core/widgets_driver.h"
#include "win/tools/graphic_utils.h"

namespace miniwin {
Window::Impl::Impl(Window* owner)
    : owner_(owner)
{
    WidgetsDriver::instance().RegisterWindow(owner_);
}

void Window::Impl::PaintBegin()
{
    top_sc_.Enter();
    collapsed_sc_.Enter();

    bool open = true;
    ImGuiHelper::BeginWindow(owner_->Title(), is_closable_ ? &open : nullptr);

    if (collapsed_sc_.HasChange())
    {
        ImGuiHelper::SetWindowCollapsed(*collapsed_sc_);
        owner_->OnCollapseChanged(*collapsed_sc_);
    }
    else
    {
        auto c = ImGuiHelper::IsWindowCollapsed();
        if (c != *collapsed_sc_)
        {
            collapsed_sc_.SetValueDirectly(c);
            owner_->OnCollapseChanged(c);
        }
    }

    is_docking_ = ImGuiHelper::IsWindowDocked();
    // 获取当前窗体句柄, 然后判断是否改变
    // 如果改变则说明当前窗体脱离或者停靠到了某个窗体
    hwnd_ = GraphicUtils::GetCurrentWindow();
    if (hwnd_ && hwnd_ != prev_hwnd_) {
        // 如果当前窗体非停靠窗, 说明是从默认窗体上剥离出来, 或者从停靠状态取消的窗体, 需要重设置顶状态
        // 如果当前窗体是停靠窗, 则不改变置顶状态
        if (!is_docking_) {
            GraphicUtils::EnableWindowTop(hwnd_, *top_sc_);
        }
        prev_hwnd_ = hwnd_;
        owner_->OnDockingChanged();
    }
    if (top_sc_.HasChange() && hwnd_) {
        GraphicUtils::EnableWindowTop(hwnd_, *top_sc_);
    }
    if (!open) {
        owner_->Close();
    }
}

void Window::Impl::PaintEnd()
{
    ImGuiHelper::EndWindow();
    top_sc_.Exit();
    collapsed_sc_.Exit();
}
}
