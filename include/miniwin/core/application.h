#pragma once
#include <memory>
#include <string_view>


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

    std::u8string_view MainWindowClassName() const;
    void MainWindowClassName(std::u8string_view class_name);

    std::u8string_view MainWindowTitle() const;
    void SetMainWindowTitle(std::u8string_view title) const;

    size_t Fps() const;
    void SetFps(size_t fps);

    bool IsExecuting() const;

    int Execute();

private:
    static Application* instance_;

    class Impl;
    std::unique_ptr<Impl> impl_;
};
}
