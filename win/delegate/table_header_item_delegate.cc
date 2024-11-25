#include <miniwin/delegate/table_header_item_delegate.h>

#include <miniwin/widgets/base/abstract_item_view.h>
#include <miniwin/model/base/abstract_item_model.h>
#include <miniwin/core/imgui.h>

#include "win/tools/debug.h"

namespace miniwin {
class TableHeaderItemDelegate::Impl {
public:
	Impl(TableHeaderItemDelegate* owner) : owner_(owner) {}

	TableHeaderItemDelegate* owner_;
	HeaderOrientation orientation_;
};

TableHeaderItemDelegate::TableHeaderItemDelegate() {
	impl_ = std::make_unique<Impl>(this);
}
TableHeaderItemDelegate::~TableHeaderItemDelegate() = default;

HeaderOrientation TableHeaderItemDelegate::Orientation() const {
	return impl_->orientation_;
}

void TableHeaderItemDelegate::SetOrientation(HeaderOrientation orientation) {
	impl_->orientation_ = orientation;
}

void TableHeaderItemDelegate::PaintBegin(const SharedItemView& view, const ModelIndex& index) {
	AbstractItemDelegate::PaintBegin(view, index);

	auto model = view->Model();

	auto section = impl_->orientation_ == HeaderOrientation::kHorizontal
					? index.column()
					: index.row();
	auto text = model->HeaderData(section, impl_->orientation_).ToString();

	if (impl_->orientation_ == HeaderOrientation::kHorizontal) {
		imgui::TableHeader(text);
	}
	else {
		//TODO 表格行头部
	}
}
}
