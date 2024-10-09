#include <fugui/core/object.h>
#include <cassert>
#include <fugui/core/signal.h>

#include <gui/tools/algorithm.h>

namespace fugui {
Object::Object()
	: owner_thread_id_{ std::this_thread::get_id() },
	is_destroyed_{ false }
{
}

Object::~Object() {
	if (!is_destroyed_) {
		Destroy();
	}
}

bool Object::IsInOwnerThread() const {
	return std::this_thread::get_id() == owner_thread_id_;
}

void Object::Invoke(Functor&& func, InvokeType type) const {
	assert(type != InvokeType::kQueued);
	func();
}

void Object::Destroy()
{
	assert(!is_destroyed_);
	Emit(on_destroy_);
	for (auto& signal : auto_disconnect_signal_queue_) {
		signal->DisConnect(this);
	}
	auto_disconnect_signal_queue_.clear();
	is_destroyed_ = true;
}

bool Object::is_closed() const {
	return is_destroyed_;
}

ConnectedSignal::ConnectedSignal(Object* receiver, SignalBase* signal)
	: receiver_{ receiver },
	signal_{ signal }
{
}

void ConnectedSignal::AutoDisConnect() {
	assert(!receiver_->is_destroyed_);
	assert(!IsContainer(receiver_->auto_disconnect_signal_queue_, signal_));
	receiver_->auto_disconnect_signal_queue_.push_back(signal_);
}
}