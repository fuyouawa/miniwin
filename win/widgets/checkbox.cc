#include <miniwin/widgets/checkbox.h>

#include <miniwin/core/imgui.h>
#include <miniwin/tools/scope_variable.h>

namespace miniwin {
class CheckBox::Impl {
public:
	Impl(CheckBox* owner) : owner_(owner) {}

	void PaintBegin() {
		checked_sc_.Enter();

		bool c = checked_sc_.cur_value();
		imgui::CheckBox(owner_->Text(), &c);

		if (c != checked_sc_.cur_value() || checked_sc_.HasChange())
		{
			checked_sc_.SetValueDirectly(c);
			owner_->OnToggled(c);
		}

		checked_sc_.Exit();
	}

	CheckBox* owner_;
	ScopeCondition checked_sc_{ false };
};

CheckBox::CheckBox(Widget* const parent, const String& label)
	: AbstractControl(parent, label)
{
	impl_ = std::make_unique<Impl>(this);
}

void CheckBox::SetChecked(bool b) {
	impl_->checked_sc_.SetControl(b);
}

void CheckBox::PaintBegin() {
	AbstractControl::PaintBegin();
	impl_->PaintBegin();
}

void CheckBox::PaintEnd() {
	AbstractControl::PaintEnd();
}
}
