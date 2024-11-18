#pragma once
#include <miniwin/widgets/dialog.h>

namespace miniwin {
/**
 * 打开资源管理器选择文件的对话框
 *
 * 在Windows下使用GetOpenFileNameA的系统api
 *
 * 这里包装一个Dialog更多是为了阻塞父级窗体，仅部分函数可用
 *
 * 可用函数:
 *
 * using Dialog::WidgetParent;
 *
 * using Dialog::SetWidgetParent;
 *
 * using Dialog::Title;
 *
 * using Dialog::SetTitle;
 *
 * using Dialog::Open;
 *
 * using Dialog::Invoke;
 */
class FileDialog : public Dialog {
	MW_OBJECT
public:
	using CallbackOfGetOpenFileName = std::function<void(String filename, String selected_filter)>;
	using SelectedFileCallback = std::function<void(const std::shared_ptr<FileDialog>& dlg)>;

	static void GetOpenFileNameAsync(
		const SharedWidget& parent,
		const String& title,
		CallbackOfGetOpenFileName callback = {},
		const String& dir = {},
		const String& filter = "All Files (*.*)");

	struct Config {
		WeakWidget parent;
		String directory;
		String filter;
		SelectedFileCallback selected_callback;
	};

	FileDialog();
	~FileDialog() override;

	Config& GetConfig() const;

	bool IsSelectionCompleted() const;

	String SelectedFilter() const;
	String SelectedFileName() const;

protected:
	void Awake() override;
	void OnPaintWindowBegin() override;

	_MW_IMPL
};
}
