#include <miniwin/delegate/selection_item_delegate.h>
#include <miniwin/widgets/base/abstract_item_view.h>

#include <miniwin/io/input.h>
#include <miniwin/core/flags.h>

#include <miniwin/core/imgui_helper.h>

namespace miniwin {
SelectionItemDelegate::SelectionItemDelegate(Object* parent)
    : AbstractItemDelegate(parent)
{
}

void SelectionItemDelegate::Paint(AbstractItemView* view, const ModelIndex& index)
{
    auto model = view->Model();
    auto selection_model = view->SelectionModel();
    auto text = model->Data(index).ToString();
    bool is_selected = selection_model->IsSelected(index);
    if (ImGuiHelper::Selectable(text, &is_selected)) {
        if (Input::IsIoKeyDown(IoKeyCode::kCtrl)) {
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
