#include <miniwin/core/application.h>
#include <miniwin/widgets/window.h>

#include <miniwin/model/standard_item_model.h>
#include <miniwin/widgets/combobox.h>
#include <miniwin/widgets/textedit.h>
#include <miniwin/widgets/view/tableview.h>
#include <miniwin/widgets/label.h>
#include <miniwin/widgets/layout/boxlayout.h>
#include <miniwin/widgets/view/listview.h>

class ExampleWindow : public miniwin::Window
{
public:
	ExampleWindow(const std::u8string_view& title)
		: Window(title)
	{
        label_ = new miniwin::Label(this, u8"jʿ���jbb");

        text_edit_label_ = new miniwin::Label(this, u8"TextEdit Label");
        text_edit_ = new miniwin::TextEdit(this, u8"fffff");

        box_layout_ = new miniwin::HBoxLayout(this);
        box_layout_->AddWidget(text_edit_label_);
        box_layout_->AddWidget(text_edit_);

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

    miniwin::HBoxLayout* box_layout_;
    miniwin::Label* label_;
    miniwin::Label* text_edit_label_;
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
