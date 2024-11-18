#include "table_view_impl.h"

#include <miniwin/delegate/selectable_item_delegate.h>

namespace miniwin {
TableView::Impl::Impl(TableView* owner): owner_(owner)
{
}

void TableView::Impl::Awake()
{
    auto d = Instantiate<SelectableItemDelegate>(owner_->shared_from_this());
    owner_->SetItemDelegate(d);

    auto hori = Instantiate<HeaderView>(owner_->shared_from_this());
    hori->SetOrientation(HeaderOrientation::Horizontal);
    owner_->SetHorizontalHeader(hori);
    //TODO 垂直表头
}

WeakHeaderView TableView::Impl::Header(HeaderOrientation orientation)
{
    return headers_[orientation];
}

void TableView::Impl::SetHeader(HeaderOrientation orientation, const SharedHeaderView& header)
{
    auto h = Header(orientation);
    if (!header || header == h)
        return;

    headers_[orientation] = header;
    header->SetWidgetParent(owner_->shared_from_this());
    if (!header->Model())
    {
        header->SetModel(owner_->Model());
        auto sm = owner_->SelectionModel();
        if (sm)
        {
            header->SetSelectionModel(sm);
        }
    }
}
}
