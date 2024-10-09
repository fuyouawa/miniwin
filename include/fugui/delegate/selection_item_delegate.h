#pragma once
#include <fugui/delegate/base/abstract_item_delegate.h>

namespace fugui {
class SelectionItemDelegate : public AbstractItemDelegate
{
public:
	SelectionItemDelegate();

	void Paint(AbstractItemModelPtr model, const ModelIndex& index) override;
};
}