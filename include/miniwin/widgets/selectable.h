#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class Selectable : public AbstractControl
{
public:
    Selectable(Widget* parent, const String& text);
    ~Selectable() override;

    bool IsSelected() const;
    void SetSelection(bool b);

    MW_SIGNAL(OnSelectionChanged, (bool) selected)

protected:
    void PaintBegin() override;

    _MW_IMPL
};
}
