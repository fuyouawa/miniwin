#include <miniwin/core/application.h>
#include <miniwin/widgets/window.h>

#include "miniwin/model/standard_item_model.h"
#include "miniwin/widgets/combobox.h"
#include "miniwin/widgets/textedit.h"
#include "miniwin/widgets/tableview.h"
#include "miniwin/widgets/label.h"

class ExampleWindow : public miniwin::Window
{
public:
	ExampleWindow(const std::u8string_view& title)
		: Window(title)
	{
        label_ = new miniwin::Label(this, u8"j士大夫jbb");
        text_edit_ = new miniwin::TextEdit(this, u8"6665", u8"fffff");
        table_view_ = new miniwin::TableView(this);

        // 实例化一个Model
        auto model = new miniwin::StandardItemModel(table_view_);
        // 设置列的数量
        model->SetColumnCount(4);
        // 设置水平头部(也就是列头)的文本
        model->SetHorizontalHeaderTexts({ u8"asd", u8"地方", u8"ooo", u8"世世代代" });
        // 设置行的数量
        model->SetRowCount(3);
        // 设置行文本
        model->SetRowTexts(0, 0, { u8"asdd", u8"大苏打·" });
        model->SetColumnTexts(0, 3, { u8"肯德基", u8"sd限塑袋·", u8"a的肥肉" });
        // 将model设置给TableView
        table_view_->SetModel(model);

        // 获取选择model
        auto selection_model = table_view_->SelectionModel();
        // 设置1行2列选中
        selection_model->Select(0, 1);

        combobox_ = new miniwin::ComboBox(this, u8"ComboBox");
        combobox_->AddItems({ u8"啥啥啥", u8"dff单独", u8"ff当我" });
	}

    miniwin::Label* label_;
    miniwin::TextEdit* text_edit_;
    miniwin::TableView* table_view_;
    miniwin::ComboBox* combobox_;
};


int main() {
	miniwin::Application app;
    app.SetHideMainWindow(true);

	auto window = new ExampleWindow{ u8"Example Window" };

	app.Execute();
}
