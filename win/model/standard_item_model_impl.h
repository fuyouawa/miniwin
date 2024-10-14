#pragma once
#include <optional>
#include <miniwin/model/standard_item_model.h>
#include <string>

namespace miniwin {
struct StandardItem
{
    std::u8string text;
    std::any user_data;
    int flags = 0;
};

class StandardItemModel::Impl
{
public:
    Impl(StandardItemModel* owner);

    StandardItemModel* owner_;

    size_t row_count() const;
    size_t column_count() const;

    void set_row_count(size_t c);
    void set_column_count(size_t c);

    void InsertRows(size_t row, size_t count);
    void RemoveRows(size_t row, size_t count);

    void InsertColumns(size_t column, size_t count);
    void RemoveColumns(size_t column, size_t count);

    std::optional<StandardItem&> item(const ModelIndex& idx);
    StandardItem& GetOrCreateItem(const ModelIndex& idx);

    void Clear();

private:
    using RowData = std::vector<StandardItem>;
    std::vector<RowData> items_;
    size_t column_count_;
};
}
