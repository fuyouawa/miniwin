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

	void set_system_data(const ModelIndex& idx, const SystemData& data) override;
	void set_user_data(const ModelIndex& idx, const UserData& data) override;
	void set_text(const ModelIndex& idx, std::u8string_view text) override;

	const SystemData& system_data(const ModelIndex& idx) const override;
	const UserData& user_data(const ModelIndex& idx) const override;
	const std::u8string& text(const ModelIndex& idx) const override;

protected:
	std::vector<ItemDataNode> data_list_;
};
}