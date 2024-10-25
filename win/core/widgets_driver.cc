#include "widgets_driver.h"

#include <cassert>

#include "win/core/widget_impl.h"
#include "win/widgets/window_impl.h"

namespace miniwin {
WidgetsDriver& WidgetsDriver::instance()
{
    static WidgetsDriver inst;
    static bool initialized = false;
    if (!initialized)
    {
        inst.ui_thread_id_ = std::this_thread::get_id();
        initialized = true;
    }
    return inst;
}

WidgetsDriver::~WidgetsDriver()
{
    CloseAll();
}

void WidgetsDriver::Update()
{
    ClearDirty();
    DoPending();
    CallUpdateEarly();
    for (auto& win : windows_)
    {
        if (!win->Orphaned() && win->Visible())
        {
            UpdateRecursion(win, win->IsCollapsed());
        }
    }
}

void WidgetsDriver::ClearDirty()
{
    {
        List<List<Window*>::iterator> orphaned_win_iters;
        for (auto it = windows_.begin(); it != windows_.end(); ++it)
        {
            if ((*it)->Orphaned())
            {
                orphaned_win_iters.PushBack(it);
            }
        }
        for (auto it : orphaned_win_iters)
        {
            auto w = *it;
            windows_.Erase(it);
            delete w;
        }
    }
    for (auto& win : windows_)
    {
        assert(!win->Orphaned());
        ClearDirtyRecursion(win);
    }
}

void WidgetsDriver::CallUpdateEarly() const
{
    for (auto& win : windows_)
    {
        CallUpdateEarlyRecursion(win);
    }
}

void WidgetsDriver::DoPending()
{
    List<std::function<void()>> functors;
    {
        std::lock_guard lk(mutex_);
        functors.Swap(pending_functors_);
    }
    for (auto& f : functors)
    {
        f();
    }
    functors.Clear();
}

bool WidgetsDriver::IsDone() const
{
    return windows_.empty() && pending_functors_.empty();
}

void WidgetsDriver::CloseAll()
{
    PushPendingFunctor([this]
        {
            for (auto& win : windows_)
            {
                delete win;
            }
            windows_.Clear();
        });
}

void WidgetsDriver::RegisterWindow(Window* window)
{
    PushPendingFunctor([=, this] { windows_.PushBack(window); });
}

std::thread::id WidgetsDriver::UiThreadId() const
{
    return ui_thread_id_;
}

void WidgetsDriver::UpdateRecursion(Widget* widget, bool force_ignore_children)
{
    if (!widget->Visible())
        return;

    auto ignore_self = (widget->DrawFlags() & Widget::kDrawIgnoreSelf) != 0;
    auto ignore_children = (widget->DrawFlags() & Widget::kDrawIgnoreChildren) != 0;

    if (!ignore_self) {
        widget->PaintBegin();
    }

    if (!ignore_children || force_ignore_children)
    {
        size_t i = 0;
        for (auto& o : widget->Children())
        {
            auto w = dynamic_cast<Widget*>(o);
            if (w && !w->Orphaned())
            {
                widget->OnBeforePaintChild(i);
                UpdateRecursion(w);
                widget->OnAfterPaintChild(i);
                ++i;
            }
        }
    }

    if (!ignore_self) {
        widget->PaintEnd();
    }
}

void WidgetsDriver::CallUpdateEarlyRecursion(Widget* widget)
{
    static Widget* win = widget;
    if (widget->Visible())
    {
        widget->PreparePaint();
        for (auto& o : widget->Children())
        {
            auto w = dynamic_cast<Widget*>(o);
            if (w)
            {
                CallUpdateEarlyRecursion(w);
            }
        }
    }
}

void WidgetsDriver::ClearDirtyRecursion(Widget* widget)
{
    if (widget->impl_->dirty_)
    {
        auto& wc = widget->WidgetChildren();
        List<List<Widget*>::const_iterator> orphaned_children_iters;
        for (auto it = wc.begin(); it != wc.end(); ++it)
        {
            if ((*it)->Orphaned())
            {
                orphaned_children_iters.PushBack(it);
            }
        }
        for (auto it : orphaned_children_iters)
        {
            delete *it;
        }
        widget->impl_->dirty_ = false;
    }
    for (auto c : widget->WidgetChildren())
    {
        assert(!c->Orphaned());
        ClearDirtyRecursion(c);
    }
}

void WidgetsDriver::PushPendingFunctor(std::function<void()>&& func)
{
    std::lock_guard lk(mutex_);
    pending_functors_.PushBack(std::move(func));
}
}
