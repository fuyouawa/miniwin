#include "listview_impl.h"

#include <miniwin/delegate/base/abstract_item_delegate.h>

namespace miniwin {
ListView::ListView(Widget* parent, const String& label)
	: AbstractItemView(parent)
{
	impl_ = std::make_unique<Impl>(this);
	impl_->Init();
	SetText(label);
}

ListView::~ListView()
{
}

const String& ListView::Text() const
{
	return Name();
}

void ListView::SetText(const String& label)
{
	SetName(label);
}

void ListView::PaintBegin()
{
	AbstractItemView::PaintBegin();
	auto m = Model();
	if (imgui::BeginListBox(Text(), Size()))
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
		imgui::EndListBox();
	}
}
}
