#include <miniwin/widgets/view/list_view.h>

#include <miniwin/delegate/base/abstract_item_delegate.h>
#include <miniwin/core/imgui.h>
#include <miniwin/model/item_selection_model.h>
#include "miniwin/delegate/selectable_item_delegate.h"
#include "miniwin/tools/scope_variable.h"

namespace miniwin {
class ListView::Impl
{
public:
	Impl(ListView* owner) : owner_(owner) {}

	void Awake() {
		auto d = Create<SelectableItemDelegate>(owner_->shared_from_this());
		owner_->SetItemDelegate(d);
		auto s = Create<ItemSelectionModel>(owner_->shared_from_this());
		s->SetModel(owner_->Model());
		owner_->SetSelectionModel(s);
	}

	ListView* owner_;

	bool visible_ = false;
	imgui::ListClipper clipper_;
	ScopeVariable<Vector2D> position_sc_;
	ScopeVariable<Vector2D> size_sc_;
};

ListView::ListView() {
	impl_ = std::make_unique<Impl>(this);
}

ListView::~ListView() {}

String ListView::RightLabel() const {
	return Name();
}

void ListView::SetRightLabel(const String& label) {
	SetName(label);
}

Vector2D ListView::Position() const { return {}; }
void ListView::SetPosition(const Vector2D& pos) {}

Vector2D ListView::Size() const {
	//TODO ListView预测大小
	return impl_->size_sc_.cur_value();
}

void ListView::SetSize(const Vector2D& size) {
	impl_->size_sc_.SetControl(size);
}

void ListView::Awake() {
	AbstractItemView::Awake();
	impl_->Awake();
}

void ListView::PaintBegin(size_t index) {
	AbstractItemView::PaintBegin(index);
	auto m = Model();

	if ((impl_->visible_ = imgui::BeginListBox(RightLabel(), impl_->size_sc_.cur_value()))) {

		auto cur_size = imgui::GetItemRectSize();
		if (cur_size != impl_->size_sc_.cur_value()) {
			if (IsUpdated()) {
				OnSizeChanged(cur_size, impl_->size_sc_.cur_value());
			}
			impl_->size_sc_.SetValueDirectly(cur_size);
		}

		if (auto d = ItemDelegate()) {
			impl_->clipper_.Begin(m->RowCount());
			auto self = shared_from_this();

			while (impl_->clipper_.Step()) {
				for (size_t i = impl_->clipper_.display_start(); i < impl_->clipper_.display_end(); ++i) {
					d->Paint(self, i);
				}
			}
		}
	}
}

void ListView::PaintEnd(size_t index) {
	if (impl_->visible_) {
		imgui::EndListBox();
	}
	AbstractItemView::PaintEnd(index);

}
}
