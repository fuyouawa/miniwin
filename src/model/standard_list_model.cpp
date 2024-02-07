#include <mvcgui/model/standard_list_model.h>

namespace mvcgui {
StandardListModel::StandardListModel()
	: AbstractListModel{ }
{}

InsertedItems StandardListModel::InsertRows(size_t row, size_t count) {
	item_datas_.insert(item_datas_.begin() + row, count, {});
	Emit(on_rows_inserted_, row, count);
	return InsertedItems{ shared_from_this(), { row, row + count } };
}

void StandardListModel::RemoveRows(size_t row, size_t count) {
	auto beg = item_datas_.begin() + row;
	auto end = beg + count;
	item_datas_.erase(beg, end);
	Emit(on_rows_removed_, row, count);
}

void StandardListModel::Clear() {
	item_datas_.clear();
}

size_t StandardListModel::row_count() const {
	return item_datas_.size();
}

void StandardListModel::set_item_data(const ModelIndex& idx, ModelItemData&& data) {
	assert(idx.column() == 0);
	item_datas_[idx.row()] = std::move(data);
}

const ModelItemData& StandardListModel::item_data(const ModelIndex& idx) const {
	assert(idx.column() == 0);
	return item_datas_[idx.row()];
}
}