#include "listview_impl.h"

#include <miniwin/delegate/selectable_item_delegate.h>

namespace miniwin {
ListView::Impl::Impl(ListView* owner)
	: owner_(owner)
{
}

void ListView::Impl::Init()
{
    auto d = new SelectableItemDelegate(owner_);
    owner_->SetItemDelegate(d);
}
}
