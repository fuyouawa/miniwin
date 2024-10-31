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
        auto it = windows_.RemoveIf([](auto w) { return w->Orphaned(); });
        if (it != windows_.end())
        {
            auto tmp = it;
            for (; tmp != windows_.end(); ++tmp)
                delete* tmp;
            windows_.Erase(it, windows_.end());
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
    PushPendingFunctor([window, this] { windows_.PushBack(window); });
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
    if (widget->Visible())
    {
        widget->PreparePaint();
        for (auto& o : widget->Children())
        {
	        if (auto w = dynamic_cast<Widget*>(o))
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
        auto& wc = widget->impl_->widget_children_;
        auto it = wc.RemoveIf([](auto w) { return w->Orphaned(); });
        assert(it != wc.end());
        auto tmp = it;
        for (; tmp != wc.end(); ++tmp)
	        delete* tmp;
        wc.Erase(it, wc.end());

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
