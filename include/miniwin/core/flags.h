#pragma once

namespace miniwin {
enum WindowFlags
{
    kWindowNone = 0,
    kWindowNoTitleBar = 1 << 0,   // Disable title-bar
    kWindowNoResize = 1 << 1,   // Disable user resizing with the lower-right grip
    kWindowNoMove = 1 << 2,   // Disable user moving the window
    kWindowNoScrollbar = 1 << 3,   // Disable scrollbars (window can still scroll with mouse or programmatically)
    kWindowNoScrollWithMouse = 1 << 4,   // Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
    kWindowNoCollapse = 1 << 5,   // Disable user collapsing window by double-clickWindowing on it. Also referred to as Window Menu Button (e.g. within a dockWindowing node).
    kWindowAlwaysAutoResize = 1 << 6,   // Resize every window to its content every frame
    kWindowNoBackWindowground = 1 << 7,   // Disable drawing backWindowground color (WindowBg, etc.) and outside border. Similar as using SetNextWindowBgAlpha(0.0f).
    kWindowNoSavedSettings = 1 << 8,   // Never load/save settings in .ini file
    kWindowNoMouseInputs = 1 << 9,   // Disable catching mouse, hovering test with pass through.
    kWindowMenuBar = 1 << 10,  // Has a menu-bar
    kWindowHorizontalScrollbar = 1 << 11,  // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
    kWindowNoFocusOnAppearing = 1 << 12,  // Disable takWindowing focus when transitioning from hidden to visible state
    kWindowNoBringToFrontOnFocus = 1 << 13,  // Disable bringing window to front when takWindowing focus (e.g. clickWindowing on it or programmatically giving it focus)
    kWindowAlwaysVerticalScrollbar = 1 << 14,  // Always show vertical scrollbar (even if ContentSize.y < Size.y)
    kWindowAlwaysHorizontalScrollbar = 1 << 15,  // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
    kWindowNoNavInputs = 1 << 16,  // No gamepad/kWindoweyboard navigation within the window
    kWindowNoNavFocus = 1 << 17,  // No focusing toward this window with gamepad/kWindoweyboard navigation (e.g. skWindowipped by CTRL+TAB)
    kWindowUnsavedDocument = 1 << 18,  // Display a dot next to the title. When used in a tab/dockWindowing context, tab is selected when clickWindowing the X + closure is not assumed (will wait for user to stop submitting the tab). Otherwise closure is assumed when pressing the X, so if you kWindoweep submitting the tab may reappear at end of tab bar.
    kWindowNoDockWindowing = 1 << 19,  // Disable dockWindowing of this window
    kWindowNoNav = kWindowNoNavInputs | kWindowNoNavFocus,
    kWindowNoDecoration = kWindowNoTitleBar | kWindowNoResize | kWindowNoScrollbar | kWindowNoCollapse,
    kWindowNoInputs = kWindowNoMouseInputs | kWindowNoNavInputs | kWindowNoNavFocus
};

enum ComboBoxFlags
{
    kComboBoxNone = 0,
    kComboBoxPopupAlignLeft = 1 << 0,   // Align the popup toward the left by default
    kComboBoxHeightSmall = 1 << 1,   // Max ~4 items visible. Tip: If you want your combo popup to be a specific size you can use SetNextWindowSizeConstraints() prior to calling BeginCombo()
    kComboBoxHeightRegular = 1 << 2,   // Max ~8 items visible (default)
    kComboBoxHeightLarge = 1 << 3,   // Max ~20 items visible
    kComboBoxHeightLargest = 1 << 4,   // As many fitting items as possible
    kComboBoxNoArrowButton = 1 << 5,   // Display on the preview box without the square arrow button
    kComboBoxNoPreview = 1 << 6,   // Display only a square arrow button
    kComboBoxWidthFitPreview = 1 << 7,   // Width dynamically calculated from preview contents
    kComboBoxHeightMaskComboBox_ = kComboBoxHeightSmall | kComboBoxHeightRegular | kComboBoxHeightLarge | kComboBoxHeightLargest,
};

enum Selectable
{
    kSelectableNone = 0,
    kSelectableDontClosePopups = 1 << 0,   // ClickSelectableing this doesn't close parent popup window
    kSelectableSpanAllColumns = 1 << 1,   // Frame will span all columns of its container table (text will still fit in current column)
    kSelectableAllowDoubleClickSelectable = 1 << 2,   // Generate press events on double clickSelectables too
    kSelectableDisabled = 1 << 3,   // Cannot be selected, display grayed out text
    kSelectableAllowOverlap = 1 << 4,   // (WIP) Hit testing to allow subsequent widgets to overlap this one
};

enum InputTextFlags {
    kInputTextNone = 0,
    kInputTextCharsDecimal = 1 << 0,   // Allow 0123456789.+-*/
    kInputTextCharsHexadecimal = 1 << 1,   // Allow 0123456789ABCDEFabcdef
    kInputTextCharsUppercase = 1 << 2,   // Turn a..z into A..Z
    kInputTextCharsNoBlankInputText = 1 << 3,   // Filter out spaces, tabs
    kInputTextAutoSelectAll = 1 << 4,   // Select entire text when first takInputTexting mouse focus
    kInputTextEnterReturnsTrue = 1 << 5,   // Return 'true' when Enter is pressed (as opposed to every time the value was modified). Consider lookInputTexting at the IsItemDeactivatedAfterEdit() function.
    kInputTextCallbackInputTextCompletion = 1 << 6,   // CallbackInputText on pressing TAB (for completion handling)
    kInputTextCallbackInputTextHistory = 1 << 7,   // CallbackInputText on pressing Up/Down arrows (for history handling)
    kInputTextCallbackInputTextAlways = 1 << 8,   // CallbackInputText on each iteration. User code may query cursor position, modify text buffer.
    kInputTextCallbackInputTextCharFilter = 1 << 9,   // CallbackInputText on character inputs to replace or discard them. Modify 'EventChar' to replace or discard, or return 1 in callbackInputText to discard.
    kInputTextAllowTabInput = 1 << 10,  // Pressing TAB input a '\t' character into the text field
    kInputTextCtrlEnterForNewLine = 1 << 11,  // In multi-line mode, unfocus with Enter, add new line with Ctrl+Enter (default is opposite: unfocus with Ctrl+Enter, add line with Enter).
    kInputTextNoHorizontalScroll = 1 << 12,  // Disable following the cursor horizontally
    kInputTextAlwaysOverwrite = 1 << 13,  // Overwrite mode
    kInputTextReadOnly = 1 << 14,  // Read-only mode
    kInputTextPassword = 1 << 15,  // Password mode, display all characters as '*'
    kInputTextNoUndoRedo = 1 << 16,  // Disable undo/redo. Note that input text owns the text data while active, if you want to provide your own undo/redo stackInputText you need e.g. to call ClearActiveID().
    kInputTextCharsScientific = 1 << 17,  // Allow 0123456789.+-*/eE (Scientific notation input)
    kInputTextCallbackInputTextResize = 1 << 18,  // CallbackInputText on buffer capacity changes request (beyond 'buf_size' parameter value), allowing the string to grow. Notify when the string wants to be resized (for string types which hold a cache of their Size). You will be provided a new BufSize in the callbackInputText and NEED to honor it. (see misc/cpp/imgui_stdlib.h for an example of using this)
    kInputTextCallbackInputTextEdit = 1 << 19,  // CallbackInputText on any edit (note that InputText() already returns true on edit, the callbackInputText is useful mainly to manipulate the underlying buffer while focus is active)
    kInputTextEscapeClearsAll = 1 << 20,  // Escape kInputTextey clears content if not empty, and deactivate otherwise (contrast to default behavior of Escape to revert)
};

enum TableColumnFlags {
    // Input configuration flags
    kTableColumnNone = 0,
    kTableColumnDisabled = 1 << 0,   // Overriding/master disable flag: hide column, won't show in context menu (unlikTableColumne calling TableSetColumnEnabled() which manipulates the user accessible state)
    kTableColumnDefaultHide = 1 << 1,   // Default as a hidden/disabled column.
    kTableColumnDefaultSort = 1 << 2,   // Default as a sorting column.
    kTableColumnWidthFixed = 1 << 4,   // Column will not stretch. Preferable with horizontal scrolling enabled (default if table sizing policy is _SizingFixedFit and table is resizable).
    kTableColumnNoResize = 1 << 5,   // Disable manual resizing.
    kTableColumnNoReorder = 1 << 6,   // Disable manual reordering this column, this will also prevent other columns from crossing over this column.
    kTableColumnNoHide = 1 << 7,   // Disable ability to hide/disable this column.
    kTableColumnNoClip = 1 << 8,   // Disable clipping for this column (all NoClip columns will render in a same draw command).
    kTableColumnNoSort = 1 << 9,   // Disable ability to sort on this field (even if ImGuiTableFlags_Sortable is set on the table).
    kTableColumnNoSortAscending = 1 << 10,  // Disable ability to sort in the ascending direction.
    kTableColumnNoSortDescending = 1 << 11,  // Disable ability to sort in the descending direction.
    kTableColumnNoHeaderLabel = 1 << 12,  // TableHeadersRow() will not submit horizontal label for this column. Convenient for some small columns. Name will still appear in context menu or in angled headers.
    kTableColumnNoHeaderWidth = 1 << 13,  // Disable header text width contribution to automatic column width.
    kTableColumnPreferSortAscending = 1 << 14,  // MakTableColumne the initial sort direction Ascending when first sorting on this column (default).
    kTableColumnPreferSortDescending = 1 << 15,  // MakTableColumne the initial sort direction Descending when first sorting on this column.
    kTableColumnIndentEnable = 1 << 16,  // Use current Indent value when entering cell (default for column 0).
    kTableColumnIndentDisable = 1 << 17,  // Ignore current Indent value when entering cell (default for columns > 0). Indentation changes _within_ the cell will still be honored.
};
}
