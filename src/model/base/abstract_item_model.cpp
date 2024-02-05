#include <mvcgui/model/base/abstract_item_model.h>

namespace mvcgui {
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
InsertedItems AbstractItemModel::InsertColumns(size_t col) {
	return InsertColumns(col, 1);
}
}