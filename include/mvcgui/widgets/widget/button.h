#pragma once
#include <mvcgui/widgets/widget/base/abstract_button.h>

namespace mvcgui {
class Button : public AbstractButton
{
public:
	Button(Widget* const parent, std::u8string_view label, bool show = true);

protected:
	void OnItemShowablePaintBegin() override;
};
}