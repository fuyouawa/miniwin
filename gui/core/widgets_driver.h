#pragma once
#include <vector>
#include <queue>
#include <mutex>

namespace fugui {
class Window;
class Widget;

class WidgetsDriver
{
public:
    static WidgetsDriver& instance();

    bool IsDone() const;
    void CloseAll();
    void RegisterWindow(Window* window);

    std::thread::id ui_thread_id() const;

private:
    friend class Application;
    enum class Operation
    {
        kAdd,
        kCloseAll
    };
    using PendingOperationsQueue = std::queue<std::pair<Operation, Window*>>;

    static void UpdateRecursion(Widget* widget);
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
