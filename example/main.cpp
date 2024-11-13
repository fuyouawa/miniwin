#include <iostream>
#include <miniwin/core/application.h>
#include <miniwin/widgets/window.h>

#include <miniwin/model/standard_item_model.h>
#include <miniwin/widgets/combobox.h>
#include <miniwin/widgets/textedit.h>
#include <miniwin/widgets/view/table_view.h>
#include <miniwin/widgets/label.h>
#include <miniwin/widgets/layout/boxlayout.h>
#include <miniwin/widgets/view/list_view.h>

#include "miniwin/core/imgui.h"
#include "miniwin/tools/file.h"
#include "miniwin/widgets/button.h"
#include "miniwin/widgets/checkbox.h"
#include "miniwin/widgets/dialog.h"
#include "miniwin/widgets/file_dialog.h"

using namespace miniwin;

class ExampleWindow : public Window {
public:
	ExampleWindow(const String& title) : Window(nullptr, title) {
		btn_open_file_ = new Button(this, "打开文件");

		Connect(btn_open_file_, &Button::OnClicked, this, [this]() {
			FileDialog::GetOpenFileNameAsync(this, "选择文件", [this](String filename, String _) {
				std::cout << filename.ToStdString() << std::endl;
			});
			});

		btn_open_dialog_ = new Button(this, "打开对话框");
		dialog_ = new Dialog(this);

		Connect(btn_open_dialog_, &Button::OnClicked, this, [this]() {
			dialog_->Open();
			});

		edit_title_to_set_ = new TextEdit(this, "示例窗体");
		btn_set_title_ = new Button(this, "修改窗体标题");
		layout_set_title_ = new HBoxLayout(this);

		layout_set_title_->AddWidget(edit_title_to_set_);
		layout_set_title_->AddWidget(btn_set_title_);

		Connect(btn_set_title_, &Button::OnClicked, this, [this]() {
			SetTitle(edit_title_to_set_->PlainText());
			});
	}

	Button* btn_open_file_;
	Button* btn_open_dialog_;
	Dialog* dialog_;
	Button* btn_set_title_;
	TextEdit* edit_title_to_set_;
	HBoxLayout* layout_set_title_;
};

int main() {
	Application app;
	app.SetHideMainWindow(true);
	auto window = new ExampleWindow{"示例窗体"};
	window->SetSize({ 600, 400 });
	window->CenterWindow();
	app.Execute();
}
