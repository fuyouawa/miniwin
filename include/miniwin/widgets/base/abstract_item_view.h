#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class AbstractItemDelegate;

class AbstractItemView : public Widget {
	MW_OBJECT
public:
	AbstractItemView();
	~AbstractItemView() override;

	virtual void SetModel(const SharedItemModel& model);
	const SharedItemModel& Model() const;

	virtual void SetSelectionModel(const SharedItemSelectionModel& selection_model);
	SharedItemSelectionModel SelectionModel() const;

	virtual void SetItemDelegate(const SharedItemDelegate& item_delegate);
	const SharedItemDelegate& ItemDelegate() const;

	Vector2D CalcSize() const override;
	Vector2D CalcPosition() const override;

protected:
	void PaintBegin(size_t index) override;
	void PaintEnd(size_t index) override;

	_MW_IMPL
};
}
