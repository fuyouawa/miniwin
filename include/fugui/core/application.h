#pragma once
#include <fugui/internal/framework/core_application.h>

namespace fugui {
class Application : public internal::CoreApplication
{
public:
	Application();

protected:
	void OnInitizlize() override;
	void OnProcess() override;
	bool IsDone() override;
	void OnAppExit() override;

	void OnDpiScaleChanged() override;

	void WindowWannaClose() override;

	bool close_in_next_frame_;
};
}