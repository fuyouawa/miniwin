#pragma once
#include <miniwin/delegate/selectable_item_delegate.h>

namespace miniwin {
class SelectableItemDelegate::Impl {
public:
	Impl(SelectableItemDelegate* owner);

	SelectableItemDelegate* owner_;

	bool alloc_multi_select = true;
};
}