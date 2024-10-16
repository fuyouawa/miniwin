#include <miniwin/model/base/abstract_item_model.h>

namespace miniwin {
class EmptyItemModel : public AbstractItemModel
{
public:
    EmptyItemModel() : AbstractItemModel(nullptr) {}

    void InsertRows(size_t row, size_t count) override {}
    void RemoveRows(size_t row, size_t count) override {}
    size_t row_count() const override { return 0; }
    void InsertColumns(size_t column, size_t count) override {}
    void RemoveColumns(size_t column, size_t count) override {}
    size_t column_count() const override { return 0; }
    void Clear() override {}
    const std::any& data(const ModelIndex& index, ItemRole role) const override {
        static std::any empty;
        return empty;
    }
    void set_data(const ModelIndex& index, std::any&& data, ItemRole role) override {}
    const std::any& header_data(int section, Orientation orientation, ItemRole role) const override {
        static std::any empty;
        return empty;
    }
    void set_header_data(int section, Orientation orientation, std::any&& data, ItemRole role) override {}
};

AbstractItemModel* AbstractItemModel::StaticEmptyModel()
{
    static auto inst = new EmptyItemModel;
    return inst;
}

AbstractItemModel::AbstractItemModel(Object* parent)
    : Object(parent, u8"Model", ObjectType::Model)
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

bool AbstractItemModel::IsValidIndex(const ModelIndex& index) const
{
    return index.valid() && index.row < row_count() && index.column < column_count();
}
}
