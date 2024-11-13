#pragma once
#include <functional>
#include <vector>
#include <queue>
#include <mutex>

#include <miniwin/tools/list.h>
#include <miniwin/core/global.h>

namespace miniwin {
class Window;
class Widget;

class WidgetsDriver
{
public:
    static WidgetsDriver& instance();
    ~WidgetsDriver();

    bool IsDone() const;
    void CloseAll();
    void RegisterWindow(Window* window);

    void PushPendingFunctor(std::function<void()>&& func);

    std::thread::id UiThreadId() const;

    WidgetId AllocId();
    bool RecycleId(WidgetId id);

private:
    friend class Application;
    enum class Operation
    {
        kAdd,
        kCloseAll
    };

    static void UpdateRecursion(Widget* widget, bool force_ignore_children = false);
    static void CallUpdateEarlyRecursion(Widget* widget);
    static void ClearDirtyRecursion(Widget* widget);
    void Update();
    void ClearDirty();
    void CallUpdateEarly() const;
    void DoPending();

    WidgetId cur_max_id_;
    uint8_t id_pool_seek_;
    WidgetId id_pool_[128];

    std::thread::id ui_thread_id_;
    mutable std::mutex mutex_;

    List<Window*> windows_;
    List<std::function<void()>> pending_functors_;
};
}
