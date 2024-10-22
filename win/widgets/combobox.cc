#include "combobox_impl.h"
#include <miniwin/core/imgui_helper.h>

namespace miniwin {
ComboBoxView::ComboBoxView(Widget* parent, std::u8string_view text)
	: AbstractItemView(parent)
{
	impl_ = std::make_unique<Impl>(this);
	impl_->Init();
	SetText(text);
}

ComboBoxView::~ComboBoxView()
{
}

std::u8string_view ComboBoxView::Text() const
{
	return Name();
}

void ComboBoxView::SetText(std::u8string_view text)
{
	SetName(text);
}

ComboBoxFlags ComboBoxView::Flags() const
{
	return impl_->flags_;
}

void ComboBoxView::SetFlags(ComboBoxFlags flags)
{
	impl_->flags_ = flags;
}

void ComboBoxView::PaintBegin()
{
	AbstractItemView::PaintBegin();
	auto cs = SelectionModel()->CurrentSelection();
	auto m = Model();
	auto text = m->Data(cs.top_left()).ToUtf8String();
	if (ImGuiHelper::BeginCombo(Text(), text, Size(), Flags()))
	{
		if (auto d = ItemDelegate())
		{
			for (size_t i = 0; i < m->RowCount(); ++i)
			{
				d->Paint(this, { i, 0 });
			}
		}
		ImGuiHelper::EndCombo();
	}
}

ComboBox::ComboBox(Widget* parent, std::u8string_view text)
	: Widget(parent, u8"ComboBox")
{
	impl_ = std::make_unique<Impl>(this);
	impl_->Init(text);
}

ComboBox::~ComboBox()
{
}

ComboBoxFlags ComboBox::Flags() const
{
	return impl_->view_->Flags();
}

void ComboBox::SetFlags(ComboBoxFlags flags) const
{
	impl_->view_->SetFlags(flags);
}

std::u8string_view ComboBox::Text() const
{
	return impl_->view_->Text();
}

void ComboBox::SetText(std::u8string_view text)
{
	impl_->view_->SetText(text);
}

void ComboBox::SetItemDelegate(AbstractItemDelegate* delegate)
{
	impl_->view_->SetItemDelegate(delegate);
}

AbstractItemDelegate* ComboBox::ItemDelegate() const
{
	return impl_->view_->ItemDelegate();
}

void ComboBox::SetModel(AbstractItemModel* model)
{
	impl_->view_->SetModel(model);
}

AbstractItemModel* ComboBox::Model() const
{
	return impl_->view_->Model();
}

size_t ComboBox::CurrentIndex() const
{
	auto s = impl_->view_->SelectionModel()->CurrentSelection();
	if (s.valid())
	{
		return s.top_left().row();
	}
	return 0;
}

Variant ComboBox::CurrentData(ItemRole role) const
{
	return Model()->Data(CurrentIndex(), role);
}

std::u8string ComboBox::CurrentText() const
{
	return CurrentData(ItemRole::Display).ToUtf8String();
}

void ComboBox::AddItem(std::u8string_view text, const Variant& user_data)
{
	InsertItem(Model()->RowCount(), text, user_data);
}

void ComboBox::AddItems(std::initializer_list<std::u8string_view> texts)
{
	InsertItems(Model()->RowCount(), texts);
}

void ComboBox::InsertItem(size_t index, std::u8string_view text, const Variant& user_data)
{
	auto m = Model();
	m->InsertRow(index);
	m->SetData(index, text, ItemRole::Display);
	m->SetData(index, user_data, ItemRole::UserData);
}

void ComboBox::InsertItems(size_t index, std::initializer_list<std::u8string_view> texts)
{
	auto m = Model();
	m->InsertRows(index, texts.size());
	int i = 0;
	for (auto t : texts)
	{
		m->SetData(index + i, t, ItemRole::Display);
		++i;
	}
}
}
