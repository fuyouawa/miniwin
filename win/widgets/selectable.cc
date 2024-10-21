#include "selectable_impl.h"

#include <miniwin/core/imgui_helper.h>

namespace miniwin {
Selectable::Selectable(Widget* const parent, std::u8string_view label)
	: AbstractControl{ parent, label }
{
    impl_ = std::make_unique<Impl>(this);
}

Selectable::~Selectable()
{
}

bool Selectable::is_selected() const
{
    return impl_->cur_selected_;
}

void Selectable::set_selection(bool b)
{
    impl_->cur_selected_ = b;
}

SelectableFlags Selectable::flags() const
{
    return impl_->flags_;
}

void Selectable::set_flags(SelectableFlags flags)
{
    impl_->flags_ = flags;
}

void Selectable::PaintBegin()
{
    AbstractControl::PaintBegin();

    ImGuiHelper::Selectable(label(), &impl_->cur_selected_, flags(), size());
    if (impl_->cur_selected_ != impl_->prev_selected_) {
        OnSelectionChanged(impl_->cur_selected_);
    }
    impl_->prev_selected_ = impl_->cur_selected_;
}
}
