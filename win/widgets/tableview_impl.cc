#include "tableview_impl.h"

#include <miniwin/delegate/selectable_item_delegate.h>

namespace miniwin {
TableView::Impl::Impl(TableView* owner): owner_(owner)
{
}

void TableView::Impl::Init()
{
    auto d = new SelectableItemDelegate(owner_);
    owner_->SetItemDelegate(d);

    auto hori = new HeaderView(owner_, Orientation::Horizontal);
    owner_->SetHorizontalHeader(hori);
    //TODO 垂直表头
}

HeaderView* TableView::Impl::Header(Orientation orientation)
{
    return headers_[orientation];
}

void TableView::Impl::SetHeader(Orientation orientation, HeaderView* header)
{
    auto h = Header(orientation);
    if (!header || header == h)
        return;
    if (h && h->WidgetParent() == owner_)
        delete h;

    headers_[orientation] = header;
    header->SetWidgetParent(owner_);
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
