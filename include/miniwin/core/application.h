#pragma once
#include <memory>

#include <miniwin/core/global.h>
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

    const String& IniFileName() const;
    void SetIniFileName(const String& filename);

    bool IsIniFileEnabled() const;
    void EnabledIniFile(bool b);

    size_t Fps() const;
    void SetFps(size_t fps);

    uint64_t FrameCount() const;
    bool IsExecuting() const;

    int Execute();

    _MW_IMPL
};
}
