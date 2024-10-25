#include "headerview_impl.h"

#include <miniwin/core/imgui_helper.h>

namespace miniwin {
HeaderView::HeaderView(Widget* parent, HeaderOrientation orientation)
    : AbstractItemView(parent)
{
    impl_ = std::make_unique<Impl>(this, orientation);
}

HeaderView::~HeaderView()
{
}

HeaderOrientation HeaderView::Orientation() const
{
    return impl_->orientation_;
}

void HeaderView::PaintSection(size_t section)
{
    auto m = Model();
    auto label = m->HeaderData(section, Orientation()).ToString();
    if (Orientation() == HeaderOrientation::Horizontal)
    {
        ImGuiHelper::TableHeader(label);
    }
    else
    {
        //TODO 垂直表头
    }
}
}
