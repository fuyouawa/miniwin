#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class Selectable : public AbstractControl
{
public:
    Selectable(Widget* parent, std::u8string_view label);
    ~Selectable() override;

    bool is_selected() const;
    void set_selection(bool b);

    SelectableFlags flags() const;
    void set_flags(SelectableFlags flags);

    MW_SIGNAL(OnSelectionChanged, (bool) selected)

protected:
    void PaintBegin() override;

    _MW_IMPL
};
}
