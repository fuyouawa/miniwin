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
        label_ = new miniwin::Label(this, u8"jʿ���jbb");
        text_edit_ = new miniwin::TextEdit(this, u8"6665", u8"fffff");
        table_view_ = new miniwin::TableView(this);

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

        combobox_ = new miniwin::ComboBox(this, u8"ComboBox");
        combobox_->AddItems({ u8"ɶɶɶ", u8"dff����", u8"ff����" });
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
