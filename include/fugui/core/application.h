#pragma once
#include <memory>
#include <string_view>

namespace fugui {
class Application
{
public:
	Application();
    ~Application();

    int Execute(bool hide_main_window = true, std::u8string_view window_title = u8"FuGui App");

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
}
