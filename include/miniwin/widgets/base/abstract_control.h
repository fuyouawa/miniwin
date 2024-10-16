#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class AbstractControl : public Widget
{
public:
	AbstractControl(Widget* parent, std::u8string_view label);
	
    std::u8string_view label() const;
    void set_label(std::u8string_view label);

    bool Visible() const override;
};
}
