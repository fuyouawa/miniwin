#include <miniwin/core/application.h>
#include <miniwin/widgets/window.h>

#include "miniwin/model/standard_item_model.h"
#include "miniwin/widgets/input_text.h"
#include "miniwin/widgets/table_view.h"
#include "miniwin/widgets/text.h"

class ExampleWindow : public miniwin::Window
{
public:
	ExampleWindow(const std::u8string_view& title, bool show)
		: Window(title)
	{
        text_ = new miniwin::Text(this, u8"j士大夫jbb");
        input_text_ = new miniwin::InputText(this, u8"6665", u8"fffff");
        table_view_ = new miniwin::TableView(this, u8"114514");

        // 实例化一个Model
        auto model = new miniwin::StandardItemModel(table_view_);
        // 设置列的数量
        model->SetColumnCount(4);
        // 设置水平头部(也就是列头)的文本
        model->SetHeaderText(0, miniwin::Orientation::Horizontal, u8"测试1");
        model->SetHeaderText(1, miniwin::Orientation::Horizontal, u8"测试2");
        model->SetHeaderText(2, miniwin::Orientation::Horizontal, u8"测试3");
        model->SetHeaderText(3, miniwin::Orientation::Horizontal, u8"测试4");
        // 设置行的数量
        model->SetRowCount(3);
        // 设置行文本
        model->SetText({ 0, 0 }, u8"yi的是");
        model->SetText({ 0, 1 }, u8"yi的是sss");
        model->SetText({ 0, 2 }, u8"yi是sss");
        model->SetText({ 0, 3 }, u8"yi的gh是sss");
        model->SetText({ 1, 1 }, u8"hg士大夫s");
        model->SetText({ 2, 2 }, u8"hg士dsd大夫s");
        // 将model设置给TableView
        table_view_->SetModel(model);

        // 获取选择model
        auto selection_model = table_view_->SelectionModel();
        // 设置1行2列选中
        selection_model->Select(0, 1);
	}

    miniwin::Text* text_;
    miniwin::InputText* input_text_;
    miniwin::TableView* table_view_;
};


int main() {
	miniwin::Application app;
    app.SetHideMainWindow(true);

	auto window = new ExampleWindow{ u8"Example Window", true };

	app.Execute();
}
