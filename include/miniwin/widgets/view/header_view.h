#pragma once
#include <miniwin/widgets/base/abstract_item_view.h>

namespace miniwin {
class HeaderView : public AbstractItemView
{
public:
    HeaderView(Widget* parent, HeaderOrientation orientation);
    ~HeaderView() override;

    HeaderOrientation Orientation() const;

    virtual void PaintSection(size_t section);

private:
    using AbstractItemView::SetDrawFlags;

    _MW_IMPL
};
}
