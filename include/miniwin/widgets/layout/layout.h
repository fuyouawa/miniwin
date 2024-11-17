#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class Layout : public Object {
	MW_OBJECT
public:
	Layout();
	~Layout() override;

	bool AddWidget(const SharedWidget& widget);
	bool RemoveWidget(const SharedWidget& widget);
	void ClearWidget();

	List<WeakWidget> Widgets() const;
	size_t IndexOfWidget(const SharedWidget& widget) const;
	bool SetWidgetIndex(const SharedWidget& widget, size_t index);
	size_t AdvanceWidget(const SharedWidget& widget, size_t count);

	size_t Count() const;
	bool IsEmpty() const;

	void Initialize(const SharedObject& parent) override;

protected:
	friend class WidgetsDriver;

	virtual void OnLayoutWidgetBegin(const SharedWidget& widget);
	virtual void OnLayoutWidgetEnd(const SharedWidget& widget);

	_MW_IMPL
};
}
