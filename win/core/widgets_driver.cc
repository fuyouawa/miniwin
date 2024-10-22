#include "win/core/widgets_driver.h"
#include "win/core/widget_impl.h"
#include "win/widgets/window_impl.h"

#include <cassert>

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
    DoPendingOperations();
    CallUpdateEarly();
    for (auto& win : windows_)
    {
        if (!win->Orphaned() && win->Visible())
        {
            UpdateRecursion(win);
        }
    }
}

void WidgetsDriver::ClearDirty()
{
    {
        std::vector<std::vector<Window*>::iterator> orphaned_win_iters;
        for (auto it = windows_.begin(); it != windows_.end(); ++it)
        {
            if ((*it)->Orphaned())
            {
                orphaned_win_iters.push_back(it);
            }
        }
        for (auto it : orphaned_win_iters)
        {
            auto w = *it;
            windows_.erase(it);
            delete w;
        }
    }
    for (auto& win : windows_)
    {
        assert(!win->Orphaned());
        ClearDirtyRecursion(win);
    }
}

void WidgetsDriver::CallUpdateEarly()
{
    for (auto& win : windows_)
    {
        CallUpdateEarlyRecursion(win);
    }
}

void WidgetsDriver::DoPendingOperations()
{
    PendingOperationsQueue queue;
    {
        std::lock_guard lk{ mutex_ };
        queue.swap(pending_operations_);
    }
    while (!queue.empty())
    {
        auto& op = queue.front();
        switch (op.first)
        {
        case Operation::kAdd:
        {
            windows_.push_back(op.second);
            break;
        }
        case Operation::kCloseAll:
        {
            for (auto& win : windows_)
            {
                delete win;
            }
            windows_.clear();
            break;
        }
        }
        queue.pop();
    }
}

bool WidgetsDriver::IsDone() const
{
    return windows_.empty() && pending_operations_.empty();
}

void WidgetsDriver::CloseAll()
{
    std::lock_guard lk{ mutex_ };
    pending_operations_.emplace(Operation::kCloseAll, nullptr);
}

void WidgetsDriver::RegisterWindow(Window* window)
{
    std::lock_guard lk{ mutex_ };
    pending_operations_.emplace(Operation::kAdd, window);
}

std::thread::id WidgetsDriver::UiThreadId() const
{
    return ui_thread_id_;
}

void WidgetsDriver::UpdateRecursion(Widget* widget)
{
    assert(widget->Visible());

    auto ignore_self = (widget->DrawFlags() & WidgetDrawFlags::kIgnoreSelfDraw) != WidgetDrawFlags::kNone;
    auto ignore_children = (widget->DrawFlags() & WidgetDrawFlags::kIgnoreChildrenDraw) != WidgetDrawFlags::kNone;

    if (!ignore_self) {
        widget->PaintBegin();
    }

    if (!ignore_children)
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
        std::vector<std::vector<Widget*>::const_iterator> orphaned_children_iters;
        for (auto it = wc.begin(); it != wc.end(); ++it)
        {
            if ((*it)->Orphaned())
            {
                orphaned_children_iters.push_back(it);
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
}
