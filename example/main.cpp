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
	ExampleWindow() {}

	void Awake() override {
		Window::Awake();

		auto self = shared_from_this();

		label_ = Instantiate<Label>(self);
		label_->SetText("输入文本");
		text_edit_ = Instantiate<TextEdit>(self);
		text_edit_->SetPlainText("初始文本");

		layout_ = Instantiate<HBoxLayout>(self);
		
		layout_->AddWidget(label_);
		layout_->AddWidget(text_edit_);

		btn_ = Instantiate<Button>(self);
		btn_->SetText("将文本值应用窗体");
		Connect(btn_, &Button::OnClicked, self, [this]() {
			SetTitle(text_edit_->PlainText());
			});

		combo_box_ = Instantiate<ComboBox>(self);
		combo_box_->SetText("组合框");
		combo_box_->AddItems({ "abc", "123", "[];" });
	}

	std::shared_ptr<Label> label_;
	std::shared_ptr<TextEdit> text_edit_;
	std::shared_ptr<HBoxLayout> layout_;
	std::shared_ptr<Button> btn_;
	std::shared_ptr<ComboBox> combo_box_;
	std::shared_ptr<ListView> list_;
};

int main() {
	Application app;
	app.SetHideMainWindow(true);
	auto window = Instantiate<ExampleWindow>(nullptr);
	window->SetTitle("示例窗体");
	window->SetSize({ 600, 400 });
	window->CenterWindow();
	window->Show();

	app.Execute();
}
