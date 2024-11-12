#include "widget_impl.h"

#include <ranges>

#include <miniwin/widgets/window.h>
#include <miniwin/core/imgui.h>

#include "widgets_driver.h"

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
    enable_sc_.Enter();
    visible_sc_.Enter();
    size_sc_.Enter();
    pos_sc_.Enter();

    if (enable_sc_.HasChange()) {
        owner_->OnEnableChanged(enable_sc_.cur_value());
    }

    if (visible_sc_.HasChange()) {
        owner_->OnVisbleChanged(visible_sc_.cur_value());
    }

    if (size_sc_.HasChange())
    {
        owner_->OnSizeChanged(size_sc_.cur_value(), size_sc_.prev_value());
    }

    if (pos_sc_.HasChange())
    {
        owner_->OnPositionChanged(pos_sc_.cur_value(), pos_sc_.prev_value());
    }

    imgui::BeginDisabled(!enable_sc_.cur_value());
    imgui::PushID(owner_->Id());
}

void Widget::Impl::PaintEnd()
{
    imgui::PopID();
    imgui::EndDisabled();
    enable_sc_.Exit();
    visible_sc_.Exit();
    size_sc_.Exit();
    pos_sc_.Exit();
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
    WidgetsDriver::instance().PushPendingFunctor([this, parent]
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
    widget_children_.Clear();
    for (const auto c : owner_->Children())
    {
        auto w = dynamic_cast<Widget*>(c);
        if (w)
        {
            widget_children_.PushBack(w);
        }
    }
}

void Widget::Impl::PushPendingFunctor(std::function<void()>&& func)
{
    std::lock_guard lk(pending_functors_mutex_);
    pending_functors_.EmplaceBack(std::move(func));
}

void Widget::Impl::DoPendingFunctors()
{
    List<std::function<void()>> functors;
    {
        std::lock_guard lk(pending_functors_mutex_);
        functors.Swap(pending_functors_);
    }
    for (auto& f : functors)
    {
        f();
    }
    functors.Clear();
}

bool Widget::Impl::Visible() const
{
    auto v = visible_sc_.cur_value();
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
    visible_sc_.SetControl(b);
}

bool Widget::Impl::Enabled() const
{
    auto v = enable_sc_.cur_value();
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
    enable_sc_.SetControl(b);
}
}
