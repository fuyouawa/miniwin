#pragma once
#include <functional>
#include <thread>

#include <miniwin/tools/list.h>
#include <miniwin/tools/string.h>

namespace miniwin {
class PlatformWindow;
using SharedPlatformWindow = std::shared_ptr<PlatformWindow>;

class Application
{
public:
    static Application& Instance();

    virtual ~Application();

    virtual String IniFileName() const = 0;
    virtual void SetIniFileName(const String& filename) = 0;

    virtual bool IsIniFileEnabled() const = 0;
    virtual void EnabledIniFile(bool b) = 0;

    virtual bool IsDone() const = 0;
    virtual bool IsExecuting() const = 0;
    virtual int Execute() = 0;

    virtual const List<SharedPlatformWindow>& MainWindows() = 0;
    virtual void PushPendingFunctor(std::function<void()> func) = 0;

    virtual std::thread::id ThreadId() const = 0;
};
}
