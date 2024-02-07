#include <mvcgui/model/standard_table_model.h>

namespace mvcgui {
StandardTableModel::StandardTableModel()
	: AbstractTableModel{}
{
}

InsertedItems StandardTableModel::InsertRows(size_t row, size_t count) {
	assert(row <= row_count());
	auto pos = std::next(table_items_.begin(), row);

	RowData tmp{ RowItemsData(column_count()), {} };
	table_items_.insert(pos, count, std::move(tmp));

	Emit(on_rows_inserted_, row, count);
	ModelIndex top_left{ row, 0 };
	ModelIndex bottom_right{ row + count, column_count() };
	return { shared_from_this(), { top_left, bottom_right} };
}

void StandardTableModel::RemoveRows(size_t row, size_t count) {
	assert(row + count <= row_count());
	auto start = std::next(table_items_.begin(), row);
	auto end = std::next(start, row);
	table_items_.erase(start, end);
	Emit(on_rows_removed_, row, count);
}

size_t StandardTableModel::row_count() const {
	return table_items_.size();
}

InsertedItems StandardTableModel::InsertColumns(size_t col, size_t count) {
	assert(col <= column_count());
	for (auto& [row_data, _] : table_items_) {
		assert(row_data.size() == column_count());
		auto pos = std::next(row_data.begin(), col);
		row_data.insert(pos, count, {});
	}

	auto hori_header_pos = std::next(column_datas_.begin(), col);
	column_datas_.insert(hori_header_pos, count, {});

	Emit(on_columns_inserted_, col, count);
	ModelIndex top_left{ 0, col };
	ModelIndex bottom_right{ row_count(), col + count };
	return { shared_from_this(), { top_left, bottom_right} };
}

void StandardTableModel::RemoveColumns(size_t col, size_t count) {
	assert(col + count <= column_count());
	for (auto& [row_data, _] : table_items_) {
		assert(row_data.size() == column_count());
		auto start = std::next(row_data.begin(), col);
		auto end = std::next(start, count);
		row_data.erase(start, end);
	}

	auto hori_header_start = std::next(column_datas_.begin(), col);
	auto hori_header_end = std::next(hori_header_start, count);
	column_datas_.erase(hori_header_start, hori_header_end);
	Emit(on_columns_removed_, col, count);
}
size_t StandardTableModel::column_count() const {
	return column_datas_.size();
}

void StandardTableModel::Clear() {
	table_items_.clear();
	column_datas_.clear();
}

void StandardTableModel::set_item_data(const ModelIndex& idx, ModelItemData&& data) {
	assert(idx.row() < row_count());
	assert(idx.column() < column_count());
	auto& row_data = std::next(table_items_.begin(), idx.row())->first;
	row_data[idx.column()] = std::move(data);
}

const ModelItemData& StandardTableModel::item_data(const ModelIndex& idx) const {
	assert(idx.row() < row_count());
	assert(idx.column() < column_count());
	auto& row_data = std::next(table_items_.begin(), idx.row())->first;
	return row_data[idx.column()];
}

const TableColumnData& StandardTableModel::column_data(size_t column) const {
	assert(column < column_count());
	return column_datas_[column];
}

void StandardTableModel::set_column_data(size_t column, TableColumnData&& data) {
	assert(column < column_count());
	column_datas_[column] = std::move(data);
}

float StandardTableModel::row_minimum_height(size_t row) const {
	assert(row < row_count());
	auto& cfg = std::next(table_items_.begin(), row)->second;
	return cfg.minimun_height;
}

void StandardTableModel::set_row_minimum_height(size_t row, float height) {
	assert(row < row_count());
	auto& cfg = std::next(table_items_.begin(), row)->second;
	cfg.minimun_height = height;
}
}