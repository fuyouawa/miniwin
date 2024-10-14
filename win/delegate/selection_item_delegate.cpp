#include <miniwin/delegate/selection_item_delegate.h>
#include <miniwin/widgets/base/abstract_item_view.h>

#include <miniwin/io/input.h>
#include <miniwin/core/flags.h>

#include <win/core/drawer.h>

namespace miniwin {
SelectionItemDelegate::SelectionItemDelegate()
{
}

void SelectionItemDelegate::Paint(AbstractItemView* view, const ModelIndex& index)
{
    auto model = view->model();
    auto selection_model = view->selection_model();
    auto text = model->text(index);
    bool is_selected = selection_model->IsSelected(index);
    if (Drawer::Selectable(text, &is_selected, kSelectableSpanAllColumns | kSelectableAllowOverlap)) {
        if (Input::IsIoKeyDown(IoKeyCode::kCtrl)) {
            selection_model->Select(index, is_selected
                ? ItemSelectionModel::SelectionType::Select
                : ItemSelectionModel::SelectionType::Deselect);
        }
        else {
            selection_model->Select(index, is_selected
                ? ItemSelectionModel::SelectionType::ClearSelect
                : ItemSelectionModel::SelectionType::Clear);
        }
    }
}
}
