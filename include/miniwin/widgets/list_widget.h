#pragma once
#include <miniwin/core/widget.h>
#include <miniwin/delegate/base/abstract_item_delegate.h>
#include <miniwin/model/base/abstract_item_model.h>
#include <miniwin/widgets/view/list_view.h>

namespace miniwin {
class ListWidget : public ListView {
public:
	ListWidget();
	~ListWidget() override;

	size_t CurrentIndex() const;
	Variant CurrentData(ItemRole role) const;
	String CurrentText() const;

	void AddItem(const String& text, const Variant& user_data = {});
	void AddItems(const StringList& texts);

	void InsertItem(size_t index, const String& text, const Variant& user_data = {});
	void InsertItems(size_t index, const StringList& texts);

protected:
	void Awake() override;
	void PaintBegin(size_t index) override;

	_MW_IMPL
};
}