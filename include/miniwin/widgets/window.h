#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class Window : public Widget
{
public:
	Window(std::u8string_view title, bool show = true);
	~Window() override;

    std::u8string_view title() const;
    void set_title(std::u8string_view title) const;

	void EnableTop(bool b) const;
	void EnableCloseButton(bool b) const;

	bool has_close_button() const;
	bool is_docking() const;

protected:
	void PaintBegin() override;
	void PaintEnd() override;

private:
    using Widget::widget_parent;
    using Widget::set_widget_parent;

    class Impl;
	std::unique_ptr<Impl> impl_;
};
}
