#include "win/widgets/base/abstract_item_view_impl.h"

namespace miniwin {
AbstractItemView::AbstractItemView(Widget* parent, bool show)
    : Widget(parent, u8"View", show, WidgetType::kView)
{
    impl_ = std::make_unique<Impl>(this);
}

void AbstractItemView::set_model(AbstractItemModel* model)
{
}

AbstractItemModel* AbstractItemView::model() const
{
    return impl_->model_;
}

void AbstractItemView::set_selection_model(ItemSelectionModel* selection_model)
{
}

ItemSelectionModel* AbstractItemView::selection_model() const
{
    return impl_->selection_model_;
}

void AbstractItemView::set_item_delegate(AbstractItemDelegate* delegate)
{
}

AbstractItemDelegate* AbstractItemView::item_delegate() const
{
    return impl_->item_delegate_;
}
}
