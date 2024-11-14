#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class Layout : public Object
{
public:
	Layout(Object* parent);
	~Layout() override;

	bool AddWidget(Widget* widget);
	bool RemoveWidget(Widget* widget);
	void ClearWidget();

	List<Widget*> Widgets() const;
	size_t IndexOfWidget(Widget* widget) const;
	bool SetWidgetIndex(Widget* widget, size_t index);
	size_t AdvanceWidget(Widget* widget, size_t count);

	size_t Count() const;
	bool IsEmpty() const;

protected:
	friend class WidgetsDriver;

	virtual void OnLayoutWidgetBegin(Widget* widget);
	virtual void OnLayoutWidgetEnd(Widget* widget);

	_MW_IMPL
};
}