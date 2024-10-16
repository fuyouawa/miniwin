#pragma once
#include <miniwin/widgets/base/abstract_item_view.h>

namespace miniwin {
class HeaderView : public AbstractItemView
{
public:
    HeaderView(Widget* parent, Orientation orientation);

    Orientation orientation();

    virtual void PaintSection(size_t index);

private:
    using AbstractItemView::set_draw_flags;

    _MW_IMPL
};
}
