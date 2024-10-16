#include <miniwin/delegate/selection_item_delegate.h>
#include <miniwin/widgets/base/abstract_item_view.h>

#include <miniwin/io/input.h>
#include <miniwin/core/flags.h>

#include <miniwin/core/drawer.h>

namespace miniwin {
SelectionItemDelegate::SelectionItemDelegate(Object* parent)
    : AbstractItemDelegate(parent)
{
}

void SelectionItemDelegate::Paint(AbstractItemView* view, const ModelIndex& index)
{
    auto model = view->model();
    auto selection_model = view->selection_model();
    auto& text = std::any_cast<const std::u8string&>(model->data(index));
    bool is_selected = selection_model->IsSelected(index);
    if (Drawer::Selectable(text, &is_selected, kSelectableSpanAllColumns | kSelectableAllowOverlap)) {
        if (Input::IsIoKeyDown(IoKeyCode::kCtrl)) {
            selection_model->Select(index, is_selected
                ? ItemSelectionModel::SelectionType::Select
                : ItemSelectionModel::SelectionType::Deselect);
        }
        else {
            if (is_selected)
            {
                selection_model->Select(index, ItemSelectionModel::SelectionType::ClearSelect);
            }
            else
            {
                selection_model->Clear();
            }
        }
    }
}
}
