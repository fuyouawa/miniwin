#pragma once
#include <mvcgui/core/widget.h>

namespace mvcgui {
class AbstractWindow : public Widget
{
public:
	AbstractWindow(AbstractWindow* const parent, std::u8string_view title, bool show);

	auto& title() const { return title_; }
	virtual void set_title(std::u8string_view title) { title_ = title; }

protected:
	std::u8string title_;
};
}