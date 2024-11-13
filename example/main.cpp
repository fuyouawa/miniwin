#include <iostream>
#include <miniwin/core/application.h>
#include <miniwin/widgets/window.h>

#include <miniwin/model/standard_item_model.h>
#include <miniwin/widgets/combobox.h>
#include <miniwin/widgets/textedit.h>
#include <miniwin/widgets/view/table_view.h>
#include <miniwin/widgets/label.h>
#include <miniwin/widgets/layout/box_layout.h>
#include <miniwin/widgets/view/list_view.h>

#include "miniwin/core/imgui.h"
#include "miniwin/tools/file.h"
#include "miniwin/widgets/button.h"
#include "miniwin/widgets/checkbox.h"
#include "miniwin/widgets/dialog.h"
#include "miniwin/widgets/file_dialog.h"
#include "miniwin/widgets/message_box.h"

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
		dialog_ = new Dialog(this, "对话框");

		Connect(btn_open_dialog_, &Button::OnClicked, this, [this]() {
			dialog_->Open();
			});

		btn_open_msgbox_ = new Button(this, "打开消息框");

		Connect(btn_open_msgbox_, &Button::OnClicked, this, [this]() {
			MessageBox::InformationAsync(this, "提示", "这是一个消息框！", "确认", []() {
				std::cout << "消息框被确认了" << std::endl;
				});
			});

		btn_open_msgbox2_ = new Button(this, "打开询问框");

		Connect(btn_open_msgbox2_, &Button::OnClicked, this, [this]() {
			MessageBox::QuestionAsync(this, "询问", "这是一个询问框？", "是的", "不是", [](bool yes) {
				std::cout << "询问框被确认了:" << yes << std::endl;
				});
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
	Button* btn_open_msgbox_;
	Button* btn_open_msgbox2_;
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
