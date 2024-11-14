#include <miniwin/widgets/base/abstract_control.h>

#include <imgui/imgui_internal.h>
#include <miniwin/core/imgui.h>

namespace miniwin {
AbstractControl::AbstractControl(Widget* parent, const String& text)
	: Widget{ parent, text }
{
}

AbstractControl::~AbstractControl()
{
}

bool AbstractControl::Visible() const
{
    //TODO ImGui::GetCurrentWindow
    return Widget::Visible() && !ImGui::GetCurrentWindow()->SkipItems;
}

void AbstractControl::PaintBegin()
{
	Widget::PaintBegin();
}

void AbstractControl::PaintEnd()
{
    Widget::SetSize(imgui::GetItemRectSize());
	Widget::PaintEnd();
}

AbstractTextualControl::AbstractTextualControl(Widget* parent, const String& text) : AbstractControl(parent, text) {}

const String& AbstractTextualControl::Text() const {
	return Name();
}

void AbstractTextualControl::SetText(const String& text) {
	auto prev = Name();
	SetName(text);
	OnTextChanged(text, std::move(prev));
}
}
