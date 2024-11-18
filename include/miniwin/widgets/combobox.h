#pragma once
#include <miniwin/tools/variant.h>
#include <miniwin/delegate/base/abstract_item_delegate.h>
#include <miniwin/model/base/abstract_item_model.h>
#include <miniwin/widgets/base/abstract_item_view.h>
#include <miniwin/model/item_selection_model.h>
#include <miniwin/tools/stringlist.h>

namespace miniwin {
class ComboBoxView : public AbstractItemView {
	MW_OBJECT
public:
	ComboBoxView();
	~ComboBoxView() override;

	String Text() const;
	void SetText(const String& text);

protected:
	void Awake() override;
	void PaintBegin() override;

	_MW_IMPL
};

class ComboBox : public Widget {
	MW_OBJECT
public:
	ComboBox();
	~ComboBox() override;

	const String& Text() const;
	void SetText(const String& text);

	void SetItemDelegate(const SharedItemDelegate& delegate);
	const SharedItemDelegate& ItemDelegate() const;

	void SetModel(const SharedItemModel& model);
	const SharedItemModel& Model() const;

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
