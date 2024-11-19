#include "application_impl.h"

#include <thread>

#include <imgui/imgui.h>
#include <miniwin/tools/mathf.h>
#include <miniwin/core/event_mgr.h>
#include "widgets_driver.h"
#include "win/tools/debug.h"

namespace miniwin {
Application* Application::Impl::instance_ = nullptr;

Application::Impl::Impl(Application* owner)
	: owner_(owner) {
	MW_ASSERT_X(instance_ == nullptr);
	instance_ = owner_;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;
	//io.ConfigViewportsNoDefaultParent = true;
	//io.ConfigDockingAlwaysTabBar = true;
	//io.ConfigDockingTransparentPayload = true;
	//io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;     // FIXME-DPI: Experimental. THIS CURRENTLY DOESN'T WORK AS EXPECTED. DON'T USE IN USER APP!
	//io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports; // FIXME-DPI: Experimental.
}

Application::Impl::~Impl() {
	instance_ = nullptr;
}

void Application::Impl::OnAppStart() {
	is_executing_ = true;
}

void Application::Impl::OnProcess() {
	EventManager::Instance().OnBeginNewFrame(frame_count_);
	WidgetsDriver::Instance().Update();
	++frame_count_;
	if (close_in_next_frame_) {
		MW_ASSERT_X(IsDone());
	}
}

bool Application::Impl::IsDone() {
	return WidgetsDriver::Instance().IsDone();
}

void Application::Impl::OnAppExit() {
	is_executing_ = false;
}

bool Application::Impl::SetDpiScale(float scale) {
	cur_dpi_scale_ = scale > 1.0f ? scale : 1.0f;
	bool changed = !Mathf::Approximately(cur_dpi_scale_, prev_dpi_scale_);
	prev_dpi_scale_ = cur_dpi_scale_;
	return changed;
}

void Application::Impl::WindowWannaClose() {
	WidgetsDriver::Instance().CloseAll();
	close_in_next_frame_ = true;
}

void Application::Impl::DoFps() const {
	auto sleep_time = 1000 / fps_;
	if (sleep_time > delta_time_) {
		std::this_thread::sleep_for(std::chrono::milliseconds{sleep_time - delta_time_});
	}
}
}
