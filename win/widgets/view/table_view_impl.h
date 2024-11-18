#pragma once
#include <miniwin/widgets/view/table_view.h>

namespace miniwin {
class TableView::Impl
{
public:
    explicit Impl(TableView* owner);

    void Init();

    SharedHeaderView Header(HeaderOrientation orientation);
    void SetHeader(HeaderOrientation orientation, const SharedHeaderView& header);

    TableView* owner_;
    std::unordered_map<HeaderOrientation, SharedHeaderView> headers_;
};
}
