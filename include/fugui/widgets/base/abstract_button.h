#pragma once
#include <fugui/widgets/base/abstract_control.h>

namespace fugui {
class AbstractButton : public AbstractControl
{
    MW_OBJECT(AbstractButton)
public:
	AbstractButton(Widget* const parent, std::u8string_view label, bool show);

    bool checked() const;
    
    MW_SIGNAL(OnClicked)
    MW_SIGNAL(OnToggled, (bool) checked)

protected:
    void PaintBegin() override;

	bool cur_checked_;
	bool prev_checked_;
};
}
