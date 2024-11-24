#include "main_window_impl.h"

#include "application_impl.h"
#include <miniwin/tools/mathf.h>
#include <imgui/imgui.h>

namespace miniwin {
MainWindowImpl::MainWindowImpl(const String& title, const Vector2DInt& size, bool adjust_size, FlagsType styles,
	const SharedMainWindow& parent)
{
	auto p = dynamic_cast<MainWindowImpl*>(parent.get());
	platform_win_ = PlatformEasyWindow::Create(title, size, adjust_size, styles, p ? p->platform_win_ : nullptr);
}

MainWindowImpl::~MainWindowImpl() {
	ImGui::DestroyContext();
}

void MainWindowImpl::Initialize() {
	auto p = dynamic_cast<ApplicationImpl*>(&Application::Instance());
	p->RegisterMainWindow(shared_from_this());
}

void MainWindowImpl::Repaint() {
	platform_win_->Repaint();
}

void MainWindowImpl::Show(bool show_or_hide) {
	platform_win_->Show(show_or_hide);
}

bool MainWindowImpl::IsFocused() const {
	return platform_win_->IsFocused();
}

void MainWindowImpl::SetFocus() {
	platform_win_->SetFocus();
}

void MainWindowImpl::SetSize(const Vector2DInt& size, bool adjust) {
	platform_win_->SetSize(size, adjust);
}

void MainWindowImpl::SetPosition(const Vector2DInt& pos, bool adjust) {
	platform_win_->SetPosition(pos, adjust);
}

void MainWindowImpl::SetMaximized(bool b) {
	platform_win_->SetMaximized(b);
}

void MainWindowImpl::SetMinimized(bool b) {
	platform_win_->SetMinimized(b);
}

void MainWindowImpl::SetTitle(const String& title) {
	platform_win_->SetTitle(title);
}

void MainWindowImpl::SetAlpha(uint8_t alpha) {
	platform_win_->SetAlpha(alpha);
}

void MainWindowImpl::SetCursor(CursorType cursor) {
	platform_win_->SetCursor(static_cast<EasyWindow::CursorType>(cursor));
}

Vector2DInt MainWindowImpl::Size() const {
	return platform_win_->Size();
}

Vector2DInt MainWindowImpl::Position() const {
	return platform_win_->Position();
}

bool MainWindowImpl::IsMaximized() const {
	return platform_win_->IsMaximized();
}

bool MainWindowImpl::IsMinimized() const {
	return platform_win_->IsMinimized();
}

uint64_t MainWindowImpl::FrameCount() const {
	return frame_count_;
}

float MainWindowImpl::DeltaTime() const {
	return static_cast<float>(delta_time_) / 1000.f;
}

bool MainWindowImpl::Orphaned() const {
	return orphaned_;
}

void* MainWindowImpl::PlatformHandle() const {
	return platform_win_->PlatformHandle();
}

bool MainWindowImpl::Update() {
	auto start_time = std::chrono::steady_clock::now();

	bool exit = !platform_win_->Update();	// 逻辑的更新（比如消息处理事件发派之类的）
	if (!exit) {
		PlatformPreRender();
		auto suc = platform_win_->PreRender();			// 预渲染
		if (suc) {										// 这里suc并不一定是失败了，只是表示当前帧是否要继续绘制
			PlatformStartFrame();

			ImGui::NewFrame();
			driver_.Update();
			ImGui::Render();

			platform_win_->Render();					// 渲染
			PlatformAdditionRender();

			ImGuiIO& io = ImGui::GetIO();
			// Update and Render additional Platform Windows
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
			}

			platform_win_->Present();					// 提交渲染结果到屏幕
		}
	}

	auto end_time_ = std::chrono::steady_clock::now();
	delta_time_ = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_ - start_time).count();

	++frame_count_;
	orphaned_ = exit;
	return !exit;
}

bool MainWindowImpl::AdjustDpiScale(float scale) {
	cur_dpi_scale_ = scale > 1.0f ? scale : 1.0f;

	if (!Mathf::Approximately(cur_dpi_scale_, prev_dpi_scale_)) {
		prev_dpi_scale_ = cur_dpi_scale_;

		auto& io = ImGui::GetIO();
		io.Fonts->Clear();
		ImFont* font = io.Fonts->AddFontFromFileTTF(
			"C:\\Windows\\Fonts\\msyh.ttc",
			16.0f * cur_dpi_scale_,
			nullptr,
			io.Fonts->GetGlyphRangesChineseFull());
		IM_ASSERT(font != NULL);
		if (font == NULL)
			return false;
	}
	return true;
}

void MainWindowImpl::RegisterSubWindow(const SharedWindow& win) {
	driver_.RegisterWindow(win);
}

const List<SharedWindow>& MainWindowImpl::SubWindows() {
	return driver_.Windows();
}

std::thread::id MainWindowImpl::ThreadId() {
	return driver_.UiThreadId();
}
}
