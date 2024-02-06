#include <mvcgui/widgets/widget/window.h>
#include <mvcgui/internal/wrapper/graphic_utils.h>
#include <mvcgui/tools/algorithm.h>
#include <mvcgui/core/drawer.h>
#include <imgui/imgui.h>

namespace mvcgui {
Window::Window(AbstractWindow* parent, std::u8string_view title, bool show)
	: AbstractWindow{ parent, title, show },
	top_sc_{ false },
	has_close_button_{ true },
	hwnd_{ nullptr },
	prev_hwnd_{ nullptr }
{
	Connect(on_close_btn_clicked_, [this]() {
		Close();
		});
}

void Window::EnableTop(bool b) {
	top_sc_.set_control(b);
}

void Window::EnableCloseButton(bool b) {
	has_close_button_ = b;
}

void Window::OnPaintBegin()
{
	Widget::OnPaintBegin();
	top_sc_.Entry();

	if (is_showing()) {
		bool open = true;
		Drawer::BeginWindow(title_, has_close_button_ ? &open : nullptr, flags_, size_);
		is_docking_ = ImGui::IsWindowDocked();
		// 获取当前窗体句柄, 然后判断是否改变
		// 如果改变则说明当前窗体脱离或者停靠到了某个窗体
		hwnd_ = internal::GraphicUtils::GetCurrentWindow();
		if (hwnd_ && hwnd_ != prev_hwnd_) {
			OnDockingChanged();
			prev_hwnd_ = hwnd_;
		}
		if (top_sc_.is_changed() && hwnd_) {
			internal::GraphicUtils::EnableWindowTop(hwnd_, *top_sc_);
		}
		if (!open) {
			Emit(on_close_btn_clicked_);
		}
	}
}

void Window::OnDockingChanged() {
	// 如果当前窗体非停靠窗, 说明是从默认窗体上剥离出来, 或者从停靠状态取消的窗体, 需要重设置顶状态
	// 如果当前窗体是停靠窗, 则不改变置顶状态
	if (!is_docking_) {
		internal::GraphicUtils::EnableWindowTop(hwnd_, *top_sc_);
	}
}

void Window::OnPaintEnd()
{
	if (is_showing()) {
		Drawer::EndWindow();
	}

	top_sc_.Exit();
	Widget::OnPaintEnd();
}
}