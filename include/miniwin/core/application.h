#pragma once
#include <memory>

#include <miniwin/defs.h>
#include <miniwin/tools/string.h>

namespace miniwin {
struct BeginNewFrameEvent {
    size_t total_frame;
};

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

    String MainWindowClassName() const;
    void MainWindowClassName(const String& class_name);

    String MainWindowTitle() const;
    void SetMainWindowTitle(const String& title) const;

    String IniFileName() const;
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
