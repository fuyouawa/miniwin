#pragma once
#include <miniwin/core/widget.h>
#include <miniwin/model/base/abstract_item_model.h>
#include <miniwin/model/item_selection_model.h>
#include <miniwin/delegate/base/abstract_item_delegate.h>

namespace miniwin {
class AbstractItemView : Widget
{
public:
    AbstractItemView(Widget* parent, bool show);

    virtual void set_model(AbstractItemModel* model);
    AbstractItemModel* model() const;

    virtual void set_selection_model(ItemSelectionModel* selection_model);
    ItemSelectionModel* selection_model() const;

    virtual void set_item_delegate(AbstractItemDelegate* item_delegate);
    AbstractItemDelegate* item_delegate() const;

    _MW_IMPL
};
}
