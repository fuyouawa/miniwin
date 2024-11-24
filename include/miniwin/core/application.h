#pragma once
#include <miniwin/tools/list.h>
#include <miniwin/tools/string.h>

namespace miniwin {
class MainWindow;
using SharedMainWindow = std::shared_ptr<MainWindow>;

class Application
{
public:
    static Application& Instance();

    virtual ~Application();

    virtual String IniFileName() const = 0;
    virtual void SetIniFileName(const String& filename) = 0;

    virtual bool IsIniFileEnabled() const = 0;
    virtual void EnabledIniFile(bool b) = 0;

    virtual bool IsExecuting() const = 0;
    virtual int Execute() = 0;

    virtual const List<SharedMainWindow>& MainWindows() = 0;
};
}
