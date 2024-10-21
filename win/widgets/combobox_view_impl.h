#pragma once
#include <miniwin/widgets/combobox_view.h>
#include <string>

namespace miniwin {
class ComboBoxView::Impl {
public:
	Impl(ComboBoxView* owner);

	void Init();

	ComboBoxView* owner_;
	ComboBoxFlags flags_ = ComboBoxFlags::kNone;
};
}