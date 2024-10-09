#pragma once
#include <fugui/widgets/widget/base/abstract_window.h>

namespace fugui {
namespace internal {
class WindowPrivate;
}

class Window : public AbstractWindow
{
public:
	Window(AbstractWindow* parent, std::u8string_view title, bool show = true);
	~Window() override;

	void EnableTop(bool b);
	void EnableCloseButton(bool b);

	bool has_close_button() const;
	bool is_docking() const;

	Signal<> on_close_btn_clicked_;

protected:
	void OnPaintBegin() override;
	void OnPaintEnd() override;

	virtual void OnDockingChanged();

private:
	internal::WindowPrivate* p_;
};
}