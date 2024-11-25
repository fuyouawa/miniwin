#include <miniwin/widgets/combobox.h>
#include <miniwin/core/imgui.h>

#include <miniwin/model/standard_item_model.h>
#include <miniwin/model/item_selection_model.h>

namespace miniwin {
class ComboBox::Impl
{
public:
	Impl(ComboBox* owner) : owner_(owner) {}

	void Awake() {
		auto model = Create<StandardItemModel>(owner_->shared_from_this());
		model->SetColumnCount(1);
		owner_->SetModel(model);
	}

	ComboBox* owner_;
};

ComboBox::ComboBox() {
	impl_ = std::make_unique<Impl>(this);
}

ComboBox::~ComboBox() {}

size_t ComboBox::CurrentIndex() const {
	auto s = SelectionModel()->CurrentSelection();
	if (s.valid()) {
		return s.top_left().row();
	}
	return 0;
}

Variant ComboBox::CurrentData(ItemRole role) const {
	return Model()->Data(CurrentIndex(), role);
}

String ComboBox::CurrentText() const {
	return CurrentData(ItemRole::kDisplay).ToString();
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
	m->SetData(index, text, ItemRole::kDisplay);
	m->SetData(index, user_data, ItemRole::kUserData);
}

void ComboBox::InsertItems(size_t index, const StringList& texts) {
	auto m = Model();
	m->InsertRows(index, texts.size());
	int i = 0;
	for (auto t : texts) {
		m->SetData(index + i, t, ItemRole::kDisplay);
		++i;
	}
}

void ComboBox::Awake() {
	ComboBoxView::Awake();
	impl_->Awake();
}
}
