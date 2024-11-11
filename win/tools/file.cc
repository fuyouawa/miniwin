#include <miniwin/tools/file.h>

#include <Windows.h>
#include <miniwin/tools/stringlist.h>
#include <miniwin/tools/regex.h>

namespace miniwin {
String File::OpenFileDialog(Window* parent, const String& capacity, const String& dir, const String& filter,
	String* selected_filter)
{
	String windows_filter;

	auto filters = filter.Split(";;");
	for (auto& f : filters) {
		Regex r(R"((.+)\s*\((.+)\))");
		auto m = r.Match(f);
		if (m.HasMatch()) {
			auto desc = m.Captured(1);
			auto ext = m.Captured(2);

			windows_filter += desc + '\0' + ext.Replace(" ", ";") + '\0';
		}
	}

	OPENFILENAMEA ofn;

	char file[MAX_PATH]{ 0 };
	ZeroMemory(&ofn, sizeof(ofn));
	if (parent) {
		ofn.hwndOwner = reinterpret_cast<HWND>(parent->PlatformHandle());
	}
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = file;
	ofn.nMaxFile = sizeof(file);
	ofn.lpstrFilter = windows_filter.data();
	ofn.lpstrTitle = capacity.data();
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&ofn)) {
		if (selected_filter)
			*selected_filter = filters[ofn.nFilterIndex == 0 ? 0 : ofn.nFilterIndex - 1];
		return ofn.lpstrFile;
	}
	return {};
}
}
