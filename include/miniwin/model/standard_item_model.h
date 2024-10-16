#pragma once
#include <miniwin/model/base/abstract_item_model.h>

namespace miniwin {
class StandardItemModel : AbstractItemModel
{
public:
    StandardItemModel(Object* parent);

    void InsertRows(size_t row, size_t count) override;
    void RemoveRows(size_t row, size_t count) override;
    size_t row_count() const override;

    void InsertColumns(size_t column, size_t count) override;
    void RemoveColumns(size_t column, size_t count) override;
    size_t column_count() const override;

    const std::any& data(const ModelIndex& index, ItemRole role) const override;
    void set_data(const ModelIndex& index, std::any&& data, ItemRole role) override;

    const std::any& header_data(int section, Orientation orientation, ItemRole role) const override;
    void set_header_data(int section, Orientation orientation, std::any&& data, ItemRole role) override;

    std::u8string_view text(const ModelIndex& index) const;
    void set_text(const ModelIndex& index, std::u8string_view text);

    int flags(const ModelIndex& index) const;
    void set_flags(const ModelIndex& index, int flags);

    std::u8string_view header_text(int section, Orientation orientation) const;
    void set_header_text(int section, Orientation orientation, std::u8string_view text);

    int header_flags(int section, Orientation orientation) const;
    void set_header_flags(int section, Orientation orientation, int flags);

    void Clear() override;

    _MW_IMPL
};
}
