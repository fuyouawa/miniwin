#pragma once
#include <miniwin/widgets/base/abstract_item_view.h>
#include <miniwin/widgets/view/header_view.h>


namespace miniwin {
class TableView : public AbstractItemView {
	MW_OBJECT
public:
	TableView();
	~TableView() override;

	SharedHeaderView HorizontalHeader() const;
	void SetHorizontalHeader(const SharedHeaderView& header);

	SharedHeaderView VerticalHeader() const;
	void SetVerticalHeader(const SharedHeaderView& header);

	void SetModel(const SharedItemModel& model) override;

protected:
	void Awake() override;
	void PaintBegin() override;

	_MW_IMPL
};
}
