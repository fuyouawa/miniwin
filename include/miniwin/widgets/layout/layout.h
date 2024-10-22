#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class Layout : public Widget
{
public:
	Layout(Widget* parent);

	void AddWidget(Widget* widget);
	void RemoveWidget(Widget* widget);

	bool SetWidgetIndex(const Widget* widget, size_t index);
	std::optional<size_t> IndexOfWidget(const Widget* widget) const;
	std::optional<size_t> AdvanceWidget(const Widget* widget, size_t count);

	size_t Count() const;
	bool IsEmpty() const;

private:
	using Widget::SetWidgetChildIndex;
	using Widget::IndexOfWidgetChild;
};
}