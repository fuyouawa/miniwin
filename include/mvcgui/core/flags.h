#pragma once
#include <initializer_list>

namespace mvcgui {
namespace flags {
namespace window {
enum Flags {
    kNone = 0,
    kNoTitleBar = 1 << 0,   // Disable title-bar
    kNoResize = 1 << 1,   // Disable user resizing with the lower-right grip
    kNoMove = 1 << 2,   // Disable user moving the window
    kNoScrollbar = 1 << 3,   // Disable scrollbars (window can still scroll with mouse or programmatically)
    kNoScrollWithMouse = 1 << 4,   // Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
    kNoCollapse = 1 << 5,   // Disable user collapsing window by double-clicking on it. Also referred to as Window Menu Button (e.g. within a docking node).
    kAlwaysAutoResize = 1 << 6,   // Resize every window to its content every frame
    kNoBackground = 1 << 7,   // Disable drawing background color (WindowBg, etc.) and outside border. Similar as using SetNextWindowBgAlpha(0.0f).
    kNoSavedSettings = 1 << 8,   // Never load/save settings in .ini file
    kNoMouseInputs = 1 << 9,   // Disable catching mouse, hovering test with pass through.
    kMenuBar = 1 << 10,  // Has a menu-bar
    kHorizontalScrollbar = 1 << 11,  // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
    kNoFocusOnAppearing = 1 << 12,  // Disable taking focus when transitioning from hidden to visible state
    kNoBringToFrontOnFocus = 1 << 13,  // Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)
    kAlwaysVerticalScrollbar = 1 << 14,  // Always show vertical scrollbar (even if ContentSize.y < Size.y)
    kAlwaysHorizontalScrollbar = 1 << 15,  // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
    kNoNavInputs = 1 << 16,  // No gamepad/keyboard navigation within the window
    kNoNavFocus = 1 << 17,  // No focusing toward this window with gamepad/keyboard navigation (e.g. skipped by CTRL+TAB)
    kUnsavedDocument = 1 << 18,  // Display a dot next to the title. When used in a tab/docking context, tab is selected when clicking the X + closure is not assumed (will wait for user to stop submitting the tab). Otherwise closure is assumed when pressing the X, so if you keep submitting the tab may reappear at end of tab bar.
    kNoDocking = 1 << 19,  // Disable docking of this window
    kNoNav = kNoNavInputs | kNoNavFocus,
    kNoDecoration = kNoTitleBar | kNoResize | kNoScrollbar | kNoCollapse,
    kNoInputs = kNoMouseInputs | kNoNavInputs | kNoNavFocus
};
}
namespace combobox {
enum Flags
{
    kNone = 0,
    kPopupAlignLeft = 1 << 0,   // Align the popup toward the left by default
    kHeightSmall = 1 << 1,   // Max ~4 items visible. Tip: If you want your combo popup to be a specific size you can use SetNextWindowSizeConstraints() prior to calling BeginCombo()
    kHeightRegular = 1 << 2,   // Max ~8 items visible (default)
    kHeightLarge = 1 << 3,   // Max ~20 items visible
    kHeightLargest = 1 << 4,   // As many fitting items as possible
    kNoArrowButton = 1 << 5,   // Display on the preview box without the square arrow button
    kNoPreview = 1 << 6,   // Display only a square arrow button
    kWidthFitPreview = 1 << 7,   // Width dynamically calculated from preview contents
    kHeightMask_ = kHeightSmall | kHeightRegular | kHeightLarge | kHeightLargest,
};
}
namespace selectable {
enum Flags {
    kNone = 0,
    kDontClosePopups = 1 << 0,   // Clicking this doesn't close parent popup window
    kSpanAllColumns = 1 << 1,   // Frame will span all columns of its container table (text will still fit in current column)
    kAllowDoubleClick = 1 << 2,   // Generate press events on double clicks too
    kDisabled = 1 << 3,   // Cannot be selected, display grayed out text
    kAllowOverlap = 1 << 4,   // (WIP) Hit testing to allow subsequent widgets to overlap this one
};
}
namespace input_text {
enum Flags {
    kNone = 0,
    kCharsDecimal = 1 << 0,   // Allow 0123456789.+-*/
    kCharsHexadecimal = 1 << 1,   // Allow 0123456789ABCDEFabcdef
    kCharsUppercase = 1 << 2,   // Turn a..z into A..Z
    kCharsNoBlank = 1 << 3,   // Filter out spaces, tabs
    kAutoSelectAll = 1 << 4,   // Select entire text when first taking mouse focus
    kEnterReturnsTrue = 1 << 5,   // Return 'true' when Enter is pressed (as opposed to every time the value was modified). Consider looking at the IsItemDeactivatedAfterEdit() function.
    kCallbackCompletion = 1 << 6,   // Callback on pressing TAB (for completion handling)
    kCallbackHistory = 1 << 7,   // Callback on pressing Up/Down arrows (for history handling)
    kCallbackAlways = 1 << 8,   // Callback on each iteration. User code may query cursor position, modify text buffer.
    kCallbackCharFilter = 1 << 9,   // Callback on character inputs to replace or discard them. Modify 'EventChar' to replace or discard, or return 1 in callback to discard.
    kAllowTabInput = 1 << 10,  // Pressing TAB input a '\t' character into the text field
    kCtrlEnterForNewLine = 1 << 11,  // In multi-line mode, unfocus with Enter, add new line with Ctrl+Enter (default is opposite: unfocus with Ctrl+Enter, add line with Enter).
    kNoHorizontalScroll = 1 << 12,  // Disable following the cursor horizontally
    kAlwaysOverwrite = 1 << 13,  // Overwrite mode
    kReadOnly = 1 << 14,  // Read-only mode
    kPassword = 1 << 15,  // Password mode, display all characters as '*'
    kNoUndoRedo = 1 << 16,  // Disable undo/redo. Note that input text owns the text data while active, if you want to provide your own undo/redo stack you need e.g. to call ClearActiveID().
    kCharsScientific = 1 << 17,  // Allow 0123456789.+-*/eE (Scientific notation input)
    kCallbackResize = 1 << 18,  // Callback on buffer capacity changes request (beyond 'buf_size' parameter value), allowing the string to grow. Notify when the string wants to be resized (for string types which hold a cache of their Size). You will be provided a new BufSize in the callback and NEED to honor it. (see misc/cpp/imgui_stdlib.h for an example of using this)
    kCallbackEdit = 1 << 19,  // Callback on any edit (note that InputText() already returns true on edit, the callback is useful mainly to manipulate the underlying buffer while focus is active)
    kEscapeClearsAll = 1 << 20,  // Escape key clears content if not empty, and deactivate otherwise (contrast to default behavior of Escape to revert)
};
}
}
}