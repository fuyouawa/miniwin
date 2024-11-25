#pragma once
#include <miniwin/tools/variant.h>
#include <miniwin/delegate/base/abstract_item_delegate.h>
#include <miniwin/model/base/abstract_item_model.h>
#include <miniwin/widgets/base/abstract_item_view.h>
#include <miniwin/tools/stringlist.h>
#include <miniwin/widgets/view/combobox_view.h>

namespace miniwin {

class ComboBox : public ComboBoxView {
	MW_OBJECT
public:
	ComboBox();
	~ComboBox() override;

	size_t CurrentIndex() const;
	Variant CurrentData(ItemRole role) const;
	String CurrentText() const;

	void AddItem(const String& text, const Variant& user_data = {});
	void AddItems(const StringList& texts);

	void InsertItem(size_t index, const String& text, const Variant& user_data = {});
	void InsertItems(size_t index, const StringList& texts);

protected:
	void Awake() override;

	_MW_IMPL
};
}
