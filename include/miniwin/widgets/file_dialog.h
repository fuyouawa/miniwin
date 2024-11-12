#pragma once
#include <miniwin/widgets/dialog.h>

namespace miniwin {
class FileDialog : Dialog {
public:
	using GetOpenFileNameCallback = std::function<void(String filename, String selected_filter)>;

	static void GetOpenFileNameAsync(
		Window* parent,
		const String& capacity,
		GetOpenFileNameCallback callback = {},
		const String& dir = {},
		const String& filter = "All Files (*.*)");

	struct Config {
		Window* parent;
		String directory;
		String filter;
		std::function<void(FileDialog* dlg)> selected_callback;
	};

	FileDialog(const Config& cfg);
	~FileDialog() override;

	Config& GetConfig() const;

	bool IsSelectionCompleted() const;

	String SelectedFilter() const;
	String SelectedFileName() const;

protected:
	void OnPaintWindowBegin() override;

	_MW_IMPL
};
}