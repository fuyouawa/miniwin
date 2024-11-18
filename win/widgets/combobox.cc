#include "combobox_impl.h"

#include <miniwin/core/imgui.h>

namespace miniwin {
ComboBoxView::ComboBoxView() {
	impl_ = std::make_unique<Impl>(this);
}

ComboBoxView::~ComboBoxView() {}

String ComboBoxView::Text() const {
	return Name();
}

void ComboBoxView::SetText(const String& text) {
	SetName(text);
}

void ComboBoxView::Initialize(const SharedObject& parent) {
	AbstractItemView::Initialize(parent);
	impl_->Init();
}

void ComboBoxView::PaintBegin() {
	AbstractItemView::PaintBegin();
	auto cs = SelectionModel()->CurrentSelection();
	auto m = Model();
	auto text = m->Data(cs.top_left()).ToString();
	if (imgui::BeginCombo(Text(), text, Flags(), Size())) {
		if (auto d = ItemDelegate()) {
			auto self = shared_from_this();
			for (size_t i = 0; i < m->RowCount(); ++i) {
				d->Paint(self, {i, 0});
			}
		}
		imgui::EndCombo();
	}
}

ComboBox::ComboBox() {
	impl_ = std::make_unique<Impl>(this);
}

ComboBox::~ComboBox() {}

const String& ComboBox::Text() const {
	return impl_->view_->Text();
}

void ComboBox::SetText(const String& text) {
	impl_->view_->SetText(text);
}

void ComboBox::SetItemDelegate(const SharedItemDelegate& delegate) {
	impl_->view_->SetItemDelegate(delegate);
}

const SharedItemDelegate& ComboBox::ItemDelegate() const {
	return impl_->view_->ItemDelegate();
}

void ComboBox::SetModel(const SharedItemModel& model) {
	impl_->view_->SetModel(model);
}

const SharedItemModel& ComboBox::Model() const {
	return impl_->view_->Model();
}

size_t ComboBox::CurrentIndex() const {
	auto s = impl_->view_->SelectionModel()->CurrentSelection();
	if (s.valid()) {
		return s.top_left().row();
	}
	return 0;
}

Variant ComboBox::CurrentData(ItemRole role) const {
	return Model()->Data(CurrentIndex(), role);
}

String ComboBox::CurrentText() const {
	return CurrentData(ItemRole::Display).ToString();
}

void ComboBox::AddItem(const String& text, const Variant& user_data) {
	InsertItem(Model()->RowCount(), text, user_data);
}

void ComboBox::AddItems(const StringList& texts) {
	InsertItems(Model()->RowCount(), texts);
}

void ComboBox::InsertItem(size_t index, const String& text, const Variant& user_data) {
	auto m = Model();
	m->InsertRow(index);
	m->SetData(index, text, ItemRole::Display);
	m->SetData(index, user_data, ItemRole::UserData);
}

void ComboBox::InsertItems(size_t index, const StringList& texts) {
	auto m = Model();
	m->InsertRows(index, texts.size());
	int i = 0;
	for (auto t : texts) {
		m->SetData(index + i, t, ItemRole::Display);
		++i;
	}
}

void ComboBox::Initialize(const SharedObject& parent) {
	Widget::Initialize(parent);
	impl_->Init();
}
}
