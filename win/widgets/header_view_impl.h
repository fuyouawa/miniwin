#pragma once
#include <miniwin/widgets/header_view.h>

namespace miniwin {
class HeaderView::Impl {
public:
    Impl(HeaderView* owner, Orientation orientation);

    HeaderView* owner_;
    Orientation orientation_;
};
}
