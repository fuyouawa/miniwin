#pragma once
#include <miniwin/widgets/base/abstract_item_view.h>

namespace miniwin {
class ComboBoxView : public AbstractItemView
{
public:
    ComboBoxView(Widget* parent, std::u8string_view label);

    std::u8string_view label() const;
    void set_label(std::u8string_view label);

    ComboBoxFlags flags() const;
    void set_flags(ComboBoxFlags flags);

protected:
    void PaintBegin() override;

    _MW_IMPL
};
}