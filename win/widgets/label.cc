#include <miniwin/widgets/label.h>

#include <miniwin/core/imgui.h>

#include "win/tools/debug.h"

namespace miniwin {
Label::Label()
{
}

void Label::PaintBegin() {
    AbstractMinimumControl::PaintBegin();
	imgui::Text(Text());
}

void Label::SetSize(const Vector2D& size) {
	MW_ASSERT(false, "You cant set label size!");
}
}
