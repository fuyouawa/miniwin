#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class AbstractButton : public AbstractControl
{
public:
	AbstractButton(Widget* parent, std::u8string_view label);

    bool checked() const;
    
    MW_SIGNAL(OnClicked)
    MW_SIGNAL(OnToggled, (bool) checked)

protected:
    void PaintBegin() override;

	bool cur_checked_;
	bool prev_checked_;
};
}
