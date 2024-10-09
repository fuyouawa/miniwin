#include <fugui/widgets/widget/base/abstract_control.h>
#include <imgui/imgui_internal.h>

namespace fugui {
AbstractControl::AbstractControl(Widget* const parent, std::u8string_view label, bool show)
	: Widget{ parent, show }, label_{ label }
{
	widget_type_ = WidgetType::kControl;
}
void AbstractControl::OnPaintBegin()
{
	Widget::OnPaintBegin();
	is_showable_item_ = !ImGui::GetCurrentWindow()->SkipItems && is_showing();
	if (is_showable_item_) {
		OnItemShowablePaintBegin();
	}
}

void AbstractControl::OnPaintEnd()
{
	if (is_showable_item_) {
		OnItemShowablePaintEnd();
	}
	Widget::OnPaintEnd();
}

AbstractMinimumControl::AbstractMinimumControl(Widget* const parent, std::u8string_view label, bool show)
	: AbstractControl{ parent, label, show }
{
	widget_type_ = WidgetType::kMinimumControl;
}
}