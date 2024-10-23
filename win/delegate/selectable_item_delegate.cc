#include "selectable_item_delegate_impl.h"

#include <miniwin/io/input.h>
#include <miniwin/core/imgui_helper.h>
#include <miniwin/widgets/base/abstract_item_view.h>

namespace miniwin {
SelectableItemDelegate::SelectableItemDelegate(Object* parent)
    : AbstractItemDelegate(parent)
{
    impl_ = std::make_unique<Impl>(this);
}

bool SelectableItemDelegate::IsAllocMultiSelect() const
{
    return impl_->alloc_multi_select;
}

void SelectableItemDelegate::SetAllocMultiSelect(bool b)
{
    impl_->alloc_multi_select = b;
}

void SelectableItemDelegate::Paint(AbstractItemView* view, const ModelIndex& index)
{
    auto model = view->Model();
    auto selection_model = view->SelectionModel();
    auto text = model->Data(index).ToUtf8String();
    bool is_selected = selection_model->IsSelected(index);
    if (ImGuiHelper::Selectable(text, &is_selected)) {
        if (Input::IsIoKeyDown(IoKeyCode::kCtrl) && IsAllocMultiSelect()) {
            selection_model->Select(index, is_selected
                ? ItemSelectionType::Select
                : ItemSelectionType::Deselect);
        }
        else {
            if (is_selected)
            {
                selection_model->Select(index, ItemSelectionType::ClearSelect);
            }
            else
            {
                selection_model->Clear();
            }
        }
    }
}
}
