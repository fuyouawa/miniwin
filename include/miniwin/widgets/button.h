#pragma once
#include <miniwin/widgets/base/abstract_button.h>

namespace miniwin {
class Button : public AbstractButton
{
public:
	Button(Widget* parent, std::u8string_view text);

protected:
	void PaintBegin() override;
};
}
