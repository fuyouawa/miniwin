#pragma once
#include <mvcgui/core/object.h>
#include <any>
#include <mvcgui/model/base/model_index.h>

namespace mvcgui {
class AbstractItemModel;
using AbstractItemModelPtr = std::shared_ptr<AbstractItemModel>;

using UserData = std::any;
using SystemData = std::any;

struct ModelItemData
{
	std::u8string text;
	UserData user_data;
	SystemData sys_data;
	bool selection;
};

class InsertedItems
{
public:
	InsertedItems() { assert(false); }
	InsertedItems(AbstractItemModelPtr model, const ModelIndexRange& range);

	InsertedItems& InitializeColumn(size_t column, std::initializer_list<std::u8string_view> texts);
	InsertedItems& InitializeRow(size_t row, std::initializer_list<std::u8string_view> texts);
	InsertedItems& Default(std::u8string_view text);

private:
	AbstractItemModelPtr model_;
	ModelIndexRange range_;
};


class AbstractItemModel : public Object, public std::enable_shared_from_this<AbstractItemModel>
{
public:
	AbstractItemModel() = default;
	virtual ~AbstractItemModel() = default;

	virtual InsertedItems InsertRow(size_t row);
	virtual InsertedItems InsertRows(size_t row, size_t count) = 0;
	virtual void RemoveRows(size_t row, size_t count) = 0;
	virtual void set_row_count(size_t count) = 0;
	virtual size_t row_count() const = 0;

	virtual InsertedItems InsertColumn(size_t col);
	virtual InsertedItems InsertColumns(size_t col, size_t count) = 0;
	virtual void RemoveColumns(size_t col, size_t count) = 0;
	virtual void set_column_count(size_t count) = 0;
	virtual size_t column_count() const = 0;

	virtual void Clear() = 0;

	virtual void set_system_data(const ModelIndex& idx, SystemData&& data);
	virtual void set_user_data(const ModelIndex& idx, UserData&& data);
	virtual void set_text(const ModelIndex& idx, std::u8string_view text);
	virtual void set_selection(const ModelIndex& idx, bool b);

	virtual const SystemData& system_data(const ModelIndex& idx) const;
	virtual const UserData& user_data(const ModelIndex& idx) const;
	virtual const std::u8string& text(const ModelIndex& idx) const;
	virtual bool is_selected(const ModelIndex& idx) const;

	virtual std::vector<ModelIndex> GetSelectionItems() const;
	virtual void ClearSelection();

	virtual void set_item_data(const ModelIndex& idx, ModelItemData&& data) = 0;
	virtual const ModelItemData& item_data(const ModelIndex& idx) const = 0;
};
}