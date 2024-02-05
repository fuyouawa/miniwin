#include <mvcgui/widgets/widget/base/abstract_control.h>
#include <imgui/imgui_internal.h>

namespace mvcgui {
AbstractControl::AbstractControl(Widget* const parent, std::u8string_view label, bool show)
	: Widget{ parent, show }, label_{ label }
{
	widget_type_ = Type::kControl;
	id_ = u8"Control: " + label_;
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
	widget_type_ = Type::kMinimumControl;
}
}