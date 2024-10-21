#pragma once
#include <miniwin/widgets/combobox.h>

#include "miniwin/widgets/combobox_view.h"

namespace miniwin {
class ComboBox::Impl
{
public:
	Impl(ComboBox* owner);

	void Init(std::u8string_view label);

	ComboBox* owner_;
	ComboBoxView* view_ = nullptr;
};
}
