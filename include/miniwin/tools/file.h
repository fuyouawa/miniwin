#pragma once
#include <miniwin/tools/string.h>
#include <miniwin/widgets/window.h>

namespace miniwin {
class File {
public:
	static String OpenFileDialog(
		Window* parent,
		const String& capacity = "Open File",
		const String& dir = {},
		const String& filter = "All Files (*.*)",
		String* selected_filter = nullptr);
};
}