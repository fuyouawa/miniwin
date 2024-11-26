#pragma once
#include <miniwin/core/platform_window.h>

#include "widgets_driver.h"
#include "win/tools/easy_window.h"
#include "win/tools/platform_easy_window.h"

namespace miniwin {
class PlatformWindowImpl : public PlatformWindow {
public:
	PlatformWindowImpl(
		const String& title,
		const Vector2DInt& size,
		bool adjust_size,
		FlagsType styles,
		const SharedPlatformWindow& parent);
	~PlatformWindowImpl() override;

	virtual void Initialize();

	void Repaint() override;
	void Show(bool show_or_hide) override;
	bool IsFocused() const override;
	void SetFocus() override;
	void SetSize(const Vector2DInt& size, bool adjust) override;
	void SetPosition(const Vector2DInt& pos, bool adjust) override;
	void SetMaximized(bool b) override;
	void SetMinimized(bool b) override;
	void SetTitle(const String& title) override;
	void SetAlpha(uint8_t alpha) override;
	void SetCursor(CursorType cursor) override;
	Vector2DInt Size() const override;
	Vector2DInt Position() const override;
	bool IsMaximized() const override;
	bool IsMinimized() const override;
	uint64_t FrameCount() const override;
	float DeltaTime() const override;
	bool IsDone() const override;
	void* PlatformHandle() const override;
	bool Update() override;
	bool AdjustDpiScale(float scale);

	virtual void PlatformPreRender() = 0;
	virtual void PlatformStartFrame() = 0;
	virtual void PlatformAdditionRender() = 0;
	void RegisterSubWindow(const SharedWindow& win);
	const List<SharedWindow>& SubWindows() override;
	Vector2DInt ClientSize() const override;
	Vector2DInt ClientPosition() const override;
	bool IsUpdated() override;

	float cur_dpi_scale_ = 0;
	float prev_dpi_scale_ = 0;
	SharedPlatformEasyWindow platform_win_;
	WidgetsDriver driver_;
	uint64_t frame_count_ = 0;
	size_t delta_time_ = 0;
	bool orphaned_ = false;
	bool updated_ = false;
};
}
