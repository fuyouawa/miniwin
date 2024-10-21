#pragma once
#include <miniwin/widgets/view/tableview.h>
#include <string>

namespace miniwin {
class TableView::Impl
{
public:
    explicit Impl(TableView* owner);

    void Init();

    HeaderView* Header(HeaderOrientation orientation);
    void SetHeader(HeaderOrientation orientation, HeaderView* header);

    TableView* owner_;
    TableFlags flags_ = TableFlags::kNone;
    TableRowFlags row_flags_ = TableRowFlags::kNone;
    TableColumnFlags column_flags_ = TableColumnFlags::kNone;
    std::unordered_map<HeaderOrientation, HeaderView*> headers_;
    std::u8string id_;
};
}
