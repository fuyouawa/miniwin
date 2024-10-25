#pragma once
#include <miniwin/widgets/view/tableview.h>

namespace miniwin {
class TableView::Impl
{
public:
    explicit Impl(TableView* owner);

    void Init();

    HeaderView* Header(HeaderOrientation orientation);
    void SetHeader(HeaderOrientation orientation, HeaderView* header);

    TableView* owner_;
    std::unordered_map<HeaderOrientation, HeaderView*> headers_;
};
}
