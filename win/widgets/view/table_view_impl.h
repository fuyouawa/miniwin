#pragma once
#include <miniwin/widgets/view/table_view.h>

#include "miniwin/tools/scope_variable.h"

namespace miniwin {
class TableView::Impl
{
public:
    explicit Impl(TableView* owner);

    void Awake();

    SharedHeaderView Header(HeaderOrientation orientation);
    void SetHeader(HeaderOrientation orientation, const SharedHeaderView& header);

    TableView* owner_;
    std::unordered_map<HeaderOrientation, SharedHeaderView> headers_;
    ScopeVariable<Vector2D> position_sc_;
    Vector2D size_to_set_;
    Vector2D really_size_;
};
}
