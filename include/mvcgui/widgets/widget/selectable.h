#pragma once
#include <mvcgui/widgets/widget/base/abstract_control.h>

namespace mvcgui {
class Selectable : public AbstractMinimumControl
{
public:
    Selectable(Widget* const parent, std::u8string_view label, bool show = true);

    auto is_selected() const { return cur_selected_; }
    void set_selection(bool b) { cur_selected_ = b; }

    Signal<bool> on_selection_changed_;

protected:
    void OnItemShowablePaintBegin() override;
    void OnUpdate() override;

    bool cur_selected_;
    bool prev_selected_;
};
}