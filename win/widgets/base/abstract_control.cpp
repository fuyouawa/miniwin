#include <miniwin/widgets/base/abstract_control.h>
#include <imgui/imgui_internal.h>

namespace miniwin {
AbstractControl::AbstractControl(Widget* parent, std::u8string_view label)
	: Widget{ parent, label, WidgetType::kControl }
{
}

std::u8string_view AbstractControl::label() const
{
    return name();
}

void AbstractControl::set_label(std::u8string_view label)
{
    set_name(label);
}

bool AbstractControl::visible() const
{
    return Widget::visible() && !ImGui::GetCurrentWindow()->SkipItems;
}
}
