#include <miniwin/widgets/base/abstract_control.h>
#include <imgui/imgui_internal.h>

namespace miniwin {
AbstractControl::AbstractControl(Widget* parent, std::u8string_view text)
	: Widget{ parent, text }
{
}

std::u8string_view AbstractControl::Text() const
{
    return Name();
}

void AbstractControl::SetText(std::u8string_view text)
{
    SetName(text);
}

bool AbstractControl::Visible() const
{
    return Widget::Visible() && !ImGui::GetCurrentWindow()->SkipItems;
}
}
