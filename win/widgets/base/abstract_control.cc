#include <miniwin/widgets/base/abstract_control.h>

#include <imgui/imgui_internal.h>
#include <miniwin/core/imgui.h>

namespace miniwin {
AbstractMinimumControl::AbstractMinimumControl() {}

AbstractMinimumControl::~AbstractMinimumControl() {}

bool AbstractMinimumControl::Visible() const {
	//TODO ImGui::GetCurrentWindow
	return Widget::Visible() && !ImGui::GetCurrentWindow()->SkipItems;
}

void AbstractMinimumControl::PaintBegin() {
	Widget::PaintBegin();
}

void AbstractMinimumControl::PaintEnd() {
	Widget::SetSize(imgui::GetItemRectSize());
	Widget::PaintEnd();
}

AbstractControl::AbstractControl() {}

String AbstractControl::Text() const {
	return Name();
}

void AbstractControl::SetText(const String& text) {
	auto prev = Name();
	SetName(text);
	OnTextChanged(text, std::move(prev));
}
}
