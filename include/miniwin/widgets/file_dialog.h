#pragma once
#include <miniwin/widgets/dialog.h>

namespace miniwin {
/**
 * 打开资源管理器选择文件的对话框
 *
 * 在Windows下使用GetOpenFileNameA的系统api
 *
 * 这里包装一个Dialog更多是为了阻塞父级窗体，所以是私有继承Dialog，仅公开部分可用函数
 */
class FileDialog : private Dialog {
public:
	using GetOpenFileNameCallback = std::function<void(String filename, String selected_filter)>;

	static void GetOpenFileNameAsync(
		Widget* parent,
		const String& title,
		GetOpenFileNameCallback callback = {},
		const String& dir = {},
		const String& filter = "All Files (*.*)");

	struct Config {
		Widget* parent;
		String directory;
		String filter;
		std::function<void(FileDialog* dlg)> selected_callback;
	};

	FileDialog(const Config& cfg, const String& title);
	~FileDialog() override;

	using Dialog::WidgetParent;
	using Dialog::SetWidgetParent;
	using Dialog::Title;
	using Dialog::SetTitle;
	using Dialog::Open;
	using Dialog::Invoke;

	Config& GetConfig() const;

	bool IsSelectionCompleted() const;

	String SelectedFilter() const;
	String SelectedFileName() const;

protected:
	void OnPaintWindowBegin() override;

	_MW_IMPL
};
}