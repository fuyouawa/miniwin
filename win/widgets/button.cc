#include "button_impl.h"

#include <miniwin/core/imgui.h>

namespace miniwin {
Button::Button(Widget* const parent, const String& text)
	: AbstractControl(parent, text)
{
	impl_ = std::make_unique<Impl>(this);
}

void Button::PaintBegin()
{
	AbstractControl::PaintBegin();
	if (imgui::Button(Text(), Size()))
	{
		OnClicked();
	}
}
}
