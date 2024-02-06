#pragma once
#include <mvcgui/widgets/widget/base/abstract_control.h>
#include <mvcgui/model/base/model_index.h>

namespace mvcgui {
class AbstractItemModel;
using AbstractItemModelPtr = std::shared_ptr<AbstractItemModel>;
class AbstractItemDelegate;
using AbstractItemDelegatePtr = std::shared_ptr<AbstractItemDelegate>;

class AbstractItemView : public AbstractMinimumControl
{
public:
    AbstractItemView(Widget* const parent, std::u8string_view label, bool show);

    void set_model(AbstractItemModelPtr model) { model_ = model; }
    virtual void set_delegate(AbstractItemDelegatePtr delegate);
    virtual void set_current_index(const ModelIndex& idx);
    virtual void set_selection(const ModelIndex& idx, bool b);
    virtual void ClearSelection();

    virtual AbstractItemDelegatePtr delegate() const { return delegate_; }
    AbstractItemModelPtr model() const { return model_; }
    virtual const ModelIndex& current_index() const { return cur_idx_; }
    virtual const ModelIndex& previous_index() const { return prev_idx_; }
    virtual bool is_selected_item(const ModelIndex& idx) const;

    Signal<ModelIndex, ModelIndex> on_current_changed_;

protected:
    void OnUpdate() override;

    AbstractItemModelPtr model_;
    AbstractItemDelegatePtr delegate_;
    ModelIndex cur_idx_;
    ModelIndex prev_idx_;
};
}