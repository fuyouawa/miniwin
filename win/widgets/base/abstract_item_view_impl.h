#pragma once
#include <miniwin/widgets/base/abstract_item_view.h>

namespace miniwin {
class AbstractItemView::Impl {
public:
    explicit Impl(AbstractItemView* owner);

    AbstractItemView* owner_;
    AbstractItemModel* model_ = nullptr;
    AbstractItemDelegate* item_delegate_ = nullptr;
    ItemSelectionModel* selection_model_ = nullptr;
};
}
