#include <miniwin/core/flags.h>

namespace miniwin {
namespace {
template<class T>
T Or(T a, T b) {
    return static_cast<T>(static_cast<size_t>(a) | static_cast<size_t>(b));
}
template<class T>
T And(T a, T b) {
    return static_cast<T>(static_cast<size_t>(a) & static_cast<size_t>(b));
}
}

WidgetDrawFlags operator|(WidgetDrawFlags a, WidgetDrawFlags b) { return Or(a, b); }
WidgetDrawFlags operator&(WidgetDrawFlags a, WidgetDrawFlags b) { return And(a, b); }

WindowFlags operator|(WindowFlags a, WindowFlags b) { return Or(a, b); }
WindowFlags operator&(WindowFlags a, WindowFlags b) { return And(a, b); }

ComboBoxFlags operator|(ComboBoxFlags a, ComboBoxFlags b) { return Or(a, b); }
ComboBoxFlags operator&(ComboBoxFlags a, ComboBoxFlags b) { return And(a, b); }

SelectableFlags operator|(SelectableFlags a, SelectableFlags b) { return Or(a, b); }
SelectableFlags operator&(SelectableFlags a, SelectableFlags b) { return And(a, b); }

InputTextFlags operator|(InputTextFlags a, InputTextFlags b) { return Or(a, b); }
InputTextFlags operator&(InputTextFlags a, InputTextFlags b) { return And(a, b); }

TableFlags operator|(TableFlags a, TableFlags b) { return Or(a, b); }
TableFlags operator&(TableFlags a, TableFlags b) { return And(a, b); }

TableRowFlags operator|(TableRowFlags a, TableRowFlags b) { return Or(a, b); }
TableRowFlags operator&(TableRowFlags a, TableRowFlags b) { return And(a, b); }

TableColumnFlags operator|(TableColumnFlags a, TableColumnFlags b) { return Or(a, b); }
TableColumnFlags operator&(TableColumnFlags a, TableColumnFlags b) { return And(a, b); }
}
