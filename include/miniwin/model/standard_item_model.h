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

    const std::any& user_data(const ModelIndex& index) const override;
    void set_user_data(const ModelIndex& index, std::any&& data) override;

    std::u8string_view text(const ModelIndex& index) const override;
    void set_text(const ModelIndex& index, std::u8string_view text) override;

    int flags(const ModelIndex& index) const override;
    void set_flags(const ModelIndex& index, int flags) override;

    void Clear() override;

    const std::any& header_data(int section, Orientation orientation, ItemRole role) override;
    void set_header_data(int section, Orientation orientation, ItemRole role, const std::any& data) override;

    _MW_IMPL
};
}
