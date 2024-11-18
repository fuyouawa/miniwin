#include <miniwin/delegate/base/abstract_item_delegate.h>

#include <miniwin/core/imgui.h>
#include <miniwin/core/widgetid_pool.h>

namespace miniwin {
class AbstractItemDelegate::Impl {
public:
	Impl() {
		id_ = WidgetIdPool::Instance().AllocId();
	}

	~Impl() {
		WidgetIdPool::Instance().RecycleId(id_);
		id_ = 0;
	}

	WidgetId id_;
};

AbstractItemDelegate::AbstractItemDelegate() {
	impl_ = std::make_unique<Impl>();
}

AbstractItemDelegate::~AbstractItemDelegate() {}

void AbstractItemDelegate::Initialize(const SharedObject& parent) {
	Object::Initialize(parent);
}

void AbstractItemDelegate::Paint(const SharedItemView& view, const ModelIndex& index) {
	PaintBegin(view, index);
	PaintEnd(view, index);
}

void AbstractItemDelegate::PaintBegin(const SharedItemView& view, const ModelIndex& index) {
	imgui::PushID(impl_->id_);
}

void AbstractItemDelegate::PaintEnd(const SharedItemView& view, const ModelIndex& index) {
	imgui::PopID();
}
}
