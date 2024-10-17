#include "win/widgets/window_impl.h"

#include "win/core/widgets_driver.h"
#include "win/tools/graphic_utils.h"

#include "miniwin/core/imgui_helper.h"

namespace miniwin {
Window::Impl::Impl(Window* owner)
    : hwnd_(nullptr), prev_hwnd_(nullptr), is_docking_(false), owner_(owner)
{
    WidgetsDriver::instance().RegisterWindow(owner_);
}

void Window::Impl::PaintBegin()
{
    top_sc_.Entry();

    bool open = true;
    ImGuiHelper::BeginWindow(owner_->title(), has_close_button_ ? &open : nullptr, owner_->flags());

    is_docking_ = ImGuiHelper::IsWindowDocked();
    // 获取当前窗体句柄, 然后判断是否改变
    // 如果改变则说明当前窗体脱离或者停靠到了某个窗体
    hwnd_ = GraphicUtils::GetCurrentWindow();
    if (hwnd_ && hwnd_ != prev_hwnd_) {
        OnDockingChanged();
        prev_hwnd_ = hwnd_;
    }
    if (top_sc_.is_changed() && hwnd_) {
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
}

void Window::Impl::OnDockingChanged()
{
    // 如果当前窗体非停靠窗, 说明是从默认窗体上剥离出来, 或者从停靠状态取消的窗体, 需要重设置顶状态
    // 如果当前窗体是停靠窗, 则不改变置顶状态
    if (!is_docking_) {
        GraphicUtils::EnableWindowTop(hwnd_, *top_sc_);
    }
}
}
