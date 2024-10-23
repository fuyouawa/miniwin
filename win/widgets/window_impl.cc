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
    // ��ȡ��ǰ������, Ȼ���ж��Ƿ�ı�
    // ����ı���˵����ǰ�����������ͣ������ĳ������
    hwnd_ = GraphicUtils::GetCurrentWindow();
    if (hwnd_ && hwnd_ != prev_hwnd_) {
        // �����ǰ�����ͣ����, ˵���Ǵ�Ĭ�ϴ����ϰ������, ���ߴ�ͣ��״̬ȡ���Ĵ���, ��Ҫ�����ö�״̬
        // �����ǰ������ͣ����, �򲻸ı��ö�״̬
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
