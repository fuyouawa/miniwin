#include <fugui/core/application.h>

#include <fugui/widgets/widget/window.h>

class ExampleWindow : public fugui::Window
{
public:
	ExampleWindow(AbstractWindow* parent, const std::u8string_view& title, bool show)
		: Window(parent, title, show)
	{
	}
};

int main() {
	fugui::Application app;

	ExampleWindow window{ nullptr, u8"Example Window", true };

	app.Execute(u8"Fugui Example App");
}