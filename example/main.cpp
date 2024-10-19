#include <Windows.h>
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
        text_ = new miniwin::Text(this, u8"jÊ¿´ó·òjbb");
        input_text_ = new miniwin::InputText(this, u8"6665", u8"fffff");
        table_view_ = new miniwin::TableView(this, u8"114514");
        auto model = new miniwin::StandardItemModel(table_view_);
        model->SetColumnCount(4);
        model->SetHeaderText(0, miniwin::Orientation::Horizontal, u8"²âÊÔ1");
        model->SetHeaderText(1, miniwin::Orientation::Horizontal, u8"²âÊÔ2");
        model->SetHeaderText(2, miniwin::Orientation::Horizontal, u8"²âÊÔ3");
        model->SetHeaderText(3, miniwin::Orientation::Horizontal, u8"²âÊÔ4");
        table_view_->SetModel(model);
	}

    miniwin::Text* text_;
    miniwin::InputText* input_text_;
    miniwin::TableView* table_view_;
};


int main() {
	miniwin::Application app;

	auto window = new ExampleWindow{ u8"Example Window", true };

	app.Execute();
}
