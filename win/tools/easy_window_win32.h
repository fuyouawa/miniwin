#pragma once
#include "easy_window.h"

#include <Windows.h>
#include <d3d11.h>

#include <miniwin/tools/vector4d.h>

namespace miniwin {
class EasyWindowWin32 : public EasyWindow {
public:
	EasyWindowWin32(const String& title, const Vector2DInt& size, bool client_size, FlagsType styles,
		const SharedEasyWindow& parent);

	~EasyWindowWin32() override;

	const wchar_t* ClassName();

	void Show(bool show_or_hide = true) override;

	bool IsFocused() const override;

	void SetFocus() override;

	void SetSize(const Vector2DInt& size, bool client) override;

	void SetPosition(const Vector2DInt& pos, bool client) override;

	void SetMaximized(bool b) override;

	void SetMinimized(bool b) override;

	void SetTitle(const String& title) override;

	void SetAlpha(uint8_t alpha) override;

	void SetCursor(CursorType cursor) override;

	Vector2DInt Size() const override;

	Vector2DInt Position() const override;

	bool IsMaximized() const override;

	bool IsMinimized() const override;

	void* PlatformHandle() const override;

	bool Update() override;

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	void Repaint() override;

	Vector2DInt ClientSize() const override;
	Vector2DInt ClientPosition() const override;

	Vector2DInt resize_{};
	size_t delta_time_ = 0;
	size_t fps_ = 60;
	HWND hwnd_ = nullptr;
	RECT border_thickness_{};
	HINSTANCE instance_;
	FlagsType styles_ = kStyleNormal;
	CursorType cursor_ = kCursorArrow;

	std::function<void(RectInt rect, uint16_t dpi)> on_dpi_changed_;
	std::function<bool(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)> on_wnd_proc_;
};

}