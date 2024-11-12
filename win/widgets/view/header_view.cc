#include <miniwin/widgets/view/header_view.h>

#include <miniwin/core/imgui.h>

namespace miniwin {
class HeaderView::Impl {
public:
    Impl(HeaderView* owner, HeaderOrientation orientation) : owner_(owner), orientation_(orientation) {}

    HeaderView* owner_;
    HeaderOrientation orientation_;
};

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
        imgui::TableHeader(label);
    }
    else
    {
        //TODO 垂直表头
    }
}
}
