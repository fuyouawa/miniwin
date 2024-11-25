#include <miniwin/widgets/view/combobox_view.h>

#include <miniwin/core/imgui.h>
#include <miniwin/delegate/selectable_item_delegate.h>
#include <miniwin/model/item_selection_model.h>
#include <miniwin/tools/scope_variable.h>

#include "miniwin/tools/mathf.h"

namespace miniwin {
class ComboBoxView::Impl {
public:
	Impl(ComboBoxView* owner) : owner_(owner) {}

	void Awake() {
		auto d = Create<SelectableItemDelegate>(owner_->shared_from_this());
		owner_->SetItemDelegate(d);
		auto s = Create<ItemSelectionModel>(owner_->shared_from_this());
		s->SetModel(owner_->Model());
		owner_->SetSelectionModel(s);
	}

	Vector2D CalcSize() const {
		auto m = owner_->Model();
		auto cs = owner_->SelectionModel()->CurrentSelection();
		String data;
		if (m->RowCount() > 0) {
			if (cs.valid()) {
				data = m->Data(cs.top_left().row()).ToString();
			}
			else {
				data = m->Data(0).ToString();
			}
		}
		return imgui::CalcTextSize(data) + imgui::style::FramePadding() * 2;
	}

	ComboBoxView* owner_;
	bool is_open_ = false;
	Vector2D really_size_;
	float width_to_set_ = 0;
};

ComboBoxView::ComboBoxView() {
	impl_ = std::make_unique<Impl>(this);
}

ComboBoxView::~ComboBoxView() = default;

String ComboBoxView::Text() const {
	return Name();
}

void ComboBoxView::SetText(const String& text) {
	SetName(text);
}

Vector2D ComboBoxView::Size() const {
	return impl_->really_size_ == Vector2D::kZero
		       ? Vector2D(impl_->width_to_set_, imgui::GetFrameHeight())
		       : impl_->really_size_;
}

void ComboBoxView::SetSize(const Vector2D& size) {
	impl_->width_to_set_ = size.x();
}

void ComboBoxView::Awake() {
	AbstractItemView::Awake();
	impl_->Awake();
}

void ComboBoxView::PaintBegin(size_t index) {
	AbstractItemView::PaintBegin(index);

	if (!Mathf::Approximately(impl_->width_to_set_, 0.f)) {
		imgui::PushItemWidth(impl_->width_to_set_);
	}

	auto cs = SelectionModel()->CurrentSelection();
	auto m = Model();
	auto text = m->Data(cs.top_left()).ToString();
	if ((impl_->is_open_ = imgui::BeginCombo(Text(), text, Flags()))) {
		if (auto d = ItemDelegate()) {
			auto self = shared_from_this();
			for (size_t i = 0; i < m->RowCount(); ++i) {
				d->Paint(self, {i, 0});
			}
		}
	}

	auto really_size = imgui::GetItemRectSize();
	if (really_size != impl_->really_size_) {
		if (IsUpdated()) {
			OnSizeChanged(really_size, impl_->really_size_);
		}
		impl_->really_size_ = really_size;
	}
}

void ComboBoxView::PaintEnd(size_t index) {
	if (impl_->is_open_) {
		imgui::EndCombo();
	}

	AbstractItemView::PaintEnd(index);
}
}
