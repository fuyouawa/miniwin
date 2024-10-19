#include "win/widgets/header_view_impl.h"

#include <miniwin/core/imgui_helper.h>

namespace miniwin {
inline HeaderView::HeaderView(Widget* parent, Orientation orientation)
    : AbstractItemView(parent)
{
    impl_ = std::make_unique<Impl>(this, orientation);
}

Orientation HeaderView::orientation() const
{
    return impl_->orientation_;
}

void HeaderView::PaintSection(size_t section)
{
    auto model = Model();
    auto label = model->HeaderData(section, orientation()).ToString();
    if (orientation() == Orientation::Horizontal)
    {
        ImGuiHelper::TableHeader(label);
    }
    else
    {
        //TODO 垂直表头
    }
}
}
