#pragma once
#include <miniwin/core/application.h>

#include <thread>

#include <miniwin/core/main_window.h>
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

	const List<SharedMainWindow>& MainWindows() override;

	void RegisterMainWindow(const SharedMainWindow& window);

	String ini_filename_;
	size_t fps_ = 60;
	List<SharedMainWindow> main_windows_;
	bool is_executing_ = false;
	float delta_time_ = 0;
	uint64_t frame_count_ = 0;
};
}