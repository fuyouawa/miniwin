#include <cassert>
#include <miniwin/model/base/abstract_item_model.h>

namespace miniwin {
bool ModelIndex::valid() const
{
    return row > 0 && column > 0;
}

bool operator==(const ModelIndex& x, const ModelIndex& y) {
    return x.row == y.row && x.column == y.column;
}
ModelIndex& operator+=(ModelIndex& x, const ModelIndex& y) {
    x.row += y.row;
    x.column += y.column;
    return x;
}
ModelIndex& operator-=(ModelIndex& x, const ModelIndex& y) {
    assert(x.row >= y.row);
    assert(x.column >= y.column);
    x.row -= y.row;
    x.column -= y.column;
    return x;
}

ModelIndex operator+(const ModelIndex& x, const ModelIndex& y)
{
    auto tmp = x;
    return tmp += y;
}

ModelIndex operator-(const ModelIndex& x, const ModelIndex& y)
{
    auto tmp = x;
    return tmp -= y;
}

AbstractItemModel::AbstractItemModel()
    : Object(nullptr, u8"Model", ObjectType::Model)
{
}

void AbstractItemModel::InsertRow(size_t row) {
	return InsertRows(row, 1);
}

void AbstractItemModel::RemoveRow(size_t row)
{
    RemoveRows(row, 1);
}

void AbstractItemModel::set_row_count(size_t count) {
	auto row_n = row_count();

	if (count == row_n) return;
	if (count > row_n) {
		InsertRows(row_n - 1, count - row_n);
	}
	else {
		RemoveRows(count, count - row_n);
	}
}

void AbstractItemModel::InsertColumn(size_t column)
{
    InsertColumns(column, 1);
}
void AbstractItemModel::RemoveColumn(size_t column)
{
    RemoveColumns(column, 1);
}
void AbstractItemModel::set_column_count(size_t count)
{
    auto col_n = column_count();

    if (count == col_n) return;
    if (count > col_n) {
        InsertColumns(col_n - 1, count - col_n);
    }
    else {
        RemoveRows(count, count - col_n);
    }
}

std::vector<ModelIndex> AbstractItemModel::GetSelectionItems() const {
	std::vector<ModelIndex> res{};
	for (int i = 0; i < static_cast<int>(row_count()); i++) {
		for (int j = 0; j < static_cast<int>(column_count()); j++) {
			ModelIndex idx{ i, j };
			if (is_selected(idx)) {
				res.push_back(idx);
			}
		}
	}
	return res;
}

void AbstractItemModel::ClearSelection() {
	for (int i = 0; i < static_cast<int>(row_count()); i++) {
		for (int j = 0; j < static_cast<int>(column_count()); j++) {
			set_selection({ i, j }, false);
		}
	}
}
}
