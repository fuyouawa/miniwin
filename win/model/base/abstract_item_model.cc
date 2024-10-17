#include <miniwin/model/base/abstract_item_model.h>

namespace miniwin {
class EmptyItemModel : public AbstractItemModel
{
public:
    EmptyItemModel() : AbstractItemModel(nullptr) {}

    void InsertRows(size_t row, size_t count) override {}
    void RemoveRows(size_t row, size_t count) override {}
    size_t RowCount() const override { return 0; }
    void InsertColumns(size_t column, size_t count) override {}
    void RemoveColumns(size_t column, size_t count) override {}
    size_t ColumnCount() const override { return 0; }
    void Clear() override {}
    const std::any& Data(const ModelIndex& index, ItemRole role) const override {
        static std::any empty;
        return empty;
    }
    void SetData(const ModelIndex& index, std::any&& data, ItemRole role) override {}
    const std::any& HeaderData(size_t section, Orientation orientation, ItemRole role) const override {
        static std::any empty;
        return empty;
    }
    void SetHeaderData(size_t section, Orientation orientation, std::any&& data, ItemRole role) override {}
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

void AbstractItemModel::SetRowCount(size_t count) {
	auto row_n = RowCount();

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
void AbstractItemModel::SetColumnCount(size_t count)
{
    auto col_n = ColumnCount();

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
    return index.valid() && index.row() < RowCount() && index.column() < ColumnCount();
}
}
