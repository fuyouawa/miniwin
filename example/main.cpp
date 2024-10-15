#include <miniwin/core/application.h>
#include <miniwin/widgets/window.h>

#include "miniwin/widgets/input_text.h"
#include "miniwin/widgets/text.h"

class ExampleWindow : public miniwin::Window
{
public:
	ExampleWindow(const std::u8string_view& title, bool show)
		: Window(title)
	{
        text_ = new miniwin::Text(this, u8"jjbb");
        input_text_ = new miniwin::InputText(this, u8"6665", u8"fffff");
	}

    miniwin::Text* text_;
    miniwin::InputText* input_text_;
};

int main() {
	miniwin::Application app;

	auto window = new ExampleWindow{ u8"Example Window", true };

	app.Execute(u8"FuGui Example App");
}
