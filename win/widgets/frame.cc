#include <miniwin/widgets/frame.h>

#include <miniwin/core/imgui.h>

namespace miniwin {
class Frame::Impl {
public:
	Impl(Frame* owner) : owner_(owner) {}

	Frame* owner_;
};

Frame::Frame() {}

void Frame::PaintBegin(size_t index) {
	AbstractMinimumControl::PaintBegin(index);
	imgui::BeginChildWindow(Id(), Size());
}

void Frame::PaintEnd(size_t index) {
	imgui::EndChildWindow();
	AbstractMinimumControl::PaintEnd(index);
}
}
