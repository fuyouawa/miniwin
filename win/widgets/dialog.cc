#include <miniwin/widgets/dialog.h>
#include <miniwin/core/imgui.h>

#include "win/tools/debug.h"

namespace miniwin {
class Dialog::Impl {
public:
	Impl(Dialog* owner) : owner_(owner) {}

	void Init() {
		owner_->SetVisible(false);
		owner_->SetTitle("Dialog");
		owner_->SetId("Dialog");
	}

	Dialog* owner_;
	bool is_opened_ = true;
};

Dialog::Dialog(Widget* parent) : Window(parent) {
	impl_ = std::make_unique<Impl>(this);
	impl_->Init();
}

Dialog::~Dialog() = default;

void Dialog::Open() {
	Show();
}

void Dialog::OnPaintWindowBegin() {
	if (!imgui::IsPopupOpen(Title(), Flags())) {
		imgui::OpenPopup(Title(), Flags());
	}

	bool open = true;
	impl_->is_opened_ = imgui::BeginPopupModal(Title(), IsCloseButtonEnabled() ? &open : nullptr, Flags());

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
