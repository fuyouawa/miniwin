#include <miniwin/widgets/base/abstract_item_view.h>

namespace miniwin {
class AbstractItemView::Impl {
public:
    Impl(AbstractItemView* owner)
        : owner_(owner)
    {

    }

    AbstractItemView* owner_;
    AbstractItemModel* model_;
    AbstractItemDelegate* item_delegate_;
    ItemSelectionModel* selection_model_;
};
}
