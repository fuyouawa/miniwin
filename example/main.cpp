#include <miniwin/core/application.h>
#include <miniwin/widgets/window.h>

#include <miniwin/model/standard_item_model.h>
#include <miniwin/widgets/combobox.h>
#include <miniwin/widgets/textedit.h>
#include <miniwin/widgets/view/tableview.h>
#include <miniwin/widgets/label.h>
#include <miniwin/widgets/layout/boxlayout.h>
#include <miniwin/widgets/view/listview.h>

#include "miniwin/widgets/button.h"
#include "miniwin/widgets/checkbox.h"

using namespace miniwin;

class ExampleWindow : public Window {
public:
	ExampleWindow(const String& title)
		: Window(title) {
		// label_ = new Label(this, "j士大夫jbb");
		//
		// text_edit_label_ = new Label(this, u8"TextEdit Label");
		text_edit_ = new TextEdit(this, "fffff");
		//
		// box_layout_ = new HBoxLayout(this);
		// box_layout_->AddWidget(text_edit_label_);
		// box_layout_->AddWidget(text_edit_);
		//
		table_view_ = new TableView(this);

		// 实例化一个Model
		auto model = new StandardItemModel(table_view_);
		// 设置列的数量
		model->SetColumnCount(4);
		// 设置水平头部(也就是列头)的文本
		model->SetHorizontalHeaderTexts({"asd", "地方", "ooo", "世世代代"});
		// 设置行的数量
		model->SetRowCount(3);
		// 设置行文本
		model->SetRowTexts(0, 0, {"asdd", "大苏打·"});
		model->SetColumnTexts(0, 3, {"肯德基", "sd限塑袋·", "a的肥肉"});
		// 将model设置给TableView
		table_view_->SetModel(model);
		//
		// // 获取选择model
		// auto selection_model = table_view_->SelectionModel();
		// // 设置1行2列选中
		// selection_model->Select(0, 1);
		//
		// combobox_ = new ComboBox(this, u8"ComboBox");
		// combobox_->AddItems({ u8"啥啥啥", u8"dff单独", u8"ff当我" });
		//
		// btn_ = new Button(this, "Btn");
		chkbox_ = new CheckBox(this, "234");
	}

	void OnClicked() const {}

	HBoxLayout* box_layout_;
	Label* label_;
	Label* text_edit_label_;
	TextEdit* text_edit_;
	CheckBox* chkbox_;
	TableView* table_view_;
	ComboBox* combobox_;
	Button* btn_;
};

int main() {
	Application app;
	app.SetHideMainWindow(true);
	auto window = new ExampleWindow{"Example Window"};
	app.Execute();
}
