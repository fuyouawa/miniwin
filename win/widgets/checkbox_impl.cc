#include "checkbox_impl.h"

#include <miniwin/core/imgui_helper.h>

namespace miniwin {
CheckBox::Impl::Impl(CheckBox* owner)
	: owner_(owner)
{
}

void CheckBox::Impl::PaintBegin()
{
	checked_sc_.Enter();

	bool c = *checked_sc_;
	ImGuiHelper::CheckBox(owner_->Text(), &c);

	if (c != *checked_sc_ || checked_sc_.HasChange())
	{
		checked_sc_.SetValueDirectly(c);
		owner_->OnToggled(c);
	}

	checked_sc_.Exit();
}
}
