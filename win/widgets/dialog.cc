#include <miniwin/widgets/dialog.h>
#include <miniwin/core/imgui.h>

#include "win/tools/debug.h"

namespace miniwin {
class Dialog::Impl {
public:
	Impl(Dialog* owner) : owner_(owner) {}

	Dialog* owner_;
	bool is_opened_ = true;
};

Dialog::Dialog() {
	impl_ = std::make_unique<Impl>(this);
}

Dialog::~Dialog() = default;

void Dialog::OnPaintWindowBegin() {
	if (!imgui::IsPopupOpen(Title(), Id(), Flags())) {
		imgui::OpenPopup(Title(), Id(), Flags());
	}

	bool open = true;
	impl_->is_opened_ = imgui::BeginPopupModal(Title(), Id(), IsCloseButtonEnabled() ? &open : nullptr, Flags());

	if (!open) {
		imgui::CloseCurrentPopup();
		Hide();
	}
}

void Dialog::OnPaintWindowEnd() {
	if (impl_->is_opened_) {
		imgui::EndPopup();
	}
}
}
