#include "combobox_view_impl.h"

#include <miniwin/delegate/selectable_item_delegate.h>

namespace miniwin {
ComboBoxView::Impl::Impl(ComboBoxView* owner)
	: owner_(owner)
{
}

void ComboBoxView::Impl::Init()
{
    auto d = new SelectableItemDelegate(owner_);
    owner_->SetItemDelegate(d);
}
}
