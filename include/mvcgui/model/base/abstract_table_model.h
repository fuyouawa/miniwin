#pragma once
#include <mvcgui/model/base/abstract_item_model.h>
#include <mvcgui/core/signal.h>

namespace mvcgui {
struct TableColumnData {
	unsigned id{ 0 };
	int flags{ 0 };
	float width{ 0.0f };
	std::u8string text{ u8"Default" };
};

class AbstractTableModel : public AbstractItemModel
{
public:
	AbstractTableModel() = default;

	virtual float row_minimum_height(size_t row) const = 0;
	virtual void set_row_minimum_height(size_t row, float height) = 0;

	virtual unsigned column_id(size_t column) const;
	virtual int column_flags(size_t column) const;
	virtual float column_width(size_t column) const;
	virtual const std::u8string& column_text(size_t column) const;

	//TODO ·¢ËÍÐÅºÅ
	virtual void set_column_id(size_t column, unsigned id);
	virtual void set_column_flags(size_t column, int flags);
	virtual void set_column_width(size_t column, float width);
	virtual void set_column_text(size_t column, std::u8string_view text);

protected:
	virtual const TableColumnData& column_data(size_t column) const = 0;
	virtual void set_column_data(size_t column, TableColumnData&& data) = 0;
};

using AbstractTableModelPtr = std::shared_ptr<AbstractTableModel>;
}