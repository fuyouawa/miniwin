#include <miniwin/widgets/dialog.h>
#include <miniwin/core/imgui_flags.h>

namespace miniwin {
class Dialog::Impl {
public:
	Impl(Dialog* owner) : owner_(owner) {}

	Dialog* owner_;
};

Dialog::Dialog(Widget* parent) : Window(parent) {
	impl_ = std::make_unique<Impl>(this);
	SetFlags(imgui::kWindowNoDocking);
}

Dialog::~Dialog() {}
}
