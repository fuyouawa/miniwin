#include "combobox_view_impl.h"
#include <miniwin/core/imgui_helper.h>
#include <miniwin/model/item_selection_model.h>
#include <miniwin/delegate/base/abstract_item_delegate.h>

namespace miniwin {
ComboBoxView::ComboBoxView(Widget* parent, std::u8string_view label)
	: AbstractItemView(parent)
{
	impl_ = std::make_unique<Impl>(this);
	impl_->Init();
	set_name(label);
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
	auto s = SelectionModel()->current_selection();
	auto model = Model();
	auto text = model->Data(s.top_left()).ToString();
	if (ImGuiHelper::BeginCombo(label(), text, size(), flags()))
	{
		auto delegate = ItemDelegate();
		if (delegate)
		{
			for (size_t i = 0; i < model->RowCount(); ++i)
			{
				delegate->Paint(this, { i, 0 });
			}
		}
		ImGuiHelper::EndCombo();
	}
}
}
