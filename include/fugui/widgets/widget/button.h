#pragma once
#include <fugui/widgets/widget/base/abstract_button.h>

namespace fugui {
class Button : public AbstractButton
{
public:
	Button(Widget* const parent, std::u8string_view label, bool show = true);

protected:
	void OnItemShowablePaintBegin() override;
};
}