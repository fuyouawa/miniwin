#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class Label : public AbstractControl
{
public:
    Label(Widget* parent, std::u8string_view text);

protected:
    void PaintBegin() override;
};
}
