#include <miniwin/widgets/frame.h>

#include <miniwin/core/imgui.h>

#include <miniwin/tools/scope_variable.h>

namespace miniwin {
class Frame::Impl {
public:
	Impl(Frame* owner) : owner_(owner) {}

	Frame* owner_;
	ScopeVariable<Vector2D> size_sc_;
};

Frame::Frame() {}

Vector2D Frame::Size() const {
	return impl_->size_sc_.cur_value();
}

void Frame::SetSize(const Vector2D& size) {
	impl_->size_sc_.SetControl(size);
}

void Frame::PaintBegin(size_t index) {
	AbstractControl::PaintBegin(index);

	impl_->size_sc_.Enter();
	if (impl_->size_sc_.HasChange()) {
		OnSizeChanged(impl_->size_sc_.cur_value(), impl_->size_sc_.prev_value());
	}

	imgui::BeginChild(Id(), impl_->size_sc_.cur_value());

	auto cur_size = imgui::GetWindowSize();
	if (cur_size != impl_->size_sc_.cur_value()) {
		// 第一次更新前的大小都是属于预测，这里不发送更改信号
		if (IsUpdated()) {
			OnSizeChanged(cur_size, impl_->size_sc_.cur_value());
		}
		impl_->size_sc_.SetValueDirectly(cur_size);
	}
}

void Frame::PaintEnd(size_t index) {
	imgui::EndChild();

	impl_->size_sc_.Exit();
	AbstractControl::PaintEnd(index);
}
}
