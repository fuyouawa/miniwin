#pragma once
#include <miniwin/widgets/checkbox.h>

#include "miniwin/tools/scope_variable.h"

namespace miniwin {
class CheckBox::Impl {
public:
	Impl(CheckBox* owner);

	void PaintBegin();

	CheckBox* owner_;
	ScopeCondition checked_sc_{ false };
};
}
