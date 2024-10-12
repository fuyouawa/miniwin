#pragma once
#include <fugui/widgets/widget/base/abstract_control.h>

namespace fugui {
class Text : public AbstractMinimumControl
{
public:
    Text(Widget* const parent, std::u8string_view label, bool show = true);

protected:
    void OnItemShowablePaintBegin() override;
};
}