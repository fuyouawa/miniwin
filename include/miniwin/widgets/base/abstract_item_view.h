#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class AbstractItemDelegate;

class AbstractItemView : public AbstractControl {
	MW_OBJECT
public:
	AbstractItemView();
	~AbstractItemView() override;

	virtual void SetModel(const SharedItemModel& model);
	const SharedItemModel& Model() const;

	virtual void SetSelectionModel(const SharedItemSelectionModel& selection_model);
	const SharedItemSelectionModel& SelectionModel() const;

	virtual void SetItemDelegate(const SharedItemDelegate& item_delegate);
	const SharedItemDelegate& ItemDelegate() const;

	_MW_IMPL
};
}
