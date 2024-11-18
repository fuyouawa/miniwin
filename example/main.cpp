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
#include "miniwin/widgets/list_widget.h"
#include "miniwin/widgets/message_box.h"

using namespace miniwin;

class ExampleWindow : public Window {
public:
	ExampleWindow() {}

	void Awake() override {
		Window::Awake();

		auto self = shared_from_this();

		label_ = Instantiate<Label>(self);
		text_edit_ = Instantiate<TextEdit>(self);
		layout_ = Instantiate<HBoxLayout>(self);
		btn_ = Instantiate<Button>(self);
		combo_box_ = Instantiate<ComboBox>(self);
		list_ = Instantiate<ListWidget>(self);
		table_ = Instantiate<TableView>(self);
		table_model_ = Instantiate<StandardItemModel>(self);
		table_->SetModel(table_model_);
	}

	void Start() override {
		Window::Start();

		label_->SetText("输入文本");
		text_edit_->SetPlainText("初始文本");

		layout_->AddWidget(label_);
		layout_->AddWidget(text_edit_);

		btn_->SetText("将文本值应用窗体");
		combo_box_->SetText("组合框");
		combo_box_->AddItems({"abc", "123", "[];"});
		
		list_->SetRightLabel("列表");
		list_->AddItems({"qwe", "ert", "yui", "tii"});
		list_->SetHeight(100);

		table_model_->SetColumnCount(4);
		table_model_->SetRowCount(5);
		table_model_->SetHorizontalHeaderTexts({ "头0", "头1", "头2" , "头3" });
		table_model_->SetRowTexts(0, 0, { "行0-0", "行0-1", "行0-2" });
		table_model_->SetRowTexts(3, 0, { "行3-0", "行3-1", "行3-2" });
		table_model_->SetColumnTexts(0, 3, { "列3-0", "列3-1","列3-2","列3-3","列3-4", });

		Connect(btn_, &Button::OnClicked, shared_from_this(), [this]() {
			SetTitle(text_edit_->PlainText());
		});
	}

	std::shared_ptr<Label> label_;
	std::shared_ptr<TextEdit> text_edit_;
	std::shared_ptr<HBoxLayout> layout_;
	std::shared_ptr<Button> btn_;
	std::shared_ptr<ComboBox> combo_box_;
	std::shared_ptr<ListWidget> list_;
	std::shared_ptr<TableView> table_;
	std::shared_ptr<StandardItemModel> table_model_;
};

int main() {
	Application app;
	app.SetHideMainWindow(true);
	auto window = Instantiate<ExampleWindow>(nullptr);
	window->SetTitle("示例窗体");
	window->SetSize({600, 400});
	window->CenterWindow();
	window->Show();

	app.Execute();
}
