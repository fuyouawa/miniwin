#pragma once
#include <miniwin/widgets/view/headerview.h>

namespace miniwin {
class HeaderView::Impl {
public:
    Impl(HeaderView* owner, HeaderOrientation orientation);

    HeaderView* owner_;
    HeaderOrientation orientation_;
};
}
