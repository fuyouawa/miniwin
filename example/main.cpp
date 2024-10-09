#include <fugui/core/application.h>
#include <fugui/widgets/widget/window.h>

#include "fugui/model/standard_list_model.h"
#include "fugui/widgets/view/list_view.h"
#include "fugui/widgets/widget/input_text.h"
#include "fugui/widgets/widget/text.h"

class ExampleWindow : public fugui::Window
{
public:
	ExampleWindow(const std::u8string_view& title, bool show)
		: Window(nullptr, title, show),
		text_(this, u8"Example Text"),
		input_text_(this, u8"Example InputText"),
		list_view_(this, u8"Example List")
	{
		auto model = std::make_shared<fugui::StandardListModel>();

		model->InsertRows(0, 3);
		model->set_text(0, u8"List Item 1");
		model->set_text(1, u8"List Item 2");
		model->set_text(2, u8"List Item 3");

		list_view_.set_model(model);
	}

	fugui::Text text_;
	fugui::InputText input_text_;
	fugui::ListView list_view_;
};

int main() {
	fugui::Application app;

	ExampleWindow window{ u8"Example Window", true };

	app.Execute(u8"FuGui Example App");
}