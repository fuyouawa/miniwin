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
