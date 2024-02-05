#pragma once
#include <mvcgui/model/base/abstract_item_model.h>
#include <mvcgui/core/signal.h>

namespace mvcgui {
class AbstractTableModel : public AbstractItemModel
{
public:
	AbstractTableModel() = default;

	Signal<ModelIndex, size_t> on_columns_inserted_;
	Signal<ModelIndex, size_t> on_columns_removed_;
};

using AbstractTableModelPtr = std::shared_ptr<AbstractTableModel>;
}