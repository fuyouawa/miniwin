#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class Label : public AbstractControl
{
public:
    Label(Widget* parent, const String& text);

protected:
    void PaintBegin() override;
};
}
