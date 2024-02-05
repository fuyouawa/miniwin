#pragma once
#include <mvcgui/core/object.h>

namespace mvcgui {
class ModelIndex;
class AbstractItemView;

class AbstractItemDelegate : public Object, public std::enable_shared_from_this<AbstractItemDelegate>
{
public:
	AbstractItemDelegate();

	virtual void Paint(const AbstractItemView& view, const ModelIndex& index) = 0;

	Signal<ModelIndex> on_current_index_changed_;
	Signal<ModelIndex, bool> on_selection_changed_;
};

using AbstractItemDelegatePtr = std::shared_ptr<AbstractItemDelegate>;
}