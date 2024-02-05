#pragma once
#include <mvcgui/widgets/widget/base/abstract_control.h>

namespace mvcgui {
class Text : public AbstractMinimumControl
{
public:
    Text(Widget* const parent, std::u8string_view label, bool show = true);

protected:
    void OnItemShowablePaintBegin() override;
};
}