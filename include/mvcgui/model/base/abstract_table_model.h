#pragma once
#include <mvcgui/model/base/abstract_item_model.h>
#include <mvcgui/core/signal.h>

namespace mvcgui {
struct TableHorizontalHeaderData {
	unsigned id;
	int flags;
	float width;
	std::u8string text = u8"Default";
};

class AbstractTableModel : public AbstractItemModel
{
public:
	AbstractTableModel() = default;

	virtual const TableHorizontalHeaderData& hori_header_data(size_t column) = 0;
	virtual void set_hori_header_data(size_t column, TableHorizontalHeaderData&& data) = 0;
};

using AbstractTableModelPtr = std::shared_ptr<AbstractTableModel>;
}