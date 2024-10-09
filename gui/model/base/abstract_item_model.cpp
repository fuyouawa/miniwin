#include <fugui/model/base/abstract_item_model.h>

namespace fugui {
InsertedItems::InsertedItems(AbstractItemModelPtr model, const ModelIndexRange& range)
	: model_{ model },
	range_{ range }
{
}

InsertedItems& InsertedItems::InitializeColumn(size_t column, std::initializer_list<std::u8string_view> texts) {
	assert(texts.size() <= range_.row_count());
	auto text_beg = texts.begin();
	range_.ForeachRow(column, [&, this](auto& idx, auto i) {
		model_->set_text(idx, *text_beg);
		++text_beg;
		return i < texts.size();
	});
	return *this;
}

InsertedItems& InsertedItems::InitializeRow(size_t row, std::initializer_list<std::u8string_view> texts) {
	assert(texts.size() <= range_.column_count());
	auto text_beg = texts.begin();
	range_.ForeachColumn(row, [&, this](auto& idx, auto i) {
		model_->set_text(idx, *text_beg);
		++text_beg;
		return i < texts.size();
		});
	return *this;
}

InsertedItems& InsertedItems::Default(std::u8string_view text) {
	for (size_t i = 0; i < range_.column_count(); i++) {
		range_.ForeachRow(i, [&, this](auto& idx, auto i) {
			model_->set_text(idx, text);
			return true;
		});
	}
	return *this;
}

InsertedItems AbstractItemModel::InsertRow(size_t row) {
	return InsertRows(row, 1);
}
InsertedItems AbstractItemModel::InsertColumn(size_t col) {
	return InsertColumns(col, 1);
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

void AbstractItemModel::set_column_count(size_t count) {
	auto col_n = column_count();

	if (count == col_n) return;
	if (count > col_n) {
		InsertColumns(col_n - 1, count - col_n);
	}
	else {
		RemoveRows(count, count - col_n);
	}
}


void AbstractItemModel::set_system_data(const ModelIndex& idx, SystemData&& data) {
	auto d = item_data(idx);
	d.sys_data = std::move(data);
	set_item_data(idx, std::move(d));
}
void AbstractItemModel::set_user_data(const ModelIndex& idx, UserData&& data) {
	auto d = item_data(idx);
	d.user_data = std::move(data);
	set_item_data(idx, std::move(d));
}
void AbstractItemModel::set_text(const ModelIndex& idx, std::u8string_view text) {
	auto d = item_data(idx);
	d.text = text;
	set_item_data(idx, std::move(d));
}
void AbstractItemModel::set_selection(const ModelIndex& idx, bool b) {
	auto d = item_data(idx);
	d.selection = b;
	set_item_data(idx, std::move(d));
}

const SystemData& AbstractItemModel::system_data(const ModelIndex& idx) const {
	return item_data(idx).sys_data;
}
const UserData& AbstractItemModel::user_data(const ModelIndex& idx) const {
	return item_data(idx).user_data;
}
const std::u8string& AbstractItemModel::text(const ModelIndex& idx) const {
	return item_data(idx).text;
}
bool AbstractItemModel::is_selected(const ModelIndex& idx) const {
	return item_data(idx).selection;
}

std::vector<ModelIndex> AbstractItemModel::GetSelectionItems() const {
	std::vector<ModelIndex> res{};
	for (size_t i = 0; i < row_count(); i++) {
		for (size_t j = 0; j < column_count(); j++) {
			ModelIndex idx{ i, j };
			if (is_selected(idx)) {
				res.push_back(idx);
			}
		}
	}
	return res;
}

void AbstractItemModel::ClearSelection() {
	for (size_t i = 0; i < row_count(); i++) {
		for (size_t j = 0; j < column_count(); j++) {
			set_selection({ i, j }, false);
		}
	}
}
}