#pragma once
#include <miniwin/core/widget.h>
#include <miniwin/model/base/abstract_item_model.h>
#include <miniwin/model/item_selection_model.h>
#include <miniwin/delegate/base/abstract_item_delegate.h>

namespace miniwin {
class AbstractItemView : public Widget
{
public:
    AbstractItemView(Widget* parent);
    ~AbstractItemView() override;

    virtual void SetModel(AbstractItemModel* model);
    AbstractItemModel* GetModel() const;

    virtual void SetSelectionModel(ItemSelectionModel* selection_model);
    ItemSelectionModel* GetSelectionModel() const;

    virtual void SetItemDelegate(AbstractItemDelegate* item_delegate);
    AbstractItemDelegate* GetItemDelegate() const;

    _MW_IMPL
};
}
