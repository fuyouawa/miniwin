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
        text_ = new miniwin::Text(this, u8"jʿ���jbb");
        input_text_ = new miniwin::InputText(this, u8"6665", u8"fffff");
        table_view_ = new miniwin::TableView(this, u8"114514");

        // ʵ����һ��Model
        auto model = new miniwin::StandardItemModel(table_view_);
        // �����е�����
        model->SetColumnCount(4);
        // ����ˮƽͷ��(Ҳ������ͷ)���ı�
        model->SetHorizontalHeaderTexts({ u8"asd", u8"�ط�", u8"ooo", u8"��������" });
        // �����е�����
        model->SetRowCount(3);
        // �������ı�
        model->SetRowTexts(0, 0, { u8"asdd", u8"���մ�" });
        model->SetColumnTexts(0, 3, { u8"�ϵ»�", u8"sd���ܴ���", u8"a�ķ���" });
        // ��model���ø�TableView
        table_view_->SetModel(model);

        // ��ȡѡ��model
        auto selection_model = table_view_->SelectionModel();
        // ����1��2��ѡ��
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
