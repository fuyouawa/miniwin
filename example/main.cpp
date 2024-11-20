#include <iostream>
#include <miniwin/core/application.h>
#include <miniwin/widgets/window.h>

#include <miniwin/model/standard_item_model.h>
#include <miniwin/widgets/combobox.h>
#include <miniwin/widgets/text_edit.h>
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
#include "miniwin/widgets/number_edit.h"

using namespace miniwin;

class ExampleWindow : public Window {
	MW_OBJECT
public:
	ExampleWindow() {}

	// Awake，在对象实例化时调用
	void Awake() override {
		Window::Awake();
		auto self = shared_from_this();
		// 实例化
		label_ = Instantiate<Label>(self);
		text_edit_ = Instantiate<TextEdit>(self);
		layout_ = Instantiate<HBoxLayout>(self);
		btn_ = Instantiate<Button>(self);
		btn2_ = Instantiate<Button>(self);
		btn3_ = Instantiate<Button>(self);
		layout2_ = Instantiate<HBoxLayout>(self);
		combo_box_ = Instantiate<ComboBox>(self);
		list_ = Instantiate<ListWidget>(self);
		table_ = Instantiate<TableView>(self);
		table_model_ = Instantiate<StandardItemModel>(self);
		check_box_ = Instantiate<CheckBox>(self);
		table_->SetModel(table_model_);

		number_edit_ = Instantiate<NumberEdit>(self);
	}

	// Start，在对象绘制前调用，只会调用一次
	void Start() override {
		Window::Start();

		// 设置标签和文本输入框的初始文本
		label_->SetText("输入文本");
		text_edit_->SetPlainText("初始文本");

		// 将标签和文本输入框水平布局
		// layout_->AddWidget(label_);
		// layout_->AddWidget(text_edit_);

		// 设置按钮文本
		btn_->SetText("将文本值应用窗体");
		check_box_->SetText("复选框");

		// 设置组合框文本和数据
		combo_box_->SetText("组合框");
		combo_box_->SetWidth(100);
		combo_box_->AddItems({ "abc", "123", "[];" });

		// 设置列表数据
		list_->SetRightLabel("列表");
		list_->AddItems({ "qwe", "ert", "yui", "tii" });
		list_->SetHeight(100);

		// 设置表格模型的数据
		table_model_->SetColumnCount(4);
		table_model_->SetRowCount(5);
		table_model_->SetHorizontalHeaderTexts({ "头0", "头1", "头2", "头3" });					// 设置表头
		table_model_->SetRowTexts(0, 0, { "行0-0", "行0-1", "行0-2" });							// 设置第一行中三列文本
		table_model_->SetRowTexts(3, 0, { "行3-0", "行3-1", "行3-2" });							// 设置第四行中三列文本
		table_model_->SetColumnTexts(0, 3, { "列3-0", "列3-1", "列3-2", "列3-3", "列3-4", });// 设置第四列的五行文本

		auto self = shared_from_this();

		// 连接按钮的点击信号，槽函数里面修改窗体标题
		Connect(btn_, &Button::OnClicked, self, [this]() {
			SetTitle(text_edit_->PlainText());
			});

		Connect(check_box_, &CheckBox::OnToggled, self, [](bool toggle) {
			std::cout << "复选框被点击了：" << toggle << std::endl;
			});

		btn2_->SetText("打开资源管理器选择文件");
		Connect(btn2_, &Button::OnClicked, self, [this]() {
			FileDialog::GetOpenFileNameAsync(shared_from_this(), "选择文件", [](String filename, String _) {
				std::cout << "选择的文件是：" << filename.ToStdString() << std::endl;
				});
			});

		btn3_->SetText("打开询问框");
		Connect(btn3_, &Button::OnClicked, self, [this]() {
			MessageBox::QuestionAsync(shared_from_this(), "询问", "我是一个询问框？", "是的", "确实", [](bool is_yes) {
				std::cout << "询问框的选择是：" << is_yes << std::endl;
				});
			});

		layout2_->AddWidget(combo_box_);
		layout2_->SetAdditionSpacing(combo_box_, 10);
		layout2_->AddWidget(btn2_);
		layout2_->AddWidget(btn3_);
		layout2_->SetAlignment(0.5f);	// 设置居中


		Connect(text_edit_, &TextEdit::OnTextChanged, self, [this]() {
			std::wcout << "文本改变了" << std::endl;
			});

		number_edit_->SetRightLabel("只能输入16进制");
		number_edit_->SetBase(16);
		number_edit_->SetNumber(0x114514);
		number_edit_->SetMaxNumber(0x1919810);
	}

	std::shared_ptr<Label> label_;
	std::shared_ptr<TextEdit> text_edit_;
	std::shared_ptr<CheckBox> check_box_;
	std::shared_ptr<HBoxLayout> layout_;
	std::shared_ptr<Button> btn_;
	std::shared_ptr<Button> btn2_;
	std::shared_ptr<Button> btn3_;
	std::shared_ptr<HBoxLayout> layout2_;
	std::shared_ptr<ComboBox> combo_box_;
	std::shared_ptr<ListWidget> list_;
	std::shared_ptr<TableView> table_;
	std::shared_ptr<StandardItemModel> table_model_;
	std::shared_ptr<NumberEdit> number_edit_;
};

int main() {
	Application app;				// 实例化一个app对象，用于配置窗体等
	app.SetHideMainWindow(true);	// 隐藏主窗体
	app.EnabledIniFile(false);		// 关闭缓存文件
	// 实例化示例窗体
	auto window = Instantiate<ExampleWindow>(nullptr);
	window->SetTitle("示例窗体");	// 设置标题
	window->SetSize({600, 400});	// 设置大小
	window->CenterInScene();		// 设置窗体在屏幕居中
	window->Show();					// 显示窗体
	
	app.Execute();					// 开始运行
}

// 未来某一时刻服务器下发了个id为114514，内含1.1f和false两个数据
// 然后转发给所有注册了114514 id的接收器