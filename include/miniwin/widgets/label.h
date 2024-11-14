#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class Label : public AbstractTextualControl
{
public:
    Label(Widget* parent, const String& text);

protected:
    void PaintBegin() override;

private:
    void SetSize(const Vector2D& size) override;
};
}
