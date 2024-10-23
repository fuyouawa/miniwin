#pragma once
#include <miniwin/core/global.h>

namespace miniwin {

class ImGuiFlags {
public:
    // Flags for ImGuiHelper::TableNextRow()
    enum TableRowFlags
    {
        kTableRowNone = 0,
        kTableRowHeaders = 1 << 0,   // Identify header row (set default background color + width of its contents accounted differently for auto column width)
    };

    // Enumeration for ImGui::SetNextWindow***(), SetWindow***(), SetNextItem***() functions
	// Represent a condition.
	// Important: Treat as a regular enum! Do NOT combine multiple values using binary operators! All the functions above treat 0 as a shortcut to kCondAlways.
    enum Cond
    {
        kCondNone = 0,        // No condition (always set the variable), same as _Always
        kCondAlways = 1 << 0,   // No condition (always set the variable), same as _None
        kCondOnce = 1 << 1,   // Set the variable once per runtime session (only the first call will succeed)
        kCondFirstUseEver = 1 << 2,   // Set the variable if the object/window has no persistently saved data (no entry in .ini file)
        kCondAppearing = 1 << 3,   // Set the variable if the object/window is appearing after being hidden/inactive (or the first time)
    };

	enum StyleVar
    {
        // Enum name --------------------- // Member in ImGuiStyle structure (see ImGuiStyle for descriptions)
        kStyleVarAlpha,               // float     Alpha
        kStyleVarDisabledAlpha,       // float     DisabledAlpha
        kStyleVarWindowPadding,       // ImVec2    WindowPadding
        kStyleVarWindowRounding,      // float     WindowRounding
        kStyleVarWindowBorderSize,    // float     WindowBorderSize
        kStyleVarWindowMinSize,       // ImVec2    WindowMinSize
        kStyleVarWindowTitleAlign,    // ImVec2    WindowTitleAlign
        kStyleVarChildRounding,       // float     ChildRounding
        kStyleVarChildBorderSize,     // float     ChildBorderSize
        kStyleVarPopupRounding,       // float     PopupRounding
        kStyleVarPopupBorderSize,     // float     PopupBorderSize
        kStyleVarFramePadding,        // ImVec2    FramePadding
        kStyleVarFrameRounding,       // float     FrameRounding
        kStyleVarFrameBorderSize,     // float     FrameBorderSize
        kStyleVarItemSpacing,         // ImVec2    ItemSpacing
        kStyleVarItemInnerSpacing,    // ImVec2    ItemInnerSpacing
        kStyleVarIndentSpacing,       // float     IndentSpacing
        kStyleVarCellPadding,         // ImVec2    CellPadding
        kStyleVarScrollbarSize,       // float     ScrollbarSize
        kStyleVarScrollbarRounding,   // float     ScrollbarRounding
        kStyleVarGrabMinSize,         // float     GrabMinSize
        kStyleVarGrabRounding,        // float     GrabRounding
        kStyleVarTabRounding,         // float     TabRounding
        kStyleVarTabBarBorderSize,    // float     TabBarBorderSize
        kStyleVarButtonTextAlign,     // ImVec2    ButtonTextAlign
        kStyleVarSelectableTextAlign, // ImVec2    SelectableTextAlign
        kStyleVarSeparatorTextBorderSize,// float  SeparatorTextBorderSize
        kStyleVarSeparatorTextAlign,  // ImVec2    SeparatorTextAlign
        kStyleVarSeparatorTextPadding,// ImVec2    SeparatorTextPadding
        kStyleVarDockingSeparatorSize // float     DockingSeparatorSize
    };
};
}
