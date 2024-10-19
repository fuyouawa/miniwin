#pragma once
#include <miniwin/model/base/abstract_item_model.h>

namespace miniwin {
class StandardItemModel : AbstractItemModel
{
public:
    StandardItemModel(Object* parent);

    void InsertRows(size_t row, size_t count) override;
    void RemoveRows(size_t row, size_t count) override;
    size_t RowCount() const override;

    void InsertColumns(size_t column, size_t count) override;
    void RemoveColumns(size_t column, size_t count) override;
    size_t ColumnCount() const override;

    Variant Data(const ModelIndex& index, ItemRole role) const override;
    void SetData(const ModelIndex& index, Variant&& data, ItemRole role) override;

    Variant HeaderData(size_t section, Orientation orientation, ItemRole role) const override;
    void SetHeaderData(size_t section, Orientation orientation, Variant&& data, ItemRole role) override;

    std::u8string_view Text(const ModelIndex& index) const;
    void SetText(const ModelIndex& index, std::u8string_view text);

    int Flags(const ModelIndex& index) const;
    void SetFlags(const ModelIndex& index, int flags);

    std::u8string_view HeaderText(int section, Orientation orientation) const;
    void SetHeaderText(int section, Orientation orientation, std::u8string_view text);

    int HeaderFlags(int section, Orientation orientation) const;
    void SetHeaderFlags(int section, Orientation orientation, int flags);

    void Clear() override;

    _MW_IMPL
};
}
