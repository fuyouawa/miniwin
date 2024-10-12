#include "gui/core/widgets_driver.h"
#include "gui/widgets/window_impl.h"

#include <cassert>

namespace fugui {
WidgetsDriver& WidgetsDriver::instance()
{
    static WidgetsDriver inst;
    return inst;
}

void WidgetsDriver::Update()
{
    std::lock_guard lk{ mutex_ };
    for (auto& win : windows_)
    {
        UpdateRecursion(win);
    }
}

bool WidgetsDriver::IsEmpty() const
{
    std::lock_guard lk{ mutex_ };
    return windows_.empty();
}

void WidgetsDriver::CloseAll()
{
    std::lock_guard lk{ mutex_ };
    for (auto& w : windows_)
    {
        delete w;
    }
    windows_.clear();
}

void WidgetsDriver::RegisterWindow(Window* window)
{
    std::lock_guard lk{ mutex_ };
    windows_.push_back(window);
}

void WidgetsDriver::UnRegisterWindow(Window* window)
{
    std::lock_guard lk{ mutex_ };
    auto res = std::ranges::find(windows_, window);
    assert(res != windows_.end());
    windows_.erase(res);
}

void WidgetsDriver::UpdateRecursion(const Widget* widget)
{
    if (widget->is_showing())
    {
        widget->PaintBegin();
        for (auto& o : widget->children())
        {
            auto w = dynamic_cast<const Widget*>(o);
            if (w)
            {
                UpdateRecursion(w);
            }
            else
            {
                //TODO 
            }
        }
        widget->PaintEnd();
    }
}
}
