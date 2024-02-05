#include <mvcgui/widgets/widget/mainwindow.h>
#include <mvcgui/core/application.h>

namespace mvcgui {
MainWindow::MainWindow(std::u8string_view title, bool show)
	: Window{ nullptr, title, show }
{
	widget_type_ = Type::kMainWindow;
}

void MainWindow::OnPaintBegin() {
	Window::OnPaintBegin();


}

void MainWindow::OnPaintEnd() {


	Window::OnPaintEnd();
}
}