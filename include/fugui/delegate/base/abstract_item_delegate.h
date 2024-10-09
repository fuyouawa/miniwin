#pragma once
#include <fugui/core/object.h>

namespace fugui {
class ModelIndex;
class AbstractItemModel;
using AbstractItemModelPtr = std::shared_ptr<AbstractItemModel>;


class AbstractItemDelegate : public Object, public std::enable_shared_from_this<AbstractItemDelegate>
{
public:
	AbstractItemDelegate();

	virtual void Paint(AbstractItemModelPtr model, const ModelIndex& index) = 0;

	Signal<ModelIndex> on_current_index_changed_;
	Signal<ModelIndex, bool> on_selection_changed_;
};

using AbstractItemDelegatePtr = std::shared_ptr<AbstractItemDelegate>;
}