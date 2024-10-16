#pragma once
#include <miniwin/widgets/table_view.h>
#include <string>

namespace miniwin {
class TableView::Impl
{
public:
    explicit Impl(TableView* owner);

    TableView* owner_;
    TableFlags flags_ = TableFlags::kNone;
    HeaderView* horizontal_header = nullptr;
    bool begin_table_ = false;
    std::u8string id_;
};
}
