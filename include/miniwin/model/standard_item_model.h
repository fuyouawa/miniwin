#pragma once
#include <miniwin/model/base/abstract_item_model.h>

namespace miniwin {
class StandardItemModel : AbstractItemModel
{
public:
    StandardItemModel();

    void InsertRows(size_t row, size_t count) override;
    void RemoveRows(size_t row, size_t count) override;
    size_t row_count() const override;

    void InsertColumns(size_t column, size_t count) override;
    void RemoveColumns(size_t column, size_t count) override;
    size_t column_count() const override;

    std::optional<const std::any&> user_data(const ModelIndex& idx) const override;
    void set_user_data(const ModelIndex& idx, std::any&& data) override;

    std::u8string_view text(const ModelIndex& idx) const override;
    void set_text(const ModelIndex& idx, std::u8string_view text) override;

    int flags(const ModelIndex& idx) const override;
    void set_flags(const ModelIndex& idx, int flags) override;

    void Clear() override;

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
}
