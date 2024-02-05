#pragma once
#include <mvcgui/core/widget.h>

namespace mvcgui {
class AbstractControl : public Widget
{
public:
	AbstractControl(Widget* const parent, std::u8string_view label, bool show);
	
	auto& label() const { return label_; }
	virtual void set_label(std::u8string_view label) { label_ = label; }

protected:
	void OnPaintBegin() override;
	virtual void OnItemShowablePaintBegin() {}
	virtual void OnItemShowablePaintEnd() {}
	void OnPaintEnd() override;

	std::u8string label_;

private:
	bool is_showable_item_;
};


class AbstractMinimumControl : public AbstractControl
{
public:
	AbstractMinimumControl(Widget* const parent, std::u8string_view label, bool show);
};
}