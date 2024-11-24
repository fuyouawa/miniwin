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

	Vector2D Position() const override;
	void SetPosition(const Vector2D& pos) override;
	Vector2D Size() const override;
	void SetSize(const Vector2D& size) override;

protected:
	void Awake() override;
	void PaintBegin(size_t index) override;

protected:
	_MW_IMPL
};
}
