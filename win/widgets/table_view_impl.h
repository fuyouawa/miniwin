#pragma once
#include <miniwin/widgets/table_view.h>
#include <string>

namespace miniwin {
class TableView::Impl
{
public:
    Impl(TableView* owner)
        : owner_(owner)
    {
    }

    TableView* owner_;
    HeaderView* horizontal_header;
    bool begin_table_;
    std::u8string id_;
};
}
