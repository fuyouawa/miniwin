#include <mvcgui/model/base/abstract_table_model.h>
#include <stdexcept>
#include <format>

namespace mvcgui {
unsigned AbstractTableModel::column_id(size_t column) const {
	return column_data(column).id;
}
int AbstractTableModel::column_flags(size_t column) const {
	return column_data(column).flags;
}
float AbstractTableModel::column_width(size_t column) const {
	return column_data(column).width;
}
const std::u8string& AbstractTableModel::column_text(size_t column) const {
	return column_data(column).text;
}

void AbstractTableModel::set_column_id(size_t column, unsigned id) {
	auto data = column_data(column);
	data.id = id;
	set_column_data(column, std::move(data));
}
void AbstractTableModel::set_column_flags(size_t column, int flags) {
	auto data = column_data(column);
	data.flags = flags;
	set_column_data(column, std::move(data));
}
void AbstractTableModel::set_column_width(size_t column, float width) {
	auto data = column_data(column);
	data.width = width;
	set_column_data(column, std::move(data));
}
void AbstractTableModel::set_column_text(size_t column, std::u8string_view text) {
	auto data = column_data(column);
	data.text = text;
	set_column_data(column, std::move(data));
}
}