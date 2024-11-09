#include <miniwin/core/application.h>
#include <miniwin/widgets/window.h>

#include <miniwin/model/standard_item_model.h>
#include <miniwin/widgets/combobox.h>
#include <miniwin/widgets/textedit.h>
#include <miniwin/widgets/view/tableview.h>
#include <miniwin/widgets/label.h>
#include <miniwin/widgets/layout/boxlayout.h>
#include <miniwin/widgets/view/listview.h>

#include <miniwin/tools/debug.h>

#include "miniwin/widgets/button.h"

using namespace miniwin;


class ExampleWindow : public Window
{
public:
	ExampleWindow(const String& title)
		: Window(title)
	{
        label_ = new Label(this, u8"jʿ���jbb");

        text_edit_label_ = new Label(this, u8"TextEdit Label");
        text_edit_ = new TextEdit(this, u8"fffff");

        box_layout_ = new HBoxLayout(this);
        box_layout_->AddWidget(text_edit_label_);
        box_layout_->AddWidget(text_edit_);

        table_view_ = new TableView(this);

        // ʵ����һ��Model
        auto model = new StandardItemModel(table_view_);
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

        combobox_ = new ComboBox(this, u8"ComboBox");
        combobox_->AddItems({ u8"ɶɶɶ", u8"dff����", u8"ff����" });

        btn_ = new Button(this, u8"Btn");

        Connect(btn_, &Button::OnClicked, this, []() {
            DebugOutput("1263");
            });
	}

    void OnClicked() const {
        DebugOutput("123");
	}

    HBoxLayout* box_layout_;
    Label* label_;
    Label* text_edit_label_;
    TextEdit* text_edit_;
    TableView* table_view_;
    ComboBox* combobox_;
    Button* btn_;
};

int main() {
	Application app;
    app.SetHideMainWindow(true);

	auto window = new ExampleWindow{ u8"Example Window" };
	app.Execute();
}
