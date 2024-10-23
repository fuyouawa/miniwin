#include <miniwin/widgets/layout/layout.h>

#include "miniwin/core/imgui_helper.h"

namespace miniwin {
Layout::Layout(Widget* parent)
	: Widget(parent, u8"Layout")
{
}
void Layout::AddWidget(Widget* widget)
{
	widget->SetWidgetParent(this);
}

void Layout::RemoveWidget(Widget* widget)
{
	widget->SetWidgetParent(const_cast<Widget*>(WidgetParent()));
}

bool Layout::SetWidgetIndex(const Widget* widget, size_t index)
{
	return Widget::SetWidgetChildIndex(widget, index);
}

std::optional<size_t> Layout::IndexOfWidget(const Widget* widget) const
{
	return Widget::IndexOfWidgetChild(widget);
}

std::optional<size_t> Layout::AdvanceWidget(const Widget* widget, size_t count)
{
	auto opt = IndexOfWidget(widget);
	if (!opt.has_value())
		return std::nullopt;
	size_t c = Count();
	size_t idx = opt.value();
	size_t end_idx = idx + count;
	if (end_idx >= c)
	{
		end_idx = c - 1;
	}
	count = end_idx - idx;
	if (count > 0)
	{
		if (SetWidgetIndex(widget, end_idx))
		{
			return count;
		}
		return std::nullopt;
	}
	return 0;
}

size_t Layout::Count() const
{
	return WidgetChildren().size();
}

bool Layout::IsEmpty() const
{
	return Count() == 0;
}

void Layout::PaintBegin()
{
	Widget::PaintBegin();
	float height = 0;
	for (auto c : WidgetChildren())
	{
		auto h = c->Size().y();
		if (h > height)
			height = h;
	}
	auto size = Size();
	size.set_y(height);
	ImGuiHelper::BeginChildWindow(u8"LayoutFrame", size);
}

void Layout::PaintEnd()
{
	ImGuiHelper::EndChildWindow();
	Widget::PaintEnd();
}
}
