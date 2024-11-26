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

    const List<SharedWindow>& Windows();

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
    void CallUpdateEarly() const;

    mutable std::mutex mutex_;

    List<SharedWindow> windows_;
};
}
