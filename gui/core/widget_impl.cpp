#include "gui/core/widget_impl.h"

#include "fugui/widgets/window.h"
#include "imgui/imgui.h"
#include <ranges>

namespace fugui {
Widget::Impl::Impl(Widget* owner)
    : enable_sc_(true),
    visible_sc_(true),
    is_painting_children_(false),
    widget_type_(), owner_(owner)
{
}

Widget::Impl::~Impl()
{
}

void Widget::Impl::Close()
{
    orphaned_ = true;
    if (widget_type_ != WidgetType::kWindow)
    {
        auto p = widget_parent();
        assert(p);
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

const Widget* Widget::Impl::widget_parent() const
{
    auto p = dynamic_cast<const Widget*>(owner_->parent());
    assert(p);
    return p;
}

void Widget::Impl::set_widget_parent(Widget* parent)
{
    PushPendingFunctor([this, parent]
        {
            // 先通知老的parent
            widget_parent()->impl_->OnChildrenChanged();
            owner_->set_parent(parent);
            // 通知新的parent
            parent->impl_->OnChildrenChanged();
        });
}

void Widget::Impl::OnChildrenChanged()
{
    widget_children_.clear();
    for (const auto c : owner_->children())
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

bool Widget::Impl::visible() const
{
    auto v = visible_sc_.get();
    if (!v)
    {
        return false;
    }
    auto p = owner_->widget_parent();
    if (!p)
    {
        return v;
    }
    return p->visible();
}

void Widget::Impl::set_visible(bool b)
{
    visible_sc_.set_control(b);
}

bool Widget::Impl::enabled() const
{
    auto v = enable_sc_.get();
    if (!v)
    {
        return false;
    }
    auto p = owner_->widget_parent();
    if (!p)
    {
        return v;
    }
    return p->enabled();
}

void Widget::Impl::set_enable(bool b)
{
    enable_sc_.set_control(b);
}
}
