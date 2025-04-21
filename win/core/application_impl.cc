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
	thread_id_ = std::this_thread::get_id();					// 记录主线程ID
	while (true) {
		auto start_time = std::chrono::steady_clock::now();		// 开始时间

		DoPendingFunctors();									// 处理待处理函数
		ClearDoneWindow();										// 清理已经完成（死亡）的窗体

		if (IsDone())											// 如果完成（没有窗体在运行了）就退出
			break;

		for (auto& win : platform_windows_) {					// 更新所有平台窗体（主窗体）
			win->Update();
		}

		auto end_time = std::chrono::steady_clock::now();		// 结束时间

		// 计算上面这些逻辑需要的时间（开始时间减结束时间）
		auto logic_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
		// 根据设定的FPS计算每帧休眠时间
		auto sleep_time = std::chrono::milliseconds(1000ull / fps_);
		// 假设休眠时间为0.2s，逻辑运行时间为0.15s
		// 那么实际所需休眠时间为0.2s - 0.15s = 0.05s
		// 如果逻辑运行时间比休眠时间长，就不休眠
		if (sleep_time > logic_time) {
			std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time - logic_time));
		}
		// 计算当前帧的时间
		delta_time_ = std::max(sleep_time, logic_time);
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

void ApplicationImpl::DoPendingFunctors() {
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

void ApplicationImpl::ClearDoneWindow() {
	platform_windows_.EraseIf([](const SharedPlatformWindow& win) {
		return win->IsDone();
	});
}
}
