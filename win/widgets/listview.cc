#include "listview_impl.h"
#include "miniwin/delegate/base/abstract_item_delegate.h"

namespace miniwin {
ListView::ListView(Widget* parent, std::u8string_view label)
	: AbstractItemView(parent)
{
	impl_ = std::make_unique<Impl>(this);
	impl_->Init();
	set_label(label);
}

ListView::~ListView()
{
}

std::u8string_view ListView::label() const
{
	return name();
}

void ListView::set_label(std::u8string_view label)
{
	set_name(label);
}

void ListView::PaintBegin()
{
	AbstractItemView::PaintBegin();
	auto m = Model();
	if (ImGuiHelper::BeginListBox(label(), size()))
	{
		if (auto d = ItemDelegate())
		{
			impl_->clipper_.Begin(m->RowCount());
			while (impl_->clipper_.Step())
			{
				for (size_t i = impl_->clipper_.display_start(); i < impl_->clipper_.display_end(); ++i)
				{
					d->Paint(this, i);
				}
			}
		}
		ImGuiHelper::EndListBox();
	}
}
}
