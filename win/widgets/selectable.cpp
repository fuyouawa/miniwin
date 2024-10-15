#include <miniwin/widgets/selectable.h>
#include <miniwin/core/drawer.h>

namespace miniwin {
Selectable::Selectable(Widget* const parent, std::u8string_view label)
	: AbstractControl{ parent, label },
	cur_selected_{ false },
	prev_selected_{ false }
{
}

bool Selectable::is_selected() const
{
    return cur_selected_;
}

void Selectable::set_selection(bool b)
{
    cur_selected_ = b;
}

void Selectable::PaintBegin()
{
    AbstractControl::PaintBegin();

    Drawer::Selectable(label(), &cur_selected_, flags(), size());
    if (cur_selected_ != prev_selected_) {
        OnSelectionChanged(cur_selected_);
    }
    prev_selected_ = cur_selected_;
}
}
