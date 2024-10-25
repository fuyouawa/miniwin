#include "button_impl.h"

#include <miniwin/core/imgui_helper.h>

namespace miniwin {
Button::Button(Widget* const parent, const String& text)
	: AbstractControl(parent, text)
{
	impl_ = std::make_unique<Impl>(this);
}

Vector2D Button::Size() const
{
	return impl_->size_to_set_ ? *impl_->size_to_set_ : AbstractControl::Size();
}

void Button::SetSize(const Vector2D& size)
{
	AbstractControl::SetSize(size);
	impl_->size_to_set_ = size;
}

void Button::PaintBegin()
{
	AbstractControl::PaintBegin();
	Vector2D size;
	if (impl_->size_to_set_)
	{
		size = *impl_->size_to_set_;
		impl_->size_to_set_ = std::nullopt;
	}
	else
	{
		size = Size();
	}
	if (ImGuiHelper::Button(Text(), size))
	{
		OnClicked();
	}
}
}
