#pragma once
#include <memory>

#include <miniwin/tools/string.h>


namespace miniwin {
class Application
{
public:
    struct Config {
        bool hide_main_window;

    };

    static const Application* instance();

	Application();
    ~Application();

    bool IsHideMainWindow() const;
    void SetHideMainWindow(bool b);

    const String& MainWindowClassName() const;
    void MainWindowClassName(const String& class_name);

    const String& MainWindowTitle() const;
    void SetMainWindowTitle(const String& title) const;

    size_t Fps() const;
    void SetFps(size_t fps);

    uint64_t FrameCount() const;
    bool IsExecuting() const;

    int Execute();

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
}
