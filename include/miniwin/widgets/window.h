#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class Window : public Widget
{
public:
	Window(std::u8string_view title);
	~Window() override;

    std::u8string_view title() const;
    void set_title(std::u8string_view title) const;

    WindowFlags flags() const;
    void set_flags(WindowFlags flags);

	void EnableTop(bool b) const;
	void EnableCloseButton(bool b) const;

	bool has_close_button() const;
	bool is_docking() const;

protected:
	void PaintBegin() override;
	void PaintEnd() override;

private:
    using Widget::WidgetParent;
    using Widget::SetWidgetParent;

    _MW_IMPL
};
}
