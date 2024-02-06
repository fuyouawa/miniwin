#pragma once
#include <mvcgui/model/base/abstract_list_model.h>

namespace mvcgui {
class StandardListModel : public AbstractListModel
{
public:
	StandardListModel();

	InsertedItems InsertRows(size_t row, size_t count) override;
	void RemoveRows(size_t row, size_t count) override;

	void set_row_count(size_t count) override;
	void Clear() override;

	size_t row_count() const override;

	void set_item_data(const ModelIndex& idx, ModelItemData&& data) override;
	const ModelItemData& item_data(const ModelIndex& idx) const override;

protected:
	std::vector<ModelItemData> item_datas_;
};
}