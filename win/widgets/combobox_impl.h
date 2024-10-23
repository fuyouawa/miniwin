#pragma once
#include <miniwin/widgets/combobox.h>

namespace miniwin {
class ComboBoxView::Impl {
public:
	Impl(ComboBoxView* owner);

	void Init();

	ComboBoxView* owner_;
};

class ComboBox::Impl
{
public:
	Impl(ComboBox* owner);

	void Init(std::u8string_view label);

	ComboBox* owner_;
	ComboBoxView* view_ = nullptr;
};
}
