#include <miniwin/widgets/view/header_view.h>

#include <miniwin/core/imgui.h>

namespace miniwin {
class HeaderView::Impl {
public:
	Impl(HeaderView* owner) : owner_(owner) {}

	HeaderView* owner_;
	HeaderOrientation orientation_ = HeaderOrientation::Horizontal;
};

HeaderView::HeaderView() {
	impl_ = std::make_unique<Impl>(this);
}

HeaderView::~HeaderView() {}

HeaderOrientation HeaderView::Orientation() const {
	return impl_->orientation_;
}

void HeaderView::SetOrientation(HeaderOrientation orientation) {
	impl_->orientation_ = orientation;
}

void HeaderView::PaintSection(size_t section) {
	auto m = Model();
	auto label = m->HeaderData(section, Orientation()).ToString();
	if (Orientation() == HeaderOrientation::Horizontal) {
		imgui::TableHeader(label);
	}
	else {
		//TODO 垂直表头
	}
}
}
