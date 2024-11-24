#include <miniwin/widgets/combobox.h>
#include <miniwin/core/imgui.h>

#include "combobox_view.h"
#include <miniwin/model/standard_item_model.h>
#include <miniwin/model/item_selection_model.h>

namespace miniwin {
class ComboBox::Impl
{
public:
	Impl(ComboBox* owner) : owner_(owner) {}

	void Awake() {
		view_ = Create<ComboBoxView>(owner_->shared_from_this());
		auto model = Create<StandardItemModel>(owner_->shared_from_this());
		model->SetColumnCount(1);
		view_->SetModel(model);
	}

	ComboBox* owner_;
	std::shared_ptr<ComboBoxView> view_ = nullptr;
};

ComboBox::ComboBox() {
	impl_ = std::make_unique<Impl>(this);
}

ComboBox::~ComboBox() {}

String ComboBox::Text() const {
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

Vector2D ComboBox::Size() const {
	return impl_->view_->Size();
}

void ComboBox::SetSize(const Vector2D& size) {
	impl_->view_->SetSize(size);
}

Vector2D ComboBox::Position() const {
	return impl_->view_->Position();
}

void ComboBox::SetPosition(const Vector2D& pos) {
	impl_->view_->SetPosition(pos);
}

void ComboBox::Awake() {
	Widget::Awake();
	impl_->Awake();
}
}
