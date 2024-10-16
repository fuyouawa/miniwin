#pragma once
#include <miniwin/core/object.h>
#include <miniwin/model/base/model_index.h>
#include <any>

namespace miniwin {
enum class Orientation
{
    Horizontal,
    Vertical
};

enum class ItemRole
{
    Display,
    UserData,
    Flags
};

class AbstractItemModel : public Object
{
public:
    static AbstractItemModel* StaticEmptyModel();

    AbstractItemModel(Object* parent);

	virtual void InsertRow(size_t row);
    virtual void InsertRows(size_t row, size_t count) = 0;
    virtual void RemoveRow(size_t row);
	virtual void RemoveRows(size_t row, size_t count) = 0;

    virtual size_t RowCount() const = 0;
    virtual void SetRowCount(size_t count);

    virtual void InsertColumn(size_t column);
    virtual void InsertColumns(size_t column, size_t count) = 0;
    virtual void RemoveColumn(size_t column);
    virtual void RemoveColumns(size_t column, size_t count) = 0;

    virtual size_t column_count() const = 0;
    virtual void set_column_count(size_t count);

	virtual void Clear() = 0;

    virtual const std::any& GetData(const ModelIndex& index, ItemRole role = ItemRole::Display) const = 0;
    virtual void SetData(const ModelIndex& index, std::any&& data, ItemRole role = ItemRole::Display) = 0;

    virtual const std::any& GetHeaderData(int section, Orientation orientation, ItemRole role = ItemRole::Display) const = 0;
    virtual void SetHeaderData(int section, Orientation orientation, std::any&& data, ItemRole role = ItemRole::Display) = 0;

    virtual bool IsValidIndex(const ModelIndex& index) const;

    MW_SIGNAL(OnRowsInserted, (size_t) row, (size_t) count)
    MW_SIGNAL(OnRowsRemoved, (size_t) row, (size_t) count)
    MW_SIGNAL(OnColumnsInserted, (size_t) column, (size_t) count)
    MW_SIGNAL(OnColumnsRemoved, (size_t) column, (size_t) count)
};
}
