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

	void Init();

	ComboBox* owner_;
	std::shared_ptr<ComboBoxView> view_ = nullptr;
};
}
