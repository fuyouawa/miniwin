#include <miniwin/widgets/combobox.h>

#include <miniwin/core/imgui.h>

#include <miniwin/delegate/selectable_item_delegate.h>
#include <miniwin/model/standard_item_model.h>
#include <miniwin/model/item_selection_model.h>

namespace miniwin {
class ComboBoxView::Impl {
public:
	Impl(ComboBoxView* owner) : owner_(owner) {}

	void Awake() {
		auto d = Instantiate<SelectableItemDelegate>(owner_->shared_from_this());
		owner_->SetItemDelegate(d);
	}

	ComboBoxView* owner_;
	bool begin_ = false;
	Vector2D calc_size_;
};

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

Vector2D ComboBoxView::CalcSize() const {
	if (impl_->calc_size_ == Vector2D::kZero) {
		auto m = Model();
		auto cs = SelectionModel()->CurrentSelection();
		String data;
		if (cs.valid()) {
			data = m->Data(cs.top_left().row()).ToString();
		}
		else {
			data = m->Data(0).ToString();
		}
		return imgui::CalcTextSize(data) + imgui::style::FramePadding() * 2;
	}
	return impl_->calc_size_;
}

void ComboBoxView::Awake() {
	AbstractItemView::Awake();
	impl_->Awake();
}

void ComboBoxView::PaintBegin(size_t index) {
	AbstractItemView::PaintBegin(index);
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
	impl_->calc_size_ = imgui::GetItemRectSize();
}

class ComboBox::Impl
{
public:
	Impl(ComboBox* owner) : owner_(owner) {}

	void Awake() {
		view_ = Instantiate<ComboBoxView>(owner_->shared_from_this());
		auto model = Instantiate<StandardItemModel>(owner_->shared_from_this());
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

Vector2D ComboBox::CalcSize() const {
	return impl_->view_->CalcSize();
}

Vector2D ComboBox::Size() const {
	return impl_->view_->Size();
}

void ComboBox::SetSize(const Vector2D& size) {
	impl_->view_->SetSize(size);
}

void ComboBox::Awake() {
	Widget::Awake();
	impl_->Awake();
}
}
