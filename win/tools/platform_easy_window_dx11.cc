#include "platform_easy_window_dx11.h"

#include <thread>

#include "easy_window_win32.h"

namespace miniwin {
SharedPlatformEasyWindow PlatformEasyWindow::Create(const String& title, const Vector2DInt& size, bool client_size,
                                                    FlagsType styles, const SharedPlatformEasyWindow& parent) {
	auto win_dx11 = std::make_shared<PlatformEasyWindowDx11>(title, size, client_size, styles, parent);
	if (!win_dx11->Init())
		return nullptr;
	return win_dx11;
}

PlatformEasyWindowDx11::PlatformEasyWindowDx11(const String& title, const Vector2DInt& size, bool client_size,
                                               FlagsType styles, const SharedPlatformEasyWindow& parent)
	: PlatformEasyWindowImpl(title, size, client_size, styles, parent) {

	auto win32 = dynamic_cast<EasyWindowWin32*>(win_.get());

	win32->on_dpi_changed_ = [this](RectInt rect, uint16_t dpi) {
		on_dpi_changed_(std::move(rect), dpi);
	};
	win32->on_wnd_proc_ = [this](HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
		if (on_wnd_proc_)
			return on_wnd_proc_(hwnd, msg, wparam, lparam);
		return false;
	};
}

PlatformEasyWindowDx11::~PlatformEasyWindowDx11() {
	CleanupDeviceD3D();
}

bool PlatformEasyWindowDx11::Init() {
	// Initialize Direct3D
	if (!CreateDeviceD3D()) {
		CleanupDeviceD3D();
		return false;
	}

	win_->Show();
	win_->Repaint();
	return true;
}

bool PlatformEasyWindowDx11::CreateDeviceD3D() {
	// Setup swap chain
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = reinterpret_cast<HWND>(win_->PlatformHandle());
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT createDeviceFlags = 0;
	//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = {D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0,};
	HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags,
	                                            featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain,
	                                            &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
	if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
		res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags,
		                                    featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain,
		                                    &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
	if (res != S_OK)
		return false;

	CreateRenderTarget();
	return true;
}

void PlatformEasyWindowDx11::CleanupDeviceD3D() {
	CleanupRenderTarget();
	if (g_pSwapChain) {
		g_pSwapChain->Release();
		g_pSwapChain = nullptr;
	}
	if (g_pd3dDeviceContext) {
		g_pd3dDeviceContext->Release();
		g_pd3dDeviceContext = nullptr;
	}
	if (g_pd3dDevice) {
		g_pd3dDevice->Release();
		g_pd3dDevice = nullptr;
	}
}

void PlatformEasyWindowDx11::CreateRenderTarget() {
	ID3D11Texture2D* pBackBuffer;
	g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
	pBackBuffer->Release();
}

void PlatformEasyWindowDx11::CleanupRenderTarget() {
	if (g_mainRenderTargetView) {
		g_mainRenderTargetView->Release();
		g_mainRenderTargetView = nullptr;
	}
}

bool PlatformEasyWindowDx11::PreRender() {
	// Handle window being minimized or screen locked
	if (g_SwapChainOccluded && g_pSwapChain->Present(0, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED) {
		return false;
	}
	g_SwapChainOccluded = false;

	// Handle window resize (we don't resize directly in the WM_SIZE handler)
	if (g_ResizeWidth != 0 && g_ResizeHeight != 0) {
		CleanupRenderTarget();
		g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
		g_ResizeWidth = g_ResizeHeight = 0;
		CreateRenderTarget();
	}
	return true;
}

void PlatformEasyWindowDx11::Render() {
	const float clear_color_with_alpha[4] = {
		clear_color.x() * clear_color.w(),
		clear_color.y() * clear_color.w(),
		clear_color.z() * clear_color.w(),
		clear_color.w()
	};
	g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
	g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
}

void PlatformEasyWindowDx11::Present() {
	// Present
	HRESULT hr = g_pSwapChain->Present(1, 0); // Present with vsync
	//HRESULT hr = g_pSwapChain->Present(0, 0); // Present without vsync
	g_SwapChainOccluded = (hr == DXGI_STATUS_OCCLUDED);
}

void PlatformEasyWindowDx11::OnResized(Vector2DInt size) {
	g_ResizeWidth = size.x();
	g_ResizeHeight = size.y();
}
}
