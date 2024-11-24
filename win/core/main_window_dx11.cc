#include "main_window_dx11.h"
#include "win/tools/platform_easy_window_dx11.h"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_win32.h>
#include <imgui/backends/imgui_impl_dx11.h>

#include "win/tools/debug.h"
#include "win/tools/easy_window_win32.h"

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace miniwin {
SharedMainWindow MainWindow::Create(const String& title, const Vector2DInt& size, bool adjust_size, FlagsType styles,
                                const SharedMainWindow& parent) {
	static bool is_initialized = false;
	if (!is_initialized) {
		ImGui_ImplWin32_EnableDpiAwareness();
		is_initialized = true;
	}

	auto inst = std::make_shared<MainWindowDx11>(title, size, adjust_size, styles, parent);
	inst->Initialize();
	return inst;
}

MainWindowDx11::MainWindowDx11(const String& title, const Vector2DInt& size, bool adjust_size, FlagsType styles,
                           const SharedMainWindow& parent)
	: MainWindowImpl(title, size, adjust_size, styles, parent) {
	platform_win_dx11_ = dynamic_cast<PlatformEasyWindowDx11*>(platform_win_.get());

	platform_win_dx11_->on_dpi_changed_ = [this](RectInt rect, uint16_t dpi) {
		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports) {
			::SetWindowPos(
				reinterpret_cast<::HWND>(PlatformHandle()),
				nullptr,
				rect.x(), rect.y(), rect.width(), rect.height(),
				SWP_NOZORDER | SWP_NOACTIVATE);
		}
		return false;
	};

	platform_win_dx11_->on_wnd_proc_ = [this](HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
		return ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);
	};
}

MainWindowDx11::~MainWindowDx11() {
	// Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
}

void MainWindowDx11::Initialize() {
	MainWindowImpl::Initialize();

	// Setup Dear ImGui context
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	auto suc = ImGui_ImplWin32_Init(PlatformHandle());
	MW_ASSERT_X(suc);
	suc = ImGui_ImplDX11_Init(platform_win_dx11_->g_pd3dDevice, platform_win_dx11_->g_pd3dDeviceContext);
	MW_ASSERT_X(suc);

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != nullptr);
}

void MainWindowDx11::PlatformStartFrame() {
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
}

void MainWindowDx11::PlatformAdditionRender() {
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void MainWindowDx11::PlatformPreRender() {
	AdjustDpiScale(ImGui_ImplWin32_GetDpiScaleForHwnd(PlatformHandle()));
}
}
