#pragma once
#include <fugui/model/base/abstract_table_model.h>

namespace fugui {
class StandardTableModel : public AbstractTableModel
{
public:
	StandardTableModel();

	InsertedItems InsertRows(size_t row, size_t count) override;
	void RemoveRows(size_t row, size_t count) override;
	size_t row_count() const override;

	InsertedItems InsertColumns(size_t col, size_t count) override;
	void RemoveColumns(size_t col, size_t count) override;
	size_t column_count() const override;

	void Clear() override;

	float row_minimum_height(size_t row) const override;
	void set_row_minimum_height(size_t row, float height) override;
private:
	void set_item_data(const ModelIndex& idx, ModelItemData&& data) override;
	const ModelItemData& item_data(const ModelIndex& idx) const override;

	const TableColumnData& column_data(size_t column) const override;
	void set_column_data(size_t column, TableColumnData&& data) override;

	struct RowConfig {
		float minimun_height{ 0 };
	};

	using RowItemsData = std::vector<ModelItemData>;
	using RowData = std::pair<RowItemsData, RowConfig>;

	std::vector<TableColumnData> column_datas_;
	std::list<RowData> table_items_;
};
}