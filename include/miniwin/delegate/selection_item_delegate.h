#pragma once
#include <miniwin/delegate/base/abstract_item_delegate.h>

namespace miniwin {
class SelectionItemDelegate : public AbstractItemDelegate
{
public:
	SelectionItemDelegate(Object* parent);

	void Paint(AbstractItemView* view, const ModelIndex& index) override;
};
}
