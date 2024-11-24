#include <miniwin/widgets/list_widget.h>

#include <miniwin/widgets/view/list_view.h>
#include <miniwin/model/standard_item_model.h>
#include <miniwin/model/item_selection_model.h>

namespace miniwin {
class ListWidget::Impl {
public:
	Impl(ListWidget* owner) : owner_(owner) {}

	void Awake() {
		view_ = Create<ListView>(owner_->shared_from_this());
		auto model = Create<StandardItemModel>(owner_->shared_from_this());
		model->SetColumnCount(1);
		view_->SetModel(model);
	}

	ListWidget* owner_;
	std::shared_ptr<ListView> view_;
};

ListWidget::ListWidget() {
	impl_ = std::make_unique<Impl>(this);
}

ListWidget::~ListWidget() {}

void ListWidget::SetItemDelegate(const SharedItemDelegate& delegate) {
	impl_->view_->SetItemDelegate(delegate);
}

const SharedItemDelegate& ListWidget::ItemDelegate() const {
	return impl_->view_->ItemDelegate();
}

void ListWidget::SetModel(const SharedItemModel& model) {
	impl_->view_->SetModel(model);
}

const SharedItemModel& ListWidget::Model() const {
	return impl_->view_->Model();
}

size_t ListWidget::CurrentIndex() const {
	auto s = impl_->view_->SelectionModel()->CurrentSelection();
	if (s.valid()) {
		return s.top_left().row();
	}
	return 0;
}

Variant ListWidget::CurrentData(ItemRole role) const {
	return Model()->Data(CurrentIndex(), role);
}

String ListWidget::CurrentText() const {
	return CurrentData(ItemRole::Display).ToString();
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
	m->SetData(index, text, ItemRole::Display);
	m->SetData(index, user_data, ItemRole::UserData);
}

void ListWidget::InsertItems(size_t index, const StringList& texts) {
	auto m = Model();
	m->InsertRows(index, texts.size());
	int i = 0;
	for (auto t : texts) {
		m->SetData(index + i, t, ItemRole::Display);
		++i;
	}
}

String ListWidget::RightLabel() const {
	return impl_->view_->RightLabel();
}

void ListWidget::SetRightLabel(const String& label) {
	impl_->view_->SetRightLabel(label);
}

Vector2D ListWidget::Size() const {
	return impl_->view_->Size();
}

void ListWidget::SetSize(const Vector2D& size) {
	impl_->view_->SetSize(size);
}

Vector2D ListWidget::Position() const {
	return impl_->view_->Position();
}
void ListWidget::SetPosition(const Vector2D& pos) {
	impl_->view_->SetPosition(pos);
}


void ListWidget::Awake() {
	Widget::Awake();
	impl_->Awake();
}
}
