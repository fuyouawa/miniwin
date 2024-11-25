#include <miniwin/widgets/selectable.h>

#include <miniwin/core/imgui.h>

#include "miniwin/tools/scope_variable.h"

namespace miniwin {
class Selectable::Impl {
public:
	Impl(Selectable* owner) : owner_(owner) {}

	Vector2D CalcSize() const {
		return imgui::CalcTextSize(owner_->Text());
	}

	Selectable* owner_;
	ScopeVariable<Vector2D> size_sc_;
	bool cur_selected_ = false;
	bool prev_selected_ = false;
};

Selectable::Selectable() {
	impl_ = std::make_unique<Impl>(this);
}

Selectable::~Selectable() {}

bool Selectable::IsSelected() const {
	return impl_->cur_selected_;
}

void Selectable::SetSelection(bool b) {
	impl_->cur_selected_ = b;
}

Vector2D Selectable::Size() const {
	return impl_->size_sc_.cur_value();
}

void Selectable::SetSize(const Vector2D& size) {
	impl_->size_sc_.SetControl(size);
}

String Selectable::Text() const {
	return Name();
}

void Selectable::SetText(const String& text, bool adjust_size) {
	SetName(text);
	if (adjust_size) {
		SetSize(impl_->CalcSize());
	}
}

void Selectable::Start() {
	AbstractControl::Start();
	impl_->size_sc_.SetValueDirectly(impl_->CalcSize());
}

void Selectable::PaintBegin(size_t index) {
	AbstractControl::PaintBegin(index);

	imgui::Selectable(Text(), &impl_->cur_selected_, 0, impl_->size_sc_.cur_value());
	if (impl_->cur_selected_ != impl_->prev_selected_) {
		OnSelectionChanged(impl_->cur_selected_);
	}
	impl_->prev_selected_ = impl_->cur_selected_;
}
}
