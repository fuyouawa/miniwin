#include "application_impl.h"

#include <mutex>

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
	thread_id_ = std::this_thread::get_id();
	while (true) {
		DoPending();
		platform_windows_.EraseIf([](const SharedPlatformWindow& win) { return win->IsDone(); });

		if (IsDone())
			break;

		delta_time_ = 0;
		for (auto& win : platform_windows_) {
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

const List<SharedPlatformWindow>& ApplicationImpl::MainWindows() {
	return platform_windows_;
}

void ApplicationImpl::RegisterMainWindow(const SharedPlatformWindow& window) {
	platform_windows_.PushBack(window);
}

void ApplicationImpl::PushPendingFunctor(std::function<void()> func) {
	std::lock_guard lk(mutex_);
	pending_functors_.EmplaceBack(std::move(func));
}

void ApplicationImpl::DoPending() {
	List<std::function<void()>> functors;
	{
		std::lock_guard lk(mutex_);
		functors.Swap(pending_functors_);
	}
	for (auto& f : functors) {
		f();
	}
	functors.Clear();
}

std::thread::id ApplicationImpl::ThreadId() const {
	return thread_id_;
}

bool ApplicationImpl::IsDone() const {
	return platform_windows_.empty() && pending_functors_.empty();
}
}
