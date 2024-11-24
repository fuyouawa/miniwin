#include "application_impl.h"

#include "win/tools/debug.h"
#include <imgui/imgui.h>

namespace miniwin {
ApplicationImpl::ApplicationImpl() {
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

String ApplicationImpl::IniFileName() const {
	return ini_filename_;
}

void ApplicationImpl::SetIniFileName(const String& filename) {
	ini_filename_ = filename;
}

bool ApplicationImpl::IsIniFileEnabled() const {
	return ImGui::GetIO().IniFilename != nullptr;
}

void ApplicationImpl::EnabledIniFile(bool b) {
	ImGui::GetIO().IniFilename = b ? ini_filename_.data() : nullptr;
}

bool ApplicationImpl::IsExecuting() const {
	return is_executing_;
}

int ApplicationImpl::Execute() {
	while (true) {
		main_windows_.EraseIf([](const SharedMainWindow& win) { return win->Orphaned(); });

		if (main_windows_.empty())
			break;

		delta_time_ = 0;
		for (auto& win : main_windows_) {
			win->Update();
			delta_time_ += win->DeltaTime();
		}

		auto sleep_time = 1000 / fps_;
		auto dt = static_cast<size_t>(delta_time_ * 1000);
		if (sleep_time > dt) {
			std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time - dt));
		}
	}

	return 0;
}

const List<SharedMainWindow>& ApplicationImpl::MainWindows() {
	return main_windows_;
}

void ApplicationImpl::RegisterMainWindow(const SharedMainWindow& window) {
	main_windows_.PushBack(window);
}
}
