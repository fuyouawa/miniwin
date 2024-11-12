#include <miniwin/core/application.h>
#include <miniwin/widgets/window.h>

#include <miniwin/model/standard_item_model.h>
#include <miniwin/widgets/combobox.h>
#include <miniwin/widgets/textedit.h>
#include <miniwin/widgets/view/tableview.h>
#include <miniwin/widgets/label.h>
#include <miniwin/widgets/layout/boxlayout.h>
#include <miniwin/widgets/view/listview.h>

#include "miniwin/core/imgui.h"
#include "miniwin/tools/file.h"
#include "miniwin/widgets/button.h"
#include "miniwin/widgets/checkbox.h"
#include "miniwin/widgets/dialog.h"

using namespace miniwin;

class ExampleWindow : public Window {
public:
	ExampleWindow(const String& title){
		SetTitle(title);
		btn_open_file_ = new Button(this, "打开文件");

		Connect(btn_open_file_, &Button::OnClicked, this, [this]() {
			File::OpenFileDialog(this);
			});

		btn_open_dialog_ = new Button(this, "打开对话框");
		dialog_ = new Dialog(this);

		Connect(btn_open_dialog_, &Button::OnClicked, this, [this]() {
			dialog_->Open();
			});
	}

	Button* btn_open_file_;
	Button* btn_open_dialog_;
	Dialog* dialog_;
};

int main() {
	Application app;
	app.SetHideMainWindow(true);
	auto window = new ExampleWindow{"Example Window"};
	window->SetSize({ 600, 400 });
	window->CenterWindow();
	app.Execute();
}
