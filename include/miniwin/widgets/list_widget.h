#pragma once
#include <miniwin/core/widget.h>
#include <miniwin/delegate/base/abstract_item_delegate.h>
#include <miniwin/model/base/abstract_item_model.h>

namespace miniwin {
class ListWidget : public Widget {
public:
	ListWidget();
	~ListWidget() override;

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

	String RightLabel() const;
	void SetRightLabel(const String& label);

	Vector2D Size() const override;
	void SetSize(const Vector2D& size) override;
	Vector2D Position() const override;
	void SetPosition(const Vector2D& pos) override;

protected:
	void Awake() override;

protected:
	_MW_IMPL
};
}