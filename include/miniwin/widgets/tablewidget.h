#pragma once
#include <miniwin/core/widget.h>

#include "miniwin/delegate/base/abstract_item_delegate.h"
#include "miniwin/model/base/abstract_item_model.h"

namespace miniwin {
class TableWidget : public Widget {
public:
	TableWidget(Widget* parent, std::u8string_view id = u8"TableWidget");
	~TableWidget() override;

	void SetItemDelegate(AbstractItemDelegate* delegate);
	AbstractItemDelegate* ItemDelegate() const;

	void SetModel(AbstractItemModel* model);
	AbstractItemModel* Model() const;

	_MW_IMPL
};
}
