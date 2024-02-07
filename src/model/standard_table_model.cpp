#include <mvcgui/model/standard_table_model.h>

namespace mvcgui {
StandardTableModel::StandardTableModel()
	: AbstractTableModel{}
{
}

InsertedItems StandardTableModel::InsertRows(size_t row, size_t count) {
	assert(row <= row_count());
	auto pos = std::next(item_datas_.begin(), row);
	RowData val_tmp(column_count());

	item_datas_.insert(pos, count, val_tmp);

	Emit(on_rows_inserted_, row, count);
	ModelIndex top_left{ row, 0 };
	ModelIndex bottom_right{ row + count, column_count() };
	return { shared_from_this(), { top_left, bottom_right} };
}

void StandardTableModel::RemoveRows(size_t row, size_t count) {
	assert(row + count <= row_count());
	auto start = std::next(item_datas_.begin(), row);
	auto end = std::next(start, row);
	item_datas_.erase(start, end);
	Emit(on_rows_removed_, row, count);
}

size_t StandardTableModel::row_count() const {
	return item_datas_.size();
}

InsertedItems StandardTableModel::InsertColumns(size_t col, size_t count) {
	assert(col <= column_count());
	for (auto& row : item_datas_) {
		assert(row.size() == column_count());
		auto pos = std::next(row.begin(), col);
		row.insert(pos, count, {});
	}

	auto hori_header_pos = std::next(hori_header_datas_.begin(), col);
	hori_header_datas_.insert(hori_header_pos, count, {});

	Emit(on_columns_inserted_, col, count);
	ModelIndex top_left{ 0, col };
	ModelIndex bottom_right{ row_count(), col + count };
	return { shared_from_this(), { top_left, bottom_right} };
}

void StandardTableModel::RemoveColumns(size_t col, size_t count) {
	assert(col + count <= column_count());
	for (auto& row : item_datas_) {
		assert(row.size() == column_count());
		auto start = std::next(row.begin(), col);
		auto end = std::next(start, count);
		row.erase(start, end);
	}

	auto hori_header_start = std::next(hori_header_datas_.begin(), col);
	auto hori_header_end = std::next(hori_header_start, count);
	hori_header_datas_.erase(hori_header_start, hori_header_end);
	Emit(on_columns_removed_, col, count);
}
size_t StandardTableModel::column_count() const {
	return hori_header_datas_.size();
}

void StandardTableModel::Clear() {
	item_datas_.clear();
	hori_header_datas_.clear();
}

void StandardTableModel::set_item_data(const ModelIndex& idx, ModelItemData&& data) {
	assert(idx.row() < row_count());
	assert(idx.column() < column_count());
	auto row_pos = std::next(item_datas_.begin(), idx.row());
	row_pos->at(idx.column()) = std::move(data);
}

const ModelItemData& StandardTableModel::item_data(const ModelIndex& idx) const {
	assert(idx.row() < row_count());
	assert(idx.column() < column_count());
	auto row_pos = std::next(item_datas_.begin(), idx.row());
	return row_pos->at(idx.column());
}

const TableHorizontalHeaderData& StandardTableModel::hori_header_data(size_t column) {
	assert(column < column_count());
	return hori_header_datas_[column];
}

void StandardTableModel::set_hori_header_data(size_t column, TableHorizontalHeaderData&& data) {
	assert(column < column_count());
	hori_header_datas_[column] = std::move(data);
}
}