#pragma once
#include <functional>
#include <vector>
#include <queue>
#include <mutex>

#include <miniwin/tools/list.h>
#include <miniwin/core/objectdefs.h>

namespace miniwin {
class Window;
class Widget;

class WidgetsDriver
{
public:
    static WidgetsDriver& Instance();
    ~WidgetsDriver();

    bool IsDone() const;
    void CloseAll();
    void RegisterWindow(const SharedWindow& window);

    void PushPendingFunctor(std::function<void()> func);

    std::thread::id UiThreadId() const;

private:
    friend class Application;
    enum class Operation
    {
        kAdd,
        kCloseAll
    };

    static void UpdateRecursion(const SharedWidget& widget, bool force_ignore_children = false);
    static void CallUpdateEarlyRecursion(const SharedWidget& widget);
    static void PrepareRecursion(const SharedWidget& widget);
    void Update();
    void Prepare();
    void CallUpdateEarly() const;
    void DoPending();

    std::thread::id ui_thread_id_;
    mutable std::mutex mutex_;

    List<SharedWindow> windows_;
    List<std::function<void()>> pending_functors_;
};
}
