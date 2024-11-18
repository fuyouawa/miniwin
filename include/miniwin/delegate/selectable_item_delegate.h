#pragma once
#include <miniwin/delegate/base/abstract_item_delegate.h>

namespace miniwin {
class SelectableItemDelegate : public AbstractItemDelegate {
	MW_OBJECT
public:
	SelectableItemDelegate();
	~SelectableItemDelegate() override;

	bool IsAllocMultiSelect() const;
	void SetAllocMultiSelect(bool b);

protected:
	void PaintBegin(const SharedItemView& view, const ModelIndex& index) override;

	_MW_IMPL
};
}
