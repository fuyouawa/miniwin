#pragma once
#include <fugui/widgets/widget/base/abstract_control.h>
#include <fugui/model/base/abstract_list_model.h>

namespace fugui {
class ComboBox : public AbstractMinimumControl
{
public:
    ComboBox(Widget* const parent, std::u8string_view label, bool show = true);

    auto model() const { return model_; }
    void set_model(AbstractListModelPtr model) { model_ = model; }

    Signal<bool> on_combo_open_changed_;
    Signal<ModelIndex, ModelIndex> on_current_changed_;

protected:
    void OnItemShowablePaintBegin() override;
    void OnUpdate() override;

    bool is_combo_open_;
    AbstractListModelPtr model_;
    ModelIndex cur_idx_;
    ModelIndex prev_idx_;
};
}