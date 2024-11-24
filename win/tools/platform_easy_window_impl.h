#pragma once
#include "platform_easy_window.h"

namespace miniwin {
class PlatformEasyWindowImpl : public PlatformEasyWindow {
public:
	PlatformEasyWindowImpl(const String& title, const Vector2DInt& size, bool client_size,
		FlagsType styles, const SharedPlatformEasyWindow& parent);

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
	void SetCursor(EasyWindow::CursorType cursor) override;
	Vector2DInt Size() const override;
	Vector2DInt Position() const override;
	bool IsMaximized() const override;
	bool IsMinimized() const override;
	bool Update() override;
	void* PlatformHandle() const override;

	virtual void OnResized(Vector2DInt size) = 0;
	Vector2DInt ClientSize() const override;
	Vector2DInt ClientPosition() const override;

	SharedEasyWindow win_;
};
}