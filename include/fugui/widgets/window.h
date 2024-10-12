#pragma once
#include <fugui/core/widget.h>

namespace fugui {
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
	void PaintBegin() const override;
	void PaintEnd() const override;

private:
    class Impl;
	std::unique_ptr<Impl> impl_;
};
}
