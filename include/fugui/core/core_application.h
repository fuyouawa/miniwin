#pragma once
#include <fugui/tools/property.h>
#include <fugui/tools/container.h>

namespace fugui {
class CoreApplication : public NonCopyable
{
public:
	CoreApplication();

	int Execute(bool hide_main_window = true, std::u8string_view window_title = u8"FuGui App");

	bool is_executing() const { return is_executing_; }

protected:
	virtual void OnInitizlize() = 0;
	virtual void OnProcess() = 0;
	virtual bool IsDone() = 0;
	virtual void OnDpiScaleChanged() = 0;
	virtual void OnAppExit() = 0;

	virtual void WindowWannaClose() = 0;

	void DoFps();

	bool is_executing_;
	unsigned fps_;
	size_t delta_time_;
	Vector2 cur_scale_;
	Vector2 prev_scale_;
};
}