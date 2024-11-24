#include "easy_window_win32.h"

#include "debug.h"

#pragma comment(lib, "D3D11.lib")

namespace miniwin {
#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0 // From Windows SDK 8.1+ headers
#endif

SharedEasyWindow EasyWindow::Create(const String& title, const Vector2DInt& size, bool client_size, FlagsType style_flags,
                                    const SharedEasyWindow& parent) {
	return std::make_shared<EasyWindowWin32>(title, size, client_size, style_flags, parent);
}

EasyWindowWin32::EasyWindowWin32(const String& title, const Vector2DInt& size, bool client_size, FlagsType styles,
	const SharedEasyWindow& parent): styles_(styles) {
	instance_ = GetModuleHandleW(nullptr);

	static bool initialized = false;
	if (!initialized) {
		SetConsoleOutputCP(CP_UTF8);
		WNDCLASSEXW wc{};
		wc.cbSize = sizeof(wc);
		wc.style = CS_CLASSDC;
		wc.lpfnWndProc = WndProc;
		wc.hInstance = instance_;
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
		wc.lpszClassName = ClassName();
		RegisterClassExW(&wc);
		initialized = true;
	}

	DWORD style = 0;
	DWORD ex_style = 0;

	if (style == kStyleNormal) {
		style = WS_OVERLAPPEDWINDOW;
	}
	else {
		if (style & kStyleBorderless) {
			style |= WS_OVERLAPPED | WS_SYSMENU;
		}
		if (style & kStyleResizable) {
			style |= WS_SIZEBOX | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;
		}
		if (style & kStylePopup) {
			style |= WS_POPUP;
		}
	}

	RECT rect(0, 0, size.x(), size.y());
	if (client_size) {
		AdjustWindowRect(&rect, style, FALSE);
	}

	auto wtitle = title.ToStdWString();
	hwnd_ = CreateWindowExW(
		ex_style,
		ClassName(),
		wtitle.data(),
		style,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		parent ? reinterpret_cast<HWND>(parent->PlatformHandle()) : nullptr,
		nullptr,
		GetModuleHandleW(nullptr),
		nullptr);

	if (styles & kStyleResizable) {
		SetRectEmpty(&border_thickness_);
		if (style & WS_THICKFRAME) {
			AdjustWindowRectEx(&border_thickness_, style & ~WS_CAPTION, FALSE, NULL);
			border_thickness_.left *= -1;
			border_thickness_.top *= -1;

			border_thickness_.left += 1;
			border_thickness_.top += 1;
			border_thickness_.right += 1;
			border_thickness_.bottom += 1;
		}
		else if (style & WS_BORDER) {
			SetRect(&border_thickness_, 1, 1, 1, 1);
		}
	}

	SetWindowLongPtrW(hwnd_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	SetWindowPos(hwnd_, nullptr, 0, 0, 0, 0,
	             SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
}

EasyWindowWin32::~EasyWindowWin32() {
	if (!IsWindow(hwnd_))
		return;

	if (hwnd_) {
		SetWindowLongPtrW(hwnd_, GWLP_USERDATA, (LONG_PTR)NULL);

		bool is_active = GetActiveWindow() == hwnd_;
		HWND owner = GetWindow(hwnd_, GW_OWNER);

		DestroyWindow(hwnd_);

		if (is_active && owner != NULL) {
			// HACK : Force active window because on destroy the owner window can be moved in background
			SetActiveWindow(owner);
		}
	}
}

const wchar_t* EasyWindowWin32::ClassName() {
	return L"OsWindowWin32";
}

void EasyWindowWin32::Show(bool show_or_hide) {
	ShowWindow(hwnd_, show_or_hide ? SW_SHOW : SW_HIDE);
}

bool EasyWindowWin32::IsFocused() const {
	return GetForegroundWindow() == hwnd_;
}

void EasyWindowWin32::SetFocus() {
	SetForegroundWindow(hwnd_);
}

void EasyWindowWin32::SetSize(const Vector2DInt& size, bool client) {
	RECT oRect = { 0, 0, size.x(), size.y() };
	if (client && styles_ & kStyleBorderless) {
		DWORD iWindowStyle = GetWindowLong(hwnd_, GWL_STYLE);
		AdjustWindowRect(&oRect, iWindowStyle, FALSE);
	}

	SetWindowPos(hwnd_, NULL, 0, 0, oRect.right - oRect.left, oRect.bottom - oRect.top, SWP_NOMOVE);
}

void EasyWindowWin32::SetPosition(const Vector2DInt& pos, bool client) {
	RECT oRect = { pos.x(), pos.y(), 0, 0 };
	if (client) {
		POINT oPoint = { 0, 0 };
		ClientToScreen(hwnd_, &oPoint);

		RECT oWinRect;
		GetWindowRect(hwnd_, &oWinRect);

		oRect.left += oPoint.x - oWinRect.left;
		oRect.top += oPoint.y - oWinRect.top;
	}
	SetWindowPos(hwnd_, NULL, oRect.left, oRect.top, 0, 0, SWP_NOSIZE);
}

void EasyWindowWin32::SetMaximized(bool b) {
	if (b)
		ShowWindow(hwnd_, SW_MAXIMIZE);
	else
		ShowWindow(hwnd_, SW_RESTORE);
}

void EasyWindowWin32::SetMinimized(bool b) {
	if (b)
		ShowWindow(hwnd_, SW_MINIMIZE);
	else if (IsIconic(hwnd_))
		ShowWindow(hwnd_, SW_RESTORE);
}

void EasyWindowWin32::SetTitle(const String& title) {
	auto w = title.ToStdWString();
	SetWindowTextW(hwnd_, w.c_str());
}

void EasyWindowWin32::SetAlpha(uint8_t alpha) {
	if (alpha < 255) {
		SetWindowLong(hwnd_, GWL_EXSTYLE, GetWindowLong(hwnd_, GWL_EXSTYLE) | WS_EX_LAYERED);
	}
	else {
		SetWindowLong(hwnd_, GWL_EXSTYLE, GetWindowLong(hwnd_, GWL_EXSTYLE) & ~WS_EX_LAYERED);
	}
	SetLayeredWindowAttributes(hwnd_, RGB(0, 0, 0), alpha, LWA_ALPHA);
}

void EasyWindowWin32::SetCursor(CursorType cursor) {
	cursor_ = cursor;
}

Vector2DInt EasyWindowWin32::Size() const {
	RECT r;
	GetWindowRect(hwnd_, &r);
	return { r.right - r.left, r.bottom - r.top };
}

Vector2DInt EasyWindowWin32::Position() const {
	RECT r;
	GetWindowRect(hwnd_, &r);
	return { r.left, r.top };
}

bool EasyWindowWin32::IsMaximized() const {
	return IsZoomed(hwnd_) == TRUE;
}

bool EasyWindowWin32::IsMinimized() const {
	return IsIconic(hwnd_) == TRUE;
}

void* EasyWindowWin32::PlatformHandle() const {
	return hwnd_;
}

bool EasyWindowWin32::Update() {
	// Poll and handle messages (inputs, window resize, etc.)
	// See the WndProc() function below for our to dispatch events to the Win32 backend.
	MSG msg;
	while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
		if (msg.message == WM_QUIT) {
			return false;
		}
	}
	return true;
}

#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0 // From Windows SDK 8.1+ headers
#endif

LRESULT EasyWindowWin32::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	auto self = reinterpret_cast<EasyWindowWin32*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (!self) {
		return DefWindowProcW(hwnd, msg, wparam, lparam);
	}

	if (self->on_wnd_proc_ && self->on_wnd_proc_(hwnd, msg, wparam, lparam)) {
		return 1;
	}

	switch (msg) {
	case WM_SIZE: {
		if (wparam == SIZE_MINIMIZED)
			return 0;
		auto size = Vector2DInt(LOWORD(lparam), HIWORD(lparam));
		self->resize_ = size;
		if (self->on_resized_) {
			self->on_resized_(std::move(size));
		}
		break;
	}
	case WM_MOVE: {
		auto pos = Vector2DInt(LOWORD(lparam), HIWORD(lparam));
		if (self->on_moved_)
			self->on_moved_(std::move(pos));
		break;
	}
	case WM_SETFOCUS:
		if (self->on_forced_)
			self->on_forced_(true);
		break;
	case WM_KILLFOCUS:
		if (self->on_forced_)
			self->on_forced_(false);
		break;
	case WM_CLOSE:
		if (self->on_close_ && !self->on_close_()) {
			return 0;
		}
		break;
	case WM_SYSCOMMAND:
		if ((wparam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	case WM_DPICHANGED: {
		auto dpi = HIWORD(wparam);
		auto r = reinterpret_cast<RECT*>(lparam);
		if (self->on_dpi_changed_)
			self->on_dpi_changed_({ r->left, r->top, r->right - r->left, r->bottom - r->top }, dpi);
		break;
	}
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void EasyWindowWin32::Repaint() {
	::UpdateWindow(hwnd_);
}

Vector2DInt EasyWindowWin32::ClientSize() const {
	RECT rect;
	GetClientRect(hwnd_, &rect);
	return { rect.right - rect.left, rect.bottom - rect.top };
}

Vector2DInt EasyWindowWin32::ClientPosition() const {
	RECT rect;
	GetClientRect(hwnd_, &rect);
	ClientToScreen(hwnd_, reinterpret_cast<POINT*>(&rect.left)); // convert top-left
	return { rect.left, rect.top };
}
}
