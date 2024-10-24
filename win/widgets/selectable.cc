#include "selectable_impl.h"

#include <miniwin/core/imgui_helper.h>

namespace miniwin {
Selectable::Selectable(Widget* const parent, const String& text)
	: AbstractControl{ parent, text }
{
    impl_ = std::make_unique<Impl>(this);
}

Selectable::~Selectable()
{
}

bool Selectable::IsSelected() const
{
    return impl_->cur_selected_;
}

void Selectable::SetSelection(bool b)
{
    impl_->cur_selected_ = b;
}

void Selectable::PaintBegin()
{
    AbstractControl::PaintBegin();

    ImGuiHelper::Selectable(Text(), &impl_->cur_selected_, 0, Size());
    if (impl_->cur_selected_ != impl_->prev_selected_) {
        OnSelectionChanged(impl_->cur_selected_);
    }
    impl_->prev_selected_ = impl_->cur_selected_;
}
}
