#pragma once
#include <miniwin/widgets/base/abstract_button.h>
#include <miniwin/delegate/base/abstract_item_delegate.h>

#include <miniwin/model/base/abstract_item_model.h>
#include <miniwin/tools/variant.h>

namespace miniwin {
class ComboBox : public Widget {
public:
	ComboBox(Widget* parent, std::u8string_view label);

	ComboBoxFlags flags() const;
	void set_flags(ComboBoxFlags flags) const;

	std::u8string_view label() const;
	void set_label(std::u8string_view label);

	void SetItemDelegate(AbstractItemDelegate* delegate);
	AbstractItemDelegate* ItemDelegate() const;

	void SetModel(AbstractItemModel* model);
	AbstractItemModel* Model() const;

	size_t CurrentIndex() const;
	Variant CurrentData(ItemRole role) const;
	std::u8string CurrentText() const;

	void AddItem(std::u8string_view text, const Variant& user_data = {});
	void AddItems(std::initializer_list<std::u8string_view> texts);

	void InsertItem(size_t index, std::u8string_view text, const Variant& user_data = {});
	void InsertItems(size_t index, std::initializer_list<std::u8string_view> texts);

	_MW_IMPL
};
}
