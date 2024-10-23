#pragma once
#include <vector>
#include <queue>
#include <mutex>

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

    std::thread::id UiThreadId() const;

private:
    friend class Application;
    enum class Operation
    {
        kAdd,
        kCloseAll
    };
    using PendingOperationsQueue = std::queue<std::pair<Operation, Window*>>;

    static void UpdateRecursion(Widget* widget, bool force_ignore_children = false);
    static void CallUpdateEarlyRecursion(Widget* widget);
    static void ClearDirtyRecursion(Widget* widget);
    void Update();
    void ClearDirty();
    void CallUpdateEarly();
    void DoPendingOperations();

    std::thread::id ui_thread_id_;
    std::vector<Window*> windows_;
    mutable std::mutex mutex_;
    PendingOperationsQueue pending_operations_;
};
}
