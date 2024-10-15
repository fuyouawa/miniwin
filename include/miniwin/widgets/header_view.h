#pragma once
#include <miniwin/widgets/base/abstract_item_view.h>

namespace miniwin {
class HeaderView : public AbstractItemView
{
public:
    HeaderView(Widget* parent);

    virtual void PaintSection(int index) = 0;
};
}
