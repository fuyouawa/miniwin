#include "win/widgets/table_view_impl.h"

namespace miniwin {
TableView::Impl::Impl(TableView* owner): owner_(owner)
{
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
    h->SetWidgetParent(owner_);
    if (!h->Model())
    {
        h->SetModel(owner_->Model());
        auto sm = owner_->SelectionModel();
        if (sm)
        {
            h->SetSelectionModel(sm);
        }
    }
}
}
