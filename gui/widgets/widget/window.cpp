#include <fugui/widgets/widget/window.h>
#include <imgui/imgui.h>

#include <gui/tools/algorithm.h>
#include <gui/core/drawer.h>
#include <gui/internal/graphic_utils.h>
#include <gui/tools/scope_variable.h>

namespace fugui {
namespace internal {
class WindowPrivate
{
public:
	ScopeCondition top_sc_;
	void* hwnd_;
	void* prev_hwnd_;
	bool is_docking_;
	bool has_close_button_;

	WindowPrivate(): hwnd_(nullptr), prev_hwnd_(nullptr), is_docking_(false), has_close_button_(false)
	{
	}
};
}

Window::Window(AbstractWindow* parent, std::u8string_view title, bool show)
	: AbstractWindow{ parent, title, show }
{
	p_ = new internal::WindowPrivate();

	Connect(on_close_btn_clicked_, [this]() {
		Close();
		});
}

Window::~Window()
{
	delete p_;
}

void Window::EnableTop(bool b) {
	p_->top_sc_.set_control(b);
}

void Window::EnableCloseButton(bool b) {
	p_->has_close_button_ = b;
}

bool Window::has_close_button() const {
	return p_->has_close_button_;
}

bool Window::is_docking() const {
	return p_->is_docking_;
}

void Window::OnPaintBegin()
{
	Widget::OnPaintBegin();
	p_->top_sc_.Entry();

	if (is_showing()) {
		bool open = true;
		Drawer::BeginWindow(title_, p_->has_close_button_ ? &open : nullptr, flags());
		p_->is_docking_ = ImGui::IsWindowDocked();
		// 获取当前窗体句柄, 然后判断是否改变
		// 如果改变则说明当前窗体脱离或者停靠到了某个窗体
		p_->hwnd_ = internal::GraphicUtils::GetCurrentWindow();
		if (p_->hwnd_ && p_->hwnd_ != p_->prev_hwnd_) {
			OnDockingChanged();
			p_->prev_hwnd_ = p_->hwnd_;
		}
		if (p_->top_sc_.is_changed() && p_->hwnd_) {
			internal::GraphicUtils::EnableWindowTop(p_->hwnd_, *p_->top_sc_);
		}
		if (!open) {
			Emit(on_close_btn_clicked_);
		}
	}
}

void Window::OnDockingChanged() {
	// 如果当前窗体非停靠窗, 说明是从默认窗体上剥离出来, 或者从停靠状态取消的窗体, 需要重设置顶状态
	// 如果当前窗体是停靠窗, 则不改变置顶状态
	if (!p_->is_docking_) {
		internal::GraphicUtils::EnableWindowTop(p_->hwnd_, *p_->top_sc_);
	}
}

void Window::OnPaintEnd()
{
	if (is_showing()) {
		Drawer::EndWindow();
	}

	p_->top_sc_.Exit();
	Widget::OnPaintEnd();
}
}
