#include <miniwin/widgets/button.h>

#include <miniwin/core/imgui.h>
#include <miniwin/tools/scope_variable.h>

namespace miniwin {
class Button::Impl {
public:
	Impl(Button* owner) : owner_(owner) {}

	Vector2D CalcSize() const {
		return imgui::CalcTextSize(owner_->Text()) + imgui::style::FramePadding() * 2;
	}

	Button* owner_;
	ScopeVariable<Vector2D> size_sc_;
};

Button::Button() {
	impl_ = std::make_unique<Impl>(this);
}

Button::~Button() {}

String Button::Text() const {
	return Name();
}

void Button::SetText(const String& text, bool adjust_size) {
	SetName(text);
	if (adjust_size) {
		SetSize(impl_->CalcSize());
	}
}

Vector2D Button::Size() const {
	return impl_->size_sc_.cur_value();
}

void Button::SetSize(const Vector2D& size) {
	impl_->size_sc_.SetControl(size);
}

void Button::Start() {
	AbstractControl::Start();
	impl_->size_sc_.SetValueDirectly(impl_->CalcSize());
}

void Button::BeginUpdate(size_t index) {
	AbstractControl::BeginUpdate(index);
	impl_->size_sc_.Enter();

	if (impl_->size_sc_.HasChange()) {
		OnSizeChanged(impl_->size_sc_.cur_value(), impl_->size_sc_.prev_value());
	}

	if (imgui::Button(Text(), impl_->size_sc_.cur_value())) {
		OnClicked();
	}
}

void Button::EndUpdate(size_t index) {
	impl_->size_sc_.Exit();

	AbstractControl::EndUpdate(index);
}
}
