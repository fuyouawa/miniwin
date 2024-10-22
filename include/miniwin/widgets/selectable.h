#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class Selectable : public AbstractControl
{
public:
    Selectable(Widget* parent, std::u8string_view text);
    ~Selectable() override;

    bool IsSelected() const;
    void SetSelection(bool b);

    SelectableFlags Flags() const;
    void SetFlags(SelectableFlags flags);

    MW_SIGNAL(OnSelectionChanged, (bool) selected)

protected:
    void PaintBegin() override;

    _MW_IMPL
};
}
