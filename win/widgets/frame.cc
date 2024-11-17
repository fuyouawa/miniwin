#include <miniwin/widgets/frame.h>

#include <miniwin/core/imgui.h>

namespace miniwin {
class Frame::Impl {
public:
	Impl(Frame* owner) : owner_(owner) {}

	Frame* owner_;
};

Frame::Frame() {}

void Frame::PaintBegin() {
	AbstractControl::PaintBegin();
	imgui::BeginChildWindow(Id(), Size());
}

void Frame::PaintEnd() {
	imgui::EndChildWindow();
	AbstractControl::PaintEnd();
}
}
