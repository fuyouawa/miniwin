#include <fugui/core/application.h>
#include <fugui/widgets/window.h>

#include "fugui/widgets/input_text.h"
#include "fugui/widgets/text.h"

class ExampleWindow : public fugui::Window
{
public:
	ExampleWindow(const std::u8string_view& title, bool show)
		: Window(title, show)
	{
        text_ = new fugui::Text(this, u8"jjbb");
        input_text_ = new fugui::InputText(this, u8"6665", u8"fffff");
	}

    fugui::Text* text_;
    fugui::InputText* input_text_;
};

int main() {
	fugui::Application app;

	auto window = new ExampleWindow{ u8"Example Window", true };

	app.Execute(u8"FuGui Example App");
}
