#pragma once
#include <fugui/widgets/view/base/abstract_item_view.h>
#include <fugui/model/base/abstract_table_model.h>

namespace fugui {
class TableView : public AbstractItemView
{
public:
    TableView(Widget* const parent, std::u8string_view label, bool show=true);

	void set_model(AbstractTableModelPtr model) { model_ = model; }
	AbstractTableModelPtr model() const {
		return std::dynamic_pointer_cast<AbstractTableModel>(model_);
	}

private:
	void OnItemShowablePaintBegin() override;
	void OnItemShowablePaintEnd() override;

	bool table_open_;
};
}