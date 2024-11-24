#pragma once
#include "easy_window.h"

namespace miniwin {
class PlatformEasyWindow;
using SharedPlatformEasyWindow = std::shared_ptr<PlatformEasyWindow>;

class PlatformEasyWindow {
public:
	static SharedPlatformEasyWindow Create(
		const String& title,
		const Vector2DInt& size,
		bool client_size = true,
		FlagsType styles = EasyWindow::kStyleNormal,
		const SharedPlatformEasyWindow& parent = nullptr);

	virtual ~PlatformEasyWindow();

	static SharedEasyWindow Create(
		const String& title,
		const Vector2DInt& size,
		bool adjust_size = true,
		FlagsType styles = EasyWindow::kStyleNormal,
		const SharedEasyWindow& parent = nullptr);

	virtual void Repaint() = 0;
	virtual void Show(bool show_or_hide = true) = 0;
	virtual bool IsFocused() const = 0;
	virtual void SetFocus() = 0;

	virtual void SetSize(const Vector2DInt& size, bool adjust = true) = 0;
	virtual void SetPosition(const Vector2DInt& pos, bool adjust = true) = 0;
	virtual void SetMaximized(bool b) = 0;
	virtual void SetMinimized(bool b) = 0;
	virtual void SetTitle(const String& title) = 0;
	virtual void SetAlpha(uint8_t alpha) = 0;
	virtual void SetCursor(EasyWindow::CursorType cursor) = 0;

	virtual Vector2DInt ClientSize() const = 0;
	virtual Vector2DInt Size() const = 0;
	virtual Vector2DInt ClientPosition() const = 0;
	virtual Vector2DInt Position() const = 0;

	virtual bool IsMaximized() const = 0;
	virtual bool IsMinimized() const = 0;

	virtual bool Update() = 0;

	virtual void* PlatformHandle() const = 0;

	virtual bool PreRender() = 0;
	virtual void Render() = 0;
	virtual void Present() = 0;

	std::function<void(Vector2DInt size)> on_resized_;
	std::function<void(Vector2DInt pos)> on_moved_;
	std::function<void(bool force)> on_forced_;
	std::function<bool()> on_close_;
};
}