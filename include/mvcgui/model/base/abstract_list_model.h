#pragma once
#include <mvcgui/model/base/abstract_item_model.h>
#include <mvcgui/core/signal.h>

namespace mvcgui {
class AbstractListModel : public AbstractItemModel
{
public:
	AbstractListModel() = default;

	size_t column_count() const override { return 1; }

	Signal<ModelIndex> on_item_text_changed_;
	Signal<ModelIndex, size_t> on_rows_inserted_;
	Signal<ModelIndex, size_t> on_rows_removed_;

private:
	InsertedItems InsertColumns(size_t col) override { assert(false); return {}; }
	InsertedItems InsertColumns(size_t col, size_t count) override { assert(false); return {}; }
	void RemoveColumns(size_t col, size_t count) override { assert(false); }
	void set_column_count(size_t count) override { assert(false); }
};

using AbstractListModelPtr = std::shared_ptr<AbstractListModel>;
}