#pragma once
#include <miniwin/core/object.h>
#include <miniwin/model/base/model_index.h>
#include <any>
#include <optional>

namespace miniwin {

class AbstractItemModel : public Object
{
public:
    AbstractItemModel();

	virtual void InsertRow(size_t row);
    virtual void InsertRows(size_t row, size_t count) = 0;
    virtual void RemoveRow(size_t row);
	virtual void RemoveRows(size_t row, size_t count) = 0;

    virtual size_t row_count() const = 0;
    virtual void set_row_count(size_t count);

    virtual void InsertColumn(size_t column);
    virtual void InsertColumns(size_t column, size_t count) = 0;
    virtual void RemoveColumn(size_t column);
    virtual void RemoveColumns(size_t column, size_t count) = 0;

    virtual size_t column_count() const = 0;
    virtual void set_column_count(size_t count);

	virtual void Clear() = 0;

    virtual std::optional<std::reference_wrapper<const std::any>> user_data(const ModelIndex& index) const = 0;
	virtual void set_user_data(const ModelIndex& index, std::any&& data) = 0;

    virtual std::u8string_view text(const ModelIndex& index) const = 0;
	virtual void set_text(const ModelIndex& index, std::u8string_view text) = 0;

    virtual int flags(const ModelIndex& index) const = 0;
    virtual void set_flags(const ModelIndex& index, int flags) = 0;

    MW_SIGNAL(OnRowsInserted, (size_t) row, (size_t) count)
    MW_SIGNAL(OnRowsRemoved, (size_t) row, (size_t) count)
    MW_SIGNAL(OnColumnsInserted, (size_t) column, (size_t) count)
    MW_SIGNAL(OnColumnsRemoved, (size_t) column, (size_t) count)

private:
    using Object::parent;
    using Object::set_parent;
};
}
