#pragma once
#include <miniwin/widgets/tableview.h>
#include <string>

namespace miniwin {
class TableView::Impl
{
public:
    explicit Impl(TableView* owner);

    void Init();

    HeaderView* Header(Orientation orientation);
    void SetHeader(Orientation orientation, HeaderView* header);

    TableView* owner_;
    TableFlags flags_ = TableFlags::kNone;
    std::unordered_map<Orientation, HeaderView*> headers_;
    std::u8string id_;
};
}
