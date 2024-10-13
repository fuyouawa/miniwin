#include <fugui/widgets/base/abstract_control.h>
#include <imgui/imgui_internal.h>

namespace fugui {
AbstractControl::AbstractControl(Widget* const parent, std::u8string_view label, bool show)
	: Widget{ parent, label, show, WidgetType::kControl }
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
