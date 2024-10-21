#include "win/core/widget_impl.h"

#include "miniwin/widgets/window.h"
#include "imgui/imgui.h"
#include <ranges>

namespace miniwin {
Widget::Impl::Impl(Widget* owner)
	:owner_(owner)
{
}

Widget::Impl::~Impl()
{
}

void Widget::Impl::Close()
{
    orphaned_ = true;
    auto p = WidgetParent();
    if (p)
    {
        p->impl_->dirty_ = true;
    }
}

void Widget::Impl::PaintBegin()
{
    enable_sc_.Entry();
    visible_sc_.Entry();

    if (enable_sc_.is_changed()) {
        owner_->OnEnableChanged(*enable_sc_);
        owner_->DoEnable(*enable_sc_);
    }

    if (visible_sc_.is_changed()) {
        if (*visible_sc_) {
            owner_->DoShow();
        }
        else {
            owner_->DoHide();
        }
        owner_->OnVisbleChanged(*visible_sc_);
    }
    if (!*enable_sc_) {
        ImGui::BeginDisabled();
    }
}

void Widget::Impl::PaintEnd()
{
    if (!*enable_sc_) {
        ImGui::EndDisabled();
    }
    enable_sc_.Exit();
    visible_sc_.Exit();
}

const Widget* Widget::Impl::WidgetParent() const
{
    if (auto p = owner_->Parent())
    {
        auto p2 = dynamic_cast<const Widget*>(p);
        return p2;
    }
    return nullptr;
}

void Widget::Impl::SetWidgetParent(Widget* parent)
{
    PushPendingFunctor([this, parent]
        {
            // 先通知老的parent
            WidgetParent()->impl_->OnChildrenChanged();
            owner_->SetParent(parent);
            // 通知新的parent
            parent->impl_->OnChildrenChanged();
        });
}

void Widget::Impl::OnChildrenChanged()
{
    widget_children_.clear();
    for (const auto c : owner_->Children())
    {
        auto w = dynamic_cast<Widget*>(c);
        if (w)
        {
            widget_children_.push_back(w);
        }
    }
}

void Widget::Impl::PushPendingFunctor(std::function<void()>&& func)
{
    std::lock_guard lk{ pending_functors_mutex_ };
    pending_functors_.emplace(std::move(func));
}

void Widget::Impl::DoPendingFunctors()
{
    std::queue<std::function<void()>> queue;
    {
        std::lock_guard lk{ pending_functors_mutex_ };
        queue.swap(pending_functors_);
    }

    while (!queue.empty())
    {
        auto& func = queue.front();
        func();
        queue.pop();
    }
}

bool Widget::Impl::Visible() const
{
    auto v = visible_sc_.get();
    if (!v)
    {
        return false;
    }
    auto p = owner_->WidgetParent();
    if (!p)
    {
        return v;
    }
    return p->Visible();
}

void Widget::Impl::SetVisible(bool b)
{
    visible_sc_.set_control(b);
}

bool Widget::Impl::Enabled() const
{
    auto v = enable_sc_.get();
    if (!v)
    {
        return false;
    }
    auto p = owner_->WidgetParent();
    if (!p)
    {
        return v;
    }
    return p->Enabled();
}

void Widget::Impl::SetEnable(bool b)
{
    enable_sc_.set_control(b);
}
}
