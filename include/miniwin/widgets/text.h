#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class Text : public AbstractControl
{
public:
    Text(Widget* parent, std::u8string_view label);

protected:
    void PaintBegin() override;
};
}
