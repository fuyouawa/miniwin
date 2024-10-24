#pragma once
#include <miniwin/tools/variant.h>
#include <miniwin/delegate/base/abstract_item_delegate.h>
#include <miniwin/model/base/abstract_item_model.h>
#include <miniwin/widgets/base/abstract_item_view.h>

namespace miniwin {
class ComboBoxView : public AbstractItemView
{
public:
	ComboBoxView(Widget* parent, const String& text);
	~ComboBoxView() override;

	const String& Text() const;
	void SetText(const String& text);

protected:
	void PaintBegin() override;

	_MW_IMPL
};

class ComboBox : public Widget {
public:
	ComboBox(Widget* parent, const String& text);
	~ComboBox() override;

	const String& Text() const;
	void SetText(const String& text);

	void SetItemDelegate(AbstractItemDelegate* delegate);
	AbstractItemDelegate* ItemDelegate() const;

	void SetModel(AbstractItemModel* model);
	AbstractItemModel* Model() const;

	size_t CurrentIndex() const;
	Variant CurrentData(ItemRole role) const;
	String CurrentText() const;

	void AddItem(const String& text, const Variant& user_data = {});
	void AddItems(const StringList& texts);

	void InsertItem(size_t index, const String& text, const Variant& user_data = {});
	void InsertItems(size_t index, const StringList& texts);

	_MW_IMPL
};
}
