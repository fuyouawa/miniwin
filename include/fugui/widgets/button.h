#pragma once
#include <fugui/widgets/base/abstract_button.h>

namespace fugui {
class Button : public AbstractButton
{
public:
	Button(Widget* parent, std::u8string_view label, bool show = true);

protected:
	void PaintBegin() override;
};
}
