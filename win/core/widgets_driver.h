#pragma once
#include <functional>
#include <mutex>

#include <miniwin/tools/list.h>
#include <miniwin/core/objectdefs.h>

namespace miniwin {
class Window;
class Widget;

class WidgetsDriver
{
public:
    WidgetsDriver();
    ~WidgetsDriver();

    bool IsDone() const;
    void CloseAll();
    void RegisterWindow(const SharedWindow& window);

    void Update();
    void PushPendingFunctor(std::function<void()> func);

    const List<SharedWindow>& Windows();

    std::thread::id UiThreadId() const;

private:
    enum class Operation
    {
        kAdd,
        kCloseAll
    };

    static void UpdateChildrenRecursion(const SharedWidget& widget);
    static void UpdateWidget(const SharedWidget& widget, size_t* index);
    static void UpdateLayout(const SharedLayout& layout, size_t* index);
    static void CallUpdateEarlyRecursion(const SharedWidget& widget);
    static void PrepareRecursion(const SharedWidget& widget);
    void Prepare();
    void CallUpdateEarly() const;
    void DoPending();

    std::thread::id ui_thread_id_;
    mutable std::mutex mutex_;

    List<SharedWindow> windows_;
    List<std::function<void()>> pending_functors_;
};
}
