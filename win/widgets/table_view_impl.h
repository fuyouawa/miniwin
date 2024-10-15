#pragma once
#include <miniwin/widgets/table_view.h>

namespace miniwin {
class TableView::Impl
{
public:
    Impl(TableView* owner)
        : owner_(owner)
    {
    }

    TableView* owner_;
};
}
