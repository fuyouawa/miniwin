#include <miniwin/widgets/checkbox.h>

#include <miniwin/core/imgui.h>
#include <miniwin/tools/scope_variable.h>

#include "win/tools/debug.h"

namespace miniwin {
class CheckBox::Impl {
public:
	Impl(CheckBox* owner) : owner_(owner) {}

	void PaintBegin() {
		checked_sc_.Enter();

		bool c = checked_sc_.cur_value();
		imgui::CheckBox(owner_->Text(), &c);

		if (c != checked_sc_.cur_value() || checked_sc_.HasChange()) {
			checked_sc_.SetValueDirectly(c);
			owner_->OnToggled(c);
		}

		checked_sc_.Exit();
	}

	CheckBox* owner_;
	ScopeCondition checked_sc_{false};
};

CheckBox::CheckBox() {
	impl_ = std::make_unique<Impl>(this);
}

CheckBox::~CheckBox() {}

void CheckBox::SetChecked(bool b) {
	impl_->checked_sc_.SetControl(b);
}

void CheckBox::PaintBegin() {
	AbstractTextualControl::PaintBegin();
	impl_->PaintBegin();
}

void CheckBox::PaintEnd() {
	AbstractTextualControl::PaintEnd();
}

void CheckBox::SetSize(const Vector2D& size) {
	MW_ASSERT(false, "You cant set check box size!");
}
}
