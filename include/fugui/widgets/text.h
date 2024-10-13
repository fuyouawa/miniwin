#pragma once
#include <fugui/widgets/base/abstract_control.h>

namespace fugui {
class Text : public AbstractControl
{
public:
    Text(Widget* parent, std::u8string_view label, bool show = true);

protected:
    void PaintBegin() override;
};
}
