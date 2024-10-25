#pragma once
#include <miniwin/model/standard_item_model.h>

namespace miniwin {
using StandardItem = std::unordered_map<ItemRole, Variant>;

using StandardLineItems = List<StandardItem>;

class StandardItemModel::Impl
{
public:
    explicit Impl(StandardItemModel* owner);

    size_t RowCount() const;

    size_t ColumnCount() const;

    void SetRowCount(size_t c);

    void SetColumnCount(size_t c);

    void InsertRows(size_t row, size_t count);

    void RemoveRows(size_t row, size_t count);

    void InsertColumns(size_t column, size_t count);

    void RemoveColumns(size_t column, size_t count);

    StandardItem& Item(const ModelIndex& idx);

    StandardItem& GetOrCreateItem(const ModelIndex& idx);

    void Clear();

    StandardItemModel* owner_;
    List<StandardLineItems> items_;
    size_t column_count_;
    StandardLineItems horizontal_header_items_;
    StandardLineItems vertical_header_items_;
};
}
