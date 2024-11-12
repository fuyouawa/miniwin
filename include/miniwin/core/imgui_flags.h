#pragma once

namespace miniwin {
namespace imgui {
enum WindowFlags {
    kWindowNone = 0,
    kWindowNoTitleBar = 1 << 0,   // Disable title-bar
    kWindowNoResize = 1 << 1,   // Disable user resizing with the lower-right grip
    kWindowNoMove = 1 << 2,   // Disable user moving the window
    kWindowNoScrollbar = 1 << 3,   // Disable scrollbars (window can still scroll with mouse or programmatically)
    kWindowNoScrollWithMouse = 1 << 4,   // Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
    kWindowNoCollapse = 1 << 5,   // Disable user collapsing window by double-clicking on it. Also referred to as Window Menu Button (e.g. within a docking node).
    kWindowAlwaysAutoResize = 1 << 6,   // Resize every window to its content every frame
    kWindowNoBackground = 1 << 7,   // Disable drawing background color (WindowBg, etc.) and outside border. Similar as using SetNextWindowBgAlpha(0.0f).
    kWindowNoSavedSettings = 1 << 8,   // Never load/save settings in .ini file
    kWindowNoMouseInputs = 1 << 9,   // Disable catching mouse, hovering test with pass through.
    kWindowMenuBar = 1 << 10,  // Has a menu-bar
    kWindowHorizontalScrollbar = 1 << 11,  // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
    kWindowNoFocusOnAppearing = 1 << 12,  // Disable taking focus when transitioning from hidden to visible state
    kWindowNoBringToFrontOnFocus = 1 << 13,  // Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)
    kWindowAlwaysVerticalScrollbar = 1 << 14,  // Always show vertical scrollbar (even if ContentSize.y < Size.y)
    kWindowAlwaysHorizontalScrollbar = 1 << 15,  // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
    kWindowNoNavInputs = 1 << 16,  // No gamepad/keyboard navigation within the window
    kWindowNoNavFocus = 1 << 17,  // No focusing toward this window with gamepad/keyboard navigation (e.g. skipped by CTRL+TAB)
    kWindowUnsavedDocument = 1 << 18,  // Display a dot next to the title. When used in a tab/docking context, tab is selected when clicking the X + closure is not assumed (will wait for user to stop submitting the tab). Otherwise closure is assumed when pressing the X, so if you keep submitting the tab may reappear at end of tab bar.
    kWindowNoDocking = 1 << 19,  // Disable docking of this window
    kWindowNoNav = kWindowNoNavInputs | kWindowNoNavFocus,
    kWindowNoDecoration = kWindowNoTitleBar | kWindowNoResize | kWindowNoScrollbar | kWindowNoCollapse,
    kWindowNoInputs = kWindowNoMouseInputs | kWindowNoNavInputs | kWindowNoNavFocus,

};

enum PopupFlags {
    kPopupNone = 0,
    kPopupMouseButtonLeft = 0,        // For BeginPopupContext*(): open on Left Mouse release. Guaranteed to always be == 0 (same as ImGuiMouseButton_Left)
    kPopupMouseButtonRight = 1,        // For BeginPopupContext*(): open on Right Mouse release. Guaranteed to always be == 1 (same as ImGuiMouseButton_Right)
    kPopupMouseButtonMiddle = 2,        // For BeginPopupContext*(): open on Middle Mouse release. Guaranteed to always be == 2 (same as ImGuiMouseButton_Middle)
    kPopupMouseButtonMask_ = 0x1F,
    kPopupMouseButtonDefault_ = 1,
    kPopupNoOpenOverExistingPopup = 1 << 5,   // For OpenPopup*(), BeginPopupContext*(): don't open if there's already a popup at the same level of the popup stack
    kPopupNoOpenOverItems = 1 << 6,   // For BeginPopupContextWindow(): don't return true when hovering items, only when hovering empty space
    kPopupAnyPopupId = 1 << 7,   // For IsPopupOpen(): ignore the ImGuiID parameter and test for any popup.
    kPopupAnyPopupLevel = 1 << 8,   // For IsPopupOpen(): search/test at any level of the popup stack (default test in the current level)
    kPopupAnyPopup = kPopupAnyPopupId | kPopupAnyPopupLevel,
};

// Flags for imgui::TableNextRow()
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
}
}
