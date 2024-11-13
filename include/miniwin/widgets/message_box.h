#pragma once
#include <miniwin/widgets/dialog.h>

namespace miniwin {
class MessageBox : public Dialog {
public:
	MessageBox(Widget* parent = nullptr, const String& title = "MessageBox");
};
}