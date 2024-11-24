#pragma once
#include "platform_easy_window_impl.h"

#include <Windows.h>
#include <d3d11.h>

#include "miniwin/tools/vector4d.h"

namespace miniwin {
class EasyWindowWin32;

class PlatformEasyWindowDx11 : public PlatformEasyWindowImpl {
public:
	PlatformEasyWindowDx11(const String& title, const Vector2DInt& size, bool client_size,
		FlagsType styles, const SharedPlatformEasyWindow& parent);
	~PlatformEasyWindowDx11() override;

	bool Init();

	// Helper functions
	bool CreateDeviceD3D();

	void CleanupDeviceD3D();

	void CreateRenderTarget();

	void CleanupRenderTarget();
	bool PreRender() override;
	void Render() override;
	void Present() override;
	void OnResized(Vector2DInt size) override;

	std::function<void(RectInt rect, uint16_t dpi)> on_dpi_changed_;
	std::function<bool(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)> on_wnd_proc_;

	ID3D11Device* g_pd3dDevice = nullptr;
	ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
	IDXGISwapChain* g_pSwapChain = nullptr;
	bool g_SwapChainOccluded = false;
	UINT g_ResizeWidth = 0, g_ResizeHeight = 0;
	ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
	Vector4D clear_color = { 0.45f, 0.55f, 0.60f, 1.00f };
};
}
