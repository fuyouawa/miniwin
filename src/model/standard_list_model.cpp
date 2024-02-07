#include <mvcgui/model/standard_list_model.h>

namespace mvcgui {
StandardListModel::StandardListModel()
	: AbstractListModel{ }
{}

InsertedItems StandardListModel::InsertRows(size_t row, size_t count) {
	list_items_.insert(list_items_.begin() + row, count, {});
	Emit(on_rows_inserted_, row, count);
	return InsertedItems{ shared_from_this(), { row, row + count } };
}

void StandardListModel::RemoveRows(size_t row, size_t count) {
	auto beg = list_items_.begin() + row;
	auto end = beg + count;
	list_items_.erase(beg, end);
	Emit(on_rows_removed_, row, count);
}

void StandardListModel::Clear() {
	list_items_.clear();
}

size_t StandardListModel::row_count() const {
	return list_items_.size();
}

void StandardListModel::set_item_data(const ModelIndex& idx, ModelItemData&& data) {
	assert(idx.column() == 0);
	list_items_[idx.row()] = std::move(data);
}

const ModelItemData& StandardListModel::item_data(const ModelIndex& idx) const {
	assert(idx.column() == 0);
	return list_items_[idx.row()];
}
}