#include "imgui/imgui.h"
#include "gui/widgets/window_impl.h"

#include "gui/core/widgets_driver.h"
#include "gui/tools/graphic_utils.h"

#include "gui/core/drawer.h"

namespace fugui {
Window::Impl::Impl(Window* owner)
    : owner_(owner)
{
    WidgetsDriver::instance().RegisterWindow(owner_);
}

void Window::Impl::PaintBegin()
{
    top_sc_.Entry();

    bool open = true;
    Drawer::BeginWindow(owner_->title(), has_close_button_ ? &open : nullptr, owner_->flags());

    is_docking_ = ImGui::IsWindowDocked();
    // 获取当前窗体句柄, 然后判断是否改变
    // 如果改变则说明当前窗体脱离或者停靠到了某个窗体
    hwnd_ = internal::GraphicUtils::GetCurrentWindow();
    if (hwnd_ && hwnd_ != prev_hwnd_) {
        OnDockingChanged();
        prev_hwnd_ = hwnd_;
    }
    if (top_sc_.is_changed() && hwnd_) {
        internal::GraphicUtils::EnableWindowTop(hwnd_, *top_sc_);
    }
    if (!open) {
        owner_->Close();
    }
}

void Window::Impl::PaintEnd()
{
    Drawer::EndWindow();
    top_sc_.Exit();
}

void Window::Impl::OnDockingChanged()
{
    // 如果当前窗体非停靠窗, 说明是从默认窗体上剥离出来, 或者从停靠状态取消的窗体, 需要重设置顶状态
    // 如果当前窗体是停靠窗, 则不改变置顶状态
    if (!is_docking_) {
        internal::GraphicUtils::EnableWindowTop(hwnd_, *top_sc_);
    }
}
}
