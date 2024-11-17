#include "list_view_impl.h"

#include <miniwin/delegate/selectable_item_delegate.h>

namespace miniwin {
ListView::Impl::Impl(ListView* owner)
	: owner_(owner)
{
}

void ListView::Impl::Awake()
{
    auto d = Instantiate<SelectableItemDelegate>(owner_->shared_from_this());
    owner_->SetItemDelegate(d);
}
}
