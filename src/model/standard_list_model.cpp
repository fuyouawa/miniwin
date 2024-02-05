#include <mvcgui/model/standard_list_model.h>

namespace mvcgui {
StandardListModel::StandardListModel()
	: AbstractListModel{ }
{}

InsertedItems StandardListModel::InsertRows(size_t row, size_t count) {
	data_list_.insert(data_list_.begin() + row, count, {});
	Emit(on_rows_inserted_, ModelIndex{ row }, count);
	return InsertedItems{ shared_from_this(), { row, row + count } };
}

void StandardListModel::RemoveRows(size_t row, size_t count) {
	auto beg = data_list_.begin() + row;
	auto end = beg + count;
	data_list_.erase(beg, end);
	Emit(on_rows_removed_, ModelIndex{ row }, count);
}

void StandardListModel::set_row_count(size_t count) {
	data_list_.resize(count);
}

void StandardListModel::Clear() {
	data_list_.clear();
}

size_t StandardListModel::row_count() const {
	return data_list_.size();
}

void StandardListModel::set_system_data(const ModelIndex& idx, const SystemData& data) {
	assert(idx.column() == 0);
	data_list_[idx.row()].sys_data = data;
}

void StandardListModel::set_user_data(const ModelIndex& idx, const UserData& data)
{
	assert(idx.column() == 0);
	data_list_[idx.row()].user_data = data;
}

const SystemData& StandardListModel::system_data(const ModelIndex& idx) const {
	assert(idx.column() == 0);
	return data_list_[idx.row()].sys_data;
}

const UserData& StandardListModel::user_data(const ModelIndex& idx) const
{
	assert(idx.column() == 0);
	return data_list_[idx.row()].user_data;
}

void StandardListModel::set_text(const ModelIndex& idx, std::u8string_view text)
{
	assert(idx.column() == 0);
	data_list_[idx.row()].text = text;
}

const std::u8string& StandardListModel::text(const ModelIndex& idx) const
{
	assert(idx.column() == 0);
	return data_list_[idx.row()].text;
}
}