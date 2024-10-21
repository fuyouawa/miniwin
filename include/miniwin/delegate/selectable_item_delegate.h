#pragma once
#include <miniwin/delegate/base/abstract_item_delegate.h>

#include "miniwin/core/flags.h"

namespace miniwin {
class SelectableItemDelegate : public AbstractItemDelegate
{
public:
	SelectableItemDelegate(Object* parent);

	bool IsAllocMultiSelect() const;
	void SetAllocMultiSelect(bool b);

	SelectableFlags selectable_flags() const;
	void set_selectable_flags(SelectableFlags flags);

	void Paint(AbstractItemView* view, const ModelIndex& index) override;

	_MW_IMPL
};
}
