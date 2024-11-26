#include <miniwin/widgets/view/list_view.h>

#include <miniwin/delegate/base/abstract_item_delegate.h>
#include <miniwin/core/imgui.h>
#include <miniwin/model/item_selection_model.h>
#include "miniwin/delegate/selectable_item_delegate.h"
#include "miniwin/tools/scope_variable.h"

namespace miniwin {
class ListView::Impl {
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
	Vector2D size_to_set_;
	Vector2D really_size_;
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

Vector2D ListView::Size() const {
	return impl_->really_size_ == Vector2D::kZero
		       ? impl_->size_to_set_
		       : impl_->really_size_;
}

void ListView::SetSize(const Vector2D& size) {
	impl_->size_to_set_ = size;
}

void ListView::Awake() {
	AbstractItemView::Awake();
	impl_->Awake();
}

void ListView::BeginUpdate(size_t index) {
	AbstractItemView::BeginUpdate(index);
	auto m = Model();

	if ((impl_->visible_ = imgui::BeginListBox(RightLabel(), impl_->size_to_set_))) {
		auto cur_size = imgui::GetItemRectSize();
		if (cur_size != impl_->really_size_) {
			if (IsUpdated()) {
				OnSizeChanged(cur_size, impl_->really_size_);
			}
			impl_->really_size_ = cur_size;
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

void ListView::EndUpdate(size_t index) {
	if (impl_->visible_) {
		imgui::EndListBox();
	}
	AbstractItemView::EndUpdate(index);
}
}
