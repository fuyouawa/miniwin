#pragma once
#include <vector>
#include <mutex>

namespace fugui {
class Window;
class Widget;

class WidgetsDriver
{
public:
    static WidgetsDriver& instance();

    void Update();
    bool IsEmpty() const;
    void CloseAll();
    void RegisterWindow(Window* window);
    void UnRegisterWindow(Window* window);

private:
    static void UpdateRecursion(const Widget* widget);

    mutable std::mutex mutex_;
    std::vector<Window*> windows_;
};
}
