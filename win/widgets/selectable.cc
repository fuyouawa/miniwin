#include <miniwin/widgets/selectable.h>

#include <miniwin/core/imgui.h>

namespace miniwin {
class Selectable::Impl {
public:
    Impl(Selectable* owner) : owner_(owner) {}

    Selectable* owner_;
    bool cur_selected_ = false;
    bool prev_selected_ = false;
};

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

    imgui::Selectable(Text(), &impl_->cur_selected_, 0, Size());
    if (impl_->cur_selected_ != impl_->prev_selected_) {
        OnSelectionChanged(impl_->cur_selected_);
    }
    impl_->prev_selected_ = impl_->cur_selected_;
}
}
