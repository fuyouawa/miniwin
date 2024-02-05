#pragma once
#include <mvcgui/widgets/delegate/base/abstract_item_delegate.h>

namespace mvcgui {
class SelectionItemDelegate : public AbstractItemDelegate
{
public:
	SelectionItemDelegate();

	void Paint(const AbstractItemView& view, const ModelIndex& index) override;
};
}