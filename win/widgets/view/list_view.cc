#include "list_view_impl.h"

#include <miniwin/delegate/base/abstract_item_delegate.h>

namespace miniwin {
ListView::ListView() {
	impl_ = std::make_unique<Impl>(this);
}

ListView::~ListView() {}

String ListView::Title() const {
	return Name();
}

void ListView::SetTitle(const String& title) {
	SetName(title);
}

void ListView::Awake() {
	AbstractItemView::Awake();
	impl_->Awake();
}

void ListView::PaintBegin() {
	AbstractItemView::PaintBegin();
	auto m = Model();
	if (imgui::BeginListBox(Title(), Size())) {
		if (auto d = ItemDelegate()) {
			impl_->clipper_.Begin(m->RowCount());
			auto self = shared_from_this();

			while (impl_->clipper_.Step()) {
				for (size_t i = impl_->clipper_.display_start(); i < impl_->clipper_.display_end(); ++i) {
					d->Paint(self, i);
				}
			}
		}
		imgui::EndListBox();
	}
}
}
