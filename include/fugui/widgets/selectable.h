#pragma once
#include <fugui/widgets/base/abstract_control.h>

namespace fugui {
class Selectable : public AbstractControl
{
public:
    Selectable(Widget* parent, std::u8string_view label, bool show = true);

    bool is_selected() const;
    void set_selection(bool b);

    MW_SIGNAL(OnSelectionChanged, (bool) selected)

protected:
    void PaintBegin() override;

    bool cur_selected_;
    bool prev_selected_;
};
}
