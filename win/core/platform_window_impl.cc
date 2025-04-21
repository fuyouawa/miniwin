#include "platform_window_impl.h"

#include "application_impl.h"
#include <miniwin/tools/mathf.h>
#include <imgui/imgui.h>

namespace miniwin {
PlatformWindowImpl::PlatformWindowImpl(const String& title, const Vector2DInt& size, bool adjust_size, FlagsType styles,
	const SharedPlatformWindow& parent)
{
	auto p = dynamic_cast<PlatformWindowImpl*>(parent.get());
	platform_win_ = PlatformEasyWindow::Create(title, size, adjust_size, styles, p ? p->platform_win_ : nullptr);
}

PlatformWindowImpl::~PlatformWindowImpl() {
	ImGui::DestroyContext();
}

void PlatformWindowImpl::Initialize() {
	auto p = dynamic_cast<ApplicationImpl*>(&Application::Instance());
	p->RegisterMainWindow(shared_from_this());
}

void PlatformWindowImpl::Repaint() {
	platform_win_->Repaint();
}

void PlatformWindowImpl::Show(bool show_or_hide) {
	platform_win_->Show(show_or_hide);
}

bool PlatformWindowImpl::IsFocused() const {
	return platform_win_->IsFocused();
}

void PlatformWindowImpl::SetFocus() {
	platform_win_->SetFocus();
}

void PlatformWindowImpl::SetSize(const Vector2DInt& size, bool adjust) {
	platform_win_->SetSize(size, adjust);
}

void PlatformWindowImpl::SetPosition(const Vector2DInt& pos, bool adjust) {
	platform_win_->SetPosition(pos, adjust);
}

void PlatformWindowImpl::SetMaximized(bool b) {
	platform_win_->SetMaximized(b);
}

void PlatformWindowImpl::SetMinimized(bool b) {
	platform_win_->SetMinimized(b);
}

void PlatformWindowImpl::SetTitle(const String& title) {
	platform_win_->SetTitle(title);
}

void PlatformWindowImpl::SetAlpha(uint8_t alpha) {
	platform_win_->SetAlpha(alpha);
}

void PlatformWindowImpl::SetCursor(CursorType cursor) {
	platform_win_->SetCursor(static_cast<EasyWindow::CursorType>(cursor));
}

Vector2DInt PlatformWindowImpl::Size() const {
	return platform_win_->Size();
}

Vector2DInt PlatformWindowImpl::Position() const {
	return platform_win_->Position();
}

bool PlatformWindowImpl::IsMaximized() const {
	return platform_win_->IsMaximized();
}

bool PlatformWindowImpl::IsMinimized() const {
	return platform_win_->IsMinimized();
}

uint64_t PlatformWindowImpl::FrameCount() const {
	return frame_count_;
}

bool PlatformWindowImpl::IsDone() const {
	return orphaned_ || driver_.IsDone();
}

void* PlatformWindowImpl::PlatformHandle() const {
	return platform_win_->PlatformHandle();
}

bool PlatformWindowImpl::Update() {
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

	++frame_count_;
	orphaned_ = exit;
	updated_ = true;
	return !exit;
}

bool PlatformWindowImpl::AdjustDpiScale(float scale) {
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

void PlatformWindowImpl::RegisterSubWindow(const SharedWindow& win) {
	driver_.RegisterWindow(win);
}

const List<SharedWindow>& PlatformWindowImpl::SubWindows() {
	return driver_.Windows();
}

Vector2DInt PlatformWindowImpl::ClientSize() const {
	return platform_win_->ClientSize();
}

Vector2DInt PlatformWindowImpl::ClientPosition() const {
	return platform_win_->ClientPosition();
}

bool PlatformWindowImpl::IsUpdated() {
	return updated_;
}
}
