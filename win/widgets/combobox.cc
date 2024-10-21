#include "combobox_impl.h"
#include <miniwin/core/imgui_helper.h>

namespace miniwin {
ComboBoxView::ComboBoxView(Widget* parent, std::u8string_view label)
	: AbstractItemView(parent)
{
	impl_ = std::make_unique<Impl>(this);
	impl_->Init();
	set_label(label);
}

ComboBoxView::~ComboBoxView()
{
}

std::u8string_view ComboBoxView::label() const
{
	return name();
}

void ComboBoxView::set_label(std::u8string_view label)
{
	set_name(label);
}

ComboBoxFlags ComboBoxView::flags() const
{
	return impl_->flags_;
}

void ComboBoxView::set_flags(ComboBoxFlags flags)
{
	impl_->flags_ = flags;
}

void ComboBoxView::PaintBegin()
{
	AbstractItemView::PaintBegin();
	auto cs = SelectionModel()->current_selection();
	auto m = Model();
	auto text = m->Data(cs.top_left()).ToString();
	if (ImGuiHelper::BeginCombo(label(), text, size(), flags()))
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

ComboBox::ComboBox(Widget* parent, std::u8string_view label)
	: Widget(parent, u8"ComboBox", WidgetType::kView)
{
	impl_ = std::make_unique<Impl>(this);
	impl_->Init(label);
}

ComboBox::~ComboBox()
{
}

ComboBoxFlags ComboBox::flags() const
{
	return impl_->view_->flags();
}

void ComboBox::set_flags(ComboBoxFlags flags) const
{
	impl_->view_->set_flags(flags);
}

std::u8string_view ComboBox::label() const
{
	return impl_->view_->label();
}

void ComboBox::set_label(std::u8string_view label)
{
	impl_->view_->set_label(label);
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
	auto s = impl_->view_->SelectionModel()->current_selection();
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
	return CurrentData(ItemRole::Display).ToString();
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
