#include "gui/core/widgets_driver.h"
#include "gui/core/widget_impl.h"
#include "gui/widgets/window_impl.h"
#include <ranges>

#include <cassert>

namespace fugui {
WidgetsDriver& WidgetsDriver::instance()
{
    static WidgetsDriver inst;
    static bool initialized = false;
    if (!initialized)
    {
        inst.ui_thread_id_ = std::this_thread::get_id();
    }
    return inst;
}

void WidgetsDriver::Update()
{
    ClearDirty();
    DoPendingOperations();
    CallUpdateEarly();
    for (auto& win : windows_)
    {
        if (!win->orphaned())
        {
            UpdateRecursion(win);
        }
    }
}

namespace  {
constexpr auto kOrphanedFilter = std::ranges::views::filter([](const Widget* w) {return w->orphaned(); });
}

void WidgetsDriver::ClearDirty()
{
    auto orphaned_win = windows_ | kOrphanedFilter;
    for (auto it = orphaned_win.begin(); it != orphaned_win.end(); ++it)
    {
        windows_.erase(it.base());
        delete* it;
    }
    for (auto& win : windows_)
    {
        assert(!win->orphaned());
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

bool WidgetsDriver::IsEmpty() const
{
    return windows_.empty();
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

std::thread::id WidgetsDriver::ui_thread_id() const
{
    return ui_thread_id_;
}

void WidgetsDriver::UpdateRecursion(Widget* widget)
{
    if (widget->is_showing())
    {
        widget->PaintBegin();
        for (auto& o : widget->children())
        {
            auto w = dynamic_cast<Widget*>(o);
            if (w && !w->orphaned())
            {
                UpdateRecursion(w);
            }
        }
        widget->PaintEnd();
    }
}

void WidgetsDriver::CallUpdateEarlyRecursion(Widget* widget)
{
    if (widget->is_showing())
    {
        widget->UpdateEarly();
        for (auto& o : widget->children())
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
        auto orphaned_children = widget->widget_children() | kOrphanedFilter;
        for (auto c : orphaned_children)
        {
            delete c;
        }
        widget->impl_->dirty_ = false;
    }
    for (auto c : widget->widget_children())
    {
        assert(!c->orphaned());
        ClearDirtyRecursion(c);
    }
}
}
