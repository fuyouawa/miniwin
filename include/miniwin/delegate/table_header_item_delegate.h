#pragma once
#include <miniwin/delegate/base/abstract_item_delegate.h>

namespace miniwin {
class TableHeaderItemDelegate : public AbstractItemDelegate {
	MW_OBJECT
public:
	TableHeaderItemDelegate();
	~TableHeaderItemDelegate() override;

	HeaderOrientation Orientation() const;
	void SetOrientation(HeaderOrientation orientation);

protected:
	void PaintBegin(const SharedItemView& view, const ModelIndex& index) override;

	_MW_IMPL
};
}
