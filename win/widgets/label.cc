#include <miniwin/widgets/label.h>

#include <miniwin/core/imgui.h>

#include "miniwin/tools/scope_variable.h"
#include "win/tools/debug.h"

namespace miniwin {
class Label::Impl {
public:
	Impl(Label* owner) : owner_(owner) {}

	Vector2D CalcSize() const {
		return imgui::CalcTextSize(owner_->Text());
	}

	Label* owner_;
	ScopeVariable<Vector2D> size_sc_;
};

Label::Label() {
	impl_ = std::make_unique<Impl>(this);
}

Label::~Label() {}

String Label::Text() const {
	return Name();
}

void Label::SetText(const String& text, bool adjust_size) {
	SetName(text);
	if (adjust_size) {
		SetSize(impl_->CalcSize());
	}
}

Vector2D Label::Size() const {
	return impl_->size_sc_.cur_value();
}

void Label::SetSize(const Vector2D& size) {
	//TODO Label::SetSize
}

void Label::Start() {
	AbstractControl::Start();
	impl_->size_sc_.SetValueDirectly(impl_->CalcSize());
}

void Label::PaintBegin(size_t index) {
	AbstractControl::PaintBegin(index);

	imgui::Text(Text());
}
}
