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

	void Initialize(const SharedObject& parent) override;

	_MW_IMPL
};
}
