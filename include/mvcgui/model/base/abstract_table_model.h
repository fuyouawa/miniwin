#pragma once
#include <mvcgui/model/base/abstract_item_model.h>
#include <mvcgui/core/signal.h>

namespace mvcgui {
struct TableHorizontalHeaderData {
	unsigned id;
	int flags;
	float width;
	std::u8string text;
};

class AbstractTableModel : public AbstractItemModel
{
public:
	AbstractTableModel() = default;

	virtual const TableHorizontalHeaderData& hori_header_data(size_t column) = 0;
	virtual void set_hori_header_data(TableHorizontalHeaderData&& data) = 0;

	Signal<ModelIndex, size_t> on_columns_inserted_;
	Signal<ModelIndex, size_t> on_columns_removed_;
};

using AbstractTableModelPtr = std::shared_ptr<AbstractTableModel>;
}