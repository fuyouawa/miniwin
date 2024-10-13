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
	}
};

int main() {
	fugui::Application app;

	auto window = new ExampleWindow{ u8"Example Window", true };

	app.Execute(u8"FuGui Example App");
}
