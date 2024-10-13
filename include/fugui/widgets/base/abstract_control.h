#pragma once
#include <fugui/core/widget.h>

namespace fugui {
class AbstractControl : public Widget
{
public:
	AbstractControl(Widget* const parent, std::u8string_view label, bool show);
	
    std::u8string_view label() const;
    void set_label(std::u8string_view label);

    bool visible() const override;
};
}
