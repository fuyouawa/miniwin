#include <miniwin/widgets/list_widget.h>

#include <miniwin/model/standard_item_model.h>
#include <miniwin/model/item_selection_model.h>

namespace miniwin {
class ListWidget::Impl {
public:
	Impl(ListWidget* owner) : owner_(owner) {}

	void Awake() {
		auto model = Create<StandardItemModel>(owner_->shared_from_this());
		model->SetColumnCount(1);
		owner_->SetModel(model);
	}

	ListWidget* owner_;
};

ListWidget::ListWidget() {
	impl_ = std::make_unique<Impl>(this);
}

ListWidget::~ListWidget() {}

size_t ListWidget::CurrentIndex() const {
	auto s = SelectionModel()->CurrentSelection();
	if (s.valid()) {
		return s.top_left().row();
	}
	return 0;
}

Variant ListWidget::CurrentData(ItemRole role) const {
	return Model()->Data(CurrentIndex(), role);
}

String ListWidget::CurrentText() const {
	return CurrentData(ItemRole::kDisplay).ToString();
}

void ListWidget::AddItem(const String& text, const Variant& user_data) {
	InsertItem(Model()->RowCount(), text, user_data);
}

void ListWidget::AddItems(const StringList& texts) {
	InsertItems(Model()->RowCount(), texts);
}

void ListWidget::InsertItem(size_t index, const String& text, const Variant& user_data) {
	auto m = Model();
	m->InsertRow(index);
	m->SetData(index, text, ItemRole::kDisplay);
	m->SetData(index, user_data, ItemRole::kUserData);
}

void ListWidget::InsertItems(size_t index, const StringList& texts) {
	auto m = Model();
	m->InsertRows(index, texts.size());
	int i = 0;
	for (auto t : texts) {
		m->SetData(index + i, t, ItemRole::kDisplay);
		++i;
	}
}

void ListWidget::Awake() {
	ListView::Awake();
	impl_->Awake();
}

void ListWidget::PaintBegin(size_t index) {
	ListView::PaintBegin(index);
}
}
