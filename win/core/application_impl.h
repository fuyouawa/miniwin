#pragma once
#include <miniwin/core/application.h>

#include <mutex>
#include <thread>

#include <miniwin/core/platform_window.h>
#include <miniwin/tools/list.h>

namespace miniwin {
class ApplicationImpl : public Application {
public:
	ApplicationImpl();

	~ApplicationImpl() override = default;

	String IniFileName() const override;

	void SetIniFileName(const String& filename) override;

	bool IsIniFileEnabled() const override;

	void EnabledIniFile(bool b) override;

	bool IsExecuting() const override;

	int Execute() override;

	const List<SharedPlatformWindow>& MainWindows() override;

	void RegisterMainWindow(const SharedPlatformWindow& window);
	void PushPendingFunctor(std::function<void()> func) override;
	void DoPending();
	std::thread::id ThreadId() const override;
	bool IsDone() const override;

	String ini_filename_;
	size_t fps_ = 60;
	List<SharedPlatformWindow> platform_windows_;
	List<std::function<void()>> pending_functors_;
	std::mutex mutex_;
	bool is_executing_ = false;
	float delta_time_ = 0;
	uint64_t frame_count_ = 0;
	std::thread::id thread_id_;
};
}