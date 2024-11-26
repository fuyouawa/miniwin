#pragma once
#include <miniwin/widgets/base/abstract_item_view.h>


namespace miniwin {
class TableView : public AbstractItemView {
	MW_OBJECT
public:
	TableView();
	~TableView() override;

	void SetHeaderVisible(HeaderOrientation orientation, bool b);
	bool IsHeaderVisible(HeaderOrientation orientation) const;

	virtual void SetHeaderItemDelegate(HeaderOrientation orientation, const SharedItemDelegate& item_delegate);
	const SharedItemDelegate& HeaderItemDelegate(HeaderOrientation orientation) const;

	Vector2D Size() const override;
	void SetSize(const Vector2D& size) override;

protected:
	void Awake() override;
	void BeginUpdate(size_t index) override;

protected:
	_MW_IMPL
};
}
