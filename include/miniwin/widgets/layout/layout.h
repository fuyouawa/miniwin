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

	bool IsLayout() const override;

	SharedWidget WidgetByIndex(size_t index) const;
	List<SharedWidget> Widgets() const;
	size_t IndexOfWidget(const SharedWidget& widget) const;
	bool SetWidgetIndex(const SharedWidget& widget, size_t index);
	size_t AdvanceWidget(const SharedWidget& widget, size_t count);

	size_t Count() const;
	bool IsEmpty() const;

	void Initialize(const SharedObject& parent) override;

protected:
	friend class WidgetsDriver;

	virtual void OnPrepareLayout();
	virtual void OnBeginLayoutWidget(const SharedWidget& widget, size_t index);
	virtual void OnEndLayoutWidget(const SharedWidget& widget, size_t index);
	virtual void OnFinishedLayout();

	_MW_IMPL
};
}
