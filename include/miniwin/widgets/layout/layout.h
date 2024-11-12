#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class Layout : public Widget
{
public:
	Layout(Widget* parent);

	void AddWidget(Widget* widget);
	void RemoveWidget(Widget* widget);
	void ClearWidget();

	size_t Count() const;
	bool IsEmpty() const;

protected:
	void PaintBegin() override;
	void PaintEnd() override;
};
}