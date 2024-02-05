#pragma once
#include <mvcgui/widgets/widget/base/abstract_window.h>
#include <mvcgui/core/flags.h>


namespace mvcgui {
class Window : public AbstractWindow
{
public:
	Window(AbstractWindow* parent, std::u8string_view title, bool show = true);

	void EnableTop(bool b);
	void EnableCloseButton(bool b);

	bool has_close_button() const { return has_close_button_; }
	bool is_docking() const { return is_docking_; }

	Signal<> on_close_btn_clicked_;

protected:
	void OnPaintBegin() override;
	void OnPaintEnd() override;

	virtual void OnDockingChanged();

	ScopeCondition top_sc_;
	void* hwnd_;
	void* prev_hwnd_;
	bool is_docking_;

private:
	bool has_close_button_;
};
}