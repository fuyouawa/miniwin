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
    size_t column_count() const override;

    const std::any& GetData(const ModelIndex& index, ItemRole role) const override;
    void SetData(const ModelIndex& index, std::any&& data, ItemRole role) override;

    const std::any& GetHeaderData(int section, Orientation orientation, ItemRole role) const override;
    void SetHeaderData(int section, Orientation orientation, std::any&& data, ItemRole role) override;

    std::u8string_view GetText(const ModelIndex& index) const;
    void SetText(const ModelIndex& index, std::u8string_view text);

    int GetFlags(const ModelIndex& index) const;
    void SetFlags(const ModelIndex& index, int flags);

    std::u8string_view GetHeaderText(int section, Orientation orientation) const;
    void SetHeaderText(int section, Orientation orientation, std::u8string_view text);

    int GetHeaderFlags(int section, Orientation orientation) const;
    void SetHeaderFlags(int section, Orientation orientation, int flags);

    void Clear() override;

    _MW_IMPL
};
}
