#pragma once

namespace miniwin {
enum class WidgetDrawFlags
{
    kNone = 0,
    kIgnoreChildrenDraw = 1 << 0,
    kIgnoreSelfDraw = 1 << 1,
    kIgnoreDraw = kIgnoreChildrenDraw | kIgnoreSelfDraw
};

WidgetDrawFlags operator|(WidgetDrawFlags a, WidgetDrawFlags b);
WidgetDrawFlags operator&(WidgetDrawFlags a, WidgetDrawFlags b);

enum class WindowFlags
{
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
    kAlwaysVerticalScrollbar = 1 << 14,  // Always show vertical scrollbar (even if ContentSize.b < Size.b)
    kAlwaysHorizontalScrollbar = 1 << 15,  // Always show horizontal scrollbar (even if ContentSize.a < Size.a)
    kNoNavInputs = 1 << 16,  // No gamepad/keyboard navigation within the window
    kNoNavFocus = 1 << 17,  // No focusing toward this window with gamepad/keyboard navigation (e.g. skipped by CTRL+TAB)
    kUnsavedDocument = 1 << 18,  // Display a dot next to the title. When used in a tab/docking context, tab is selected when clicking the X + closure is not assumed (will wait for user to stop submitting the tab). Otherwise closure is assumed when pressing the X, so if you keep submitting the tab may reappear at end of tab bar.
    kNoDocking = 1 << 19,  // Disable docking of this window
    kNoNav = kNoNavInputs | kNoNavFocus,
    kNoDecoration = kNoTitleBar | kNoResize | kNoScrollbar | kNoCollapse,
    kNoInputs = kNoMouseInputs | kNoNavInputs | kNoNavFocus
};

WindowFlags operator|(WindowFlags a, WindowFlags b);
WindowFlags operator&(WindowFlags a, WindowFlags b);

enum class ComboBoxFlags
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

ComboBoxFlags operator|(ComboBoxFlags a, ComboBoxFlags b);
ComboBoxFlags operator&(ComboBoxFlags a, ComboBoxFlags b);

enum class SelectableFlags
{
    kNone = 0,
    kDontClosePopups = 1 << 0,   // Clicking this doesn't close parent popup window
    kSpanAllColumns = 1 << 1,   // Frame will span all columns of its container table (text will still fit in current column)
    kAllowDoubleClick = 1 << 2,   // Generate press events on double clicks too
    kDisabled = 1 << 3,   // Cannot be selected, display grayed out text
    kAllowOverlap = 1 << 4,   // (WIP) Hit testing to allow subsequent widgets to overlap this one
};

SelectableFlags operator|(SelectableFlags a, SelectableFlags b);
SelectableFlags operator&(SelectableFlags a, SelectableFlags b);

enum class InputTextFlags
{
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

InputTextFlags operator|(InputTextFlags a, InputTextFlags b);
InputTextFlags operator&(InputTextFlags a, InputTextFlags b);

enum class TableFlags
{
    // Features
    kNone = 0,
    kResizable = 1 << 0,   // Enable resizing columns.
    kReorderable = 1 << 1,   // Enable reordering columns in header row (need calling TableSetupColumn() + TableHeadersRow() to display headers)
    kHideable = 1 << 2,   // Enable hiding/disabling columns in context menu.
    kSortable = 1 << 3,   // Enable sorting. Call TableGetSortSpecs() to obtain sort specs. Also see kSortMulti and kSortTristate.
    kNoSavedSettings = 1 << 4,   // Disable persisting columns order, width and sort settings in the .ini file.
    kContextMenuInBody = 1 << 5,   // Right-click on columns body/contents will display table context menu. By default it is available in TableHeadersRow().
    // Decorations
    kRowBg = 1 << 6,   // Set each RowBg color with ImGuiCol_TableRowBg or ImGuiCol_TableRowBgAlt (equivalent of calling TableSetBgColor with ImGuiTableBgFlags_RowBg0 on each row manually)
    kBordersInnerH = 1 << 7,   // Draw horizontal borders between rows.
    kBordersOuterH = 1 << 8,   // Draw horizontal borders at the top and bottom.
    kBordersInnerV = 1 << 9,   // Draw vertical borders between columns.
    kBordersOuterV = 1 << 10,  // Draw vertical borders on the left and right sides.
    kBordersH = kBordersInnerH | kBordersOuterH, // Draw horizontal borders.
    kBordersV = kBordersInnerV | kBordersOuterV, // Draw vertical borders.
    kBordersInner = kBordersInnerV | kBordersInnerH, // Draw inner borders.
    kBordersOuter = kBordersOuterV | kBordersOuterH, // Draw outer borders.
    kBorders = kBordersInner | kBordersOuter,   // Draw all borders.
    kNoBordersInBody = 1 << 11,  // [ALPHA] Disable vertical borders in columns Body (borders will always appear in Headers). -> May move to style
    kNoBordersInBodyUntilResize = 1 << 12,  // [ALPHA] Disable vertical borders in columns Body until hovered for resize (borders will always appear in Headers). -> May move to style
    // Sizing Policy (read above for defaults)
    kSizingFixedFit = 1 << 13,  // Columns default to _WidthFixed or _WidthAuto (if resizable or not resizable), matching contents width.
    kSizingFixedSame = 2 << 13,  // Columns default to _WidthFixed or _WidthAuto (if resizable or not resizable), matching the maximum contents width of all columns. Implicitly enable kNoKeepColumnsVisible.
    kSizingStretchProp = 3 << 13,  // Columns default to _WidthStretch with default weights proportional to each columns contents widths.
    kSizingStretchSame = 4 << 13,  // Columns default to _WidthStretch with default weights all equal, unless overridden by TableSetupColumn().
    // Sizing Extra Options
    kNoHostExtendX = 1 << 16,  // Make outer width auto-fit to columns, overriding outer_size.a value. Only available when ScrollX/ScrollY are disabled and Stretch columns are not used.
    kNoHostExtendY = 1 << 17,  // Make outer height stop exactly at outer_size.b (prevent auto-extending table past the limit). Only available when ScrollX/ScrollY are disabled. Data below the limit will be clipped and not visible.
    kNoKeepColumnsVisible = 1 << 18,  // Disable keeping column always minimally visible when ScrollX is off and table gets too small. Not recommended if columns are resizable.
    kPreciseWidths = 1 << 19,  // Disable distributing remainder width to stretched columns (width allocation on a 100-wide table with 3 columns: Without this flag: 33,33,34. With this flag: 33,33,33). With larger number of columns, resizing will appear to be less smooth.
    // Clipping
    kNoClip = 1 << 20,  // Disable clipping rectangle for every individual columns (reduce draw command count, items will be able to overflow into other columns). Generally incompatible with TableSetupScrollFreeze().
    // Padding
    kPadOuterX = 1 << 21,  // Default if BordersOuterV is on. Enable outermost padding. Generally desirable if you have headers.
    kNoPadOuterX = 1 << 22,  // Default if BordersOuterV is off. Disable outermost padding.
    kNoPadInnerX = 1 << 23,  // Disable inner padding between columns (double inner padding if BordersOuterV is on, single inner padding if BordersOuterV is off).
    // Scrolling
    kScrollX = 1 << 24,  // Enable horizontal scrolling. Require 'outer_size' parameter of BeginTable() to specify the container size. Changes default sizing policy. Because this creates a child window, ScrollY is currently generally recommended when using ScrollX.
    kScrollY = 1 << 25,  // Enable vertical scrolling. Require 'outer_size' parameter of BeginTable() to specify the container size.
    // Sorting
    kSortMulti = 1 << 26,  // Hold shift when clicking headers to sort on multiple column. TableGetSortSpecs() may return specs where (SpecsCount > 1).
    kSortTristate = 1 << 27,  // Allow no sorting, disable default sorting. TableGetSortSpecs() may return specs where (SpecsCount == 0).
    // Miscellaneous
    kHighlightHoveredColumn = 1 << 28,  // Highlight column headers when hovered (may evolve into a fuller highlight)
};

TableFlags operator|(TableFlags a, TableFlags b);
TableFlags operator&(TableFlags a, TableFlags b);

enum class TableRowFlags
{
    kNone = 0,
    kHeaders = 1 << 0,   // Identify header row (set default background color + width of its contents accounted differently for auto column width)
};

TableRowFlags operator|(TableRowFlags a, TableRowFlags b);
TableRowFlags operator&(TableRowFlags a, TableRowFlags b);

enum class TableColumnFlags
{
    // Input configuration flags
    kNone = 0,
    kDisabled = 1 << 0,   // Overriding/master disable flag: hide column, won't show in context menu (unlike calling TableSetColumnEnabled() which manipulates the user accessible state)
    kDefaultHide = 1 << 1,   // Default as a hidden/disabled column.
    kDefaultSort = 1 << 2,   // Default as a sorting column.
    kWidthStretch = 1 << 3,   // Column will stretch. Preferable with horizontal scrolling disabled (default if table sizing policy is _SizingStretchSame or _SizingStretchProp).
    kWidthFixed = 1 << 4,   // Column will not stretch. Preferable with horizontal scrolling enabled (default if table sizing policy is _SizingFixedFit and table is resizable).
    kNoResize = 1 << 5,   // Disable manual resizing.
    kNoReorder = 1 << 6,   // Disable manual reordering this column, this will also prevent other columns from crossing over this column.
    kNoHide = 1 << 7,   // Disable ability to hide/disable this column.
    kNoClip = 1 << 8,   // Disable clipping for this column (all NoClip columns will render in a same draw command).
    kNoSort = 1 << 9,   // Disable ability to sort on this field (even if ImGuiTableFlags_Sortable is set on the table).
    kNoSortAscending = 1 << 10,  // Disable ability to sort in the ascending direction.
    kNoSortDescending = 1 << 11,  // Disable ability to sort in the descending direction.
    kNoHeaderLabel = 1 << 12,  // TableHeadersRow() will not submit horizontal label for this column. Convenient for some small columns. Name will still appear in context menu or in angled headers.
    kNoHeaderWidth = 1 << 13,  // Disable header text width contribution to automatic column width.
    kPreferSortAscending = 1 << 14,  // Make the initial sort direction Ascending when first sorting on this column (default).
    kPreferSortDescending = 1 << 15,  // Make the initial sort direction Descending when first sorting on this column.
    kIndentEnable = 1 << 16,  // Use current Indent value when entering cell (default for column 0).
    kIndentDisable = 1 << 17,  // Ignore current Indent value when entering cell (default for columns > 0). Indentation changes _within_ the cell will still be honored.
    kAngledHeader = 1 << 18,  // TableHeadersRow() will submit an angled header row for this column. Note this will add an extra row.

    // Output status flags, read-only via TableGetColumnFlags()
    kIsEnabled = 1 << 24,  // Status: is enabled == not hidden by user/api (referred to as "Hide" in _DefaultHide and _NoHide) flags.
    kIsVisible = 1 << 25,  // Status: is visible == is enabled AND not clipped by scrolling.
    kIsSorted = 1 << 26,  // Status: is currently part of the sort specs
    kIsHovered = 1 << 27,  // Status: is hovered by mouse
};

TableColumnFlags operator|(TableColumnFlags a, TableColumnFlags b);
TableColumnFlags operator&(TableColumnFlags a, TableColumnFlags b);
}
