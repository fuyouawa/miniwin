#include "combobox_view.h"

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
	Vector2D calc_size_;
	ScopeVariable<Vector2D> position_sc_;
	ScopeVariable<Vector2D> size_sc_;
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

Vector2D ComboBoxView::Position() const {
	return impl_->position_sc_.cur_value();
}

void ComboBoxView::SetPosition(const Vector2D& pos) {
	impl_->position_sc_.SetControl(pos);
}

Vector2D ComboBoxView::Size() const {
	return impl_->size_sc_.cur_value();
}

void ComboBoxView::SetSize(const Vector2D& size) {
	Vector2D s = size;
	s.set_y(impl_->size_sc_.cur_value().y());
	impl_->size_sc_.SetControl(std::move(s));
}

void ComboBoxView::Awake() {
	AbstractItemView::Awake();
	impl_->Awake();
}

void ComboBoxView::PaintBegin(size_t index) {
	AbstractItemView::PaintBegin(index);
	impl_->position_sc_.Enter();

	if (impl_->position_sc_.HasChange()) {
		OnPositionChanged(impl_->position_sc_.cur_value(), impl_->position_sc_.prev_value());
		imgui::SetCursorPos(impl_->position_sc_.cur_value());
	}
	else {
		auto cur_pos = imgui::GetCursorPos();
		if (cur_pos != impl_->position_sc_.cur_value()) {
			OnPositionChanged(cur_pos, impl_->position_sc_.cur_value());
			impl_->position_sc_.SetValueDirectly(cur_pos);
		}
	}

	if (impl_->size_sc_.HasChange()) {
		OnSizeChanged(impl_->size_sc_.cur_value(), impl_->size_sc_.prev_value());
	}
	auto width = impl_->size_sc_.cur_value().x();
	if (!Mathf::Approximately(width, 0.f)) {
		imgui::PushItemWidth(width);
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

	//TODO Combo的Size
}

void ComboBoxView::PaintEnd(size_t index) {
	if (impl_->is_open_) {
		imgui::EndCombo();
	}
	impl_->position_sc_.Exit();

	AbstractItemView::PaintEnd(index);
}
}
