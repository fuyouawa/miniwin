#include "window_impl.h"
#include <miniwin/core/imgui.h>

#include <miniwin/io/scene.h>
#include "win/core/widgets_driver.h"
#include <miniwin/tools/graphic.h>

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

    if (pos_and_pivot_to_set_) {
        imgui::SetNextWindowPos(pos_and_pivot_to_set_->first, imgui::kCondAlways, pos_and_pivot_to_set_->second);
        pos_and_pivot_to_set_.reset();
    }

    if (size_to_set_) {
        imgui::SetNextWindowSize(*size_to_set_, imgui::kCondAlways);
        size_to_set_.reset();
    }

    bool open = true;
    imgui::BeginWindow(owner_->Title(), is_closable_ ? &open : nullptr);

    owner_->Widget::SetSize(imgui::GetWindowSize());
    owner_->Widget::SetPosition(imgui::GetWindowPos());

    if (collapsed_sc_.HasChange())
    {
        imgui::SetWindowCollapsed(*collapsed_sc_);
        owner_->OnCollapseChanged(*collapsed_sc_);
    }
    else
    {
        auto c = imgui::IsWindowCollapsed();
        if (c != *collapsed_sc_)
        {
            collapsed_sc_.SetValueDirectly(c);
            owner_->OnCollapseChanged(c);
        }
    }

    is_docking_ = imgui::IsWindowDocked();
    // 获取当前窗体句柄, 然后判断是否改变
    // 如果改变则说明当前窗体脱离或者停靠到了某个窗体
    hwnd_ = graphic::GetCurrentWindow();
    if (hwnd_ && hwnd_ != prev_hwnd_) {
        // 如果当前窗体非停靠窗, 说明是从默认窗体上剥离出来, 或者从停靠状态取消的窗体, 需要重设置顶状态
        // 如果当前窗体是停靠窗, 则不改变置顶状态
        if (!is_docking_) {
            graphic::EnableWindowTop(hwnd_, *top_sc_);
        }
        prev_hwnd_ = hwnd_;
        owner_->OnDockingChanged();
    }
    if (top_sc_.HasChange() && hwnd_) {
        graphic::EnableWindowTop(hwnd_, *top_sc_);
    }
    if (!open) {
        owner_->Close();
    }
}

void Window::Impl::PaintEnd()
{
    imgui::EndWindow();
    top_sc_.Exit();
    collapsed_sc_.Exit();
}

ImGuiWindow* Window::Impl::GetImGuiWindow() const {
    return ImGui::FindWindowByName(owner_->Title().data());
}
}
