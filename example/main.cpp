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

	void Initialize(const SharedObject& parent) override {
		Window::Initialize(parent);

		auto self = shared_from_this();

		label_ = Instantiate<Label>(self);
		text_edit_ = Instantiate<TextEdit>(self);
		layout_ = Instantiate<HBoxLayout>(self);
		btn_ = Instantiate<Button>(self);
		combo_box_ = Instantiate<ComboBox>(self);
		list_ = Instantiate<ListView>(self);
		list_model_ = Instantiate<StandardItemModel>(list_);

		Connect(btn_, &Button::OnClicked, self, [this]() {
			SetTitle(text_edit_->PlainText());
			});
	}

	void Awake() override {
		Window::Awake();

		label_->SetText("输入文本");
		text_edit_->SetPlainText("初始文本");

		
		layout_->AddWidget(label_);
		layout_->AddWidget(text_edit_);

		btn_->SetText("将文本值应用窗体");

		combo_box_->SetText("组合框");
		combo_box_->AddItems({ "abc", "123", "[];" });

		list_model_->SetColumnCount(1);
		list_model_->SetRowCount(4);
		list_model_->SetColumnTexts(0, 0, { "hfg", "yui", "lkj", "4435" });
		list_->SetModel(list_model_);
	}

	std::shared_ptr<Label> label_;
	std::shared_ptr<TextEdit> text_edit_;
	std::shared_ptr<HBoxLayout> layout_;
	std::shared_ptr<Button> btn_;
	std::shared_ptr<ComboBox> combo_box_;
	std::shared_ptr<ListView> list_;
	std::shared_ptr<StandardItemModel> list_model_;
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
