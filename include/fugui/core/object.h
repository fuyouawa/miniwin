#pragma once
#include <memory>
#include <thread>
#include <unordered_set>
#include <fugui/tools/container.h>
#include <fugui/core/signal.h>

namespace fugui {
class Object;

class ConnectedSignal : NonCopyMoveable
{
public:
	ConnectedSignal(Object* receiver, SignalBase* signal);

	void AutoDisConnect();

private:
	Object* receiver_;
	SignalBase* signal_;
};


class Object : public AbstractObject
{
	friend class ConnectedSignal;
public:
	Object();
	~Object();

	virtual void Destroy();

	bool is_closed() const;

	template<std::derived_from<Object> T>
	auto as() {
		return dynamic_cast<T*>(this);
	}

	template<typename... Args>
	ConnectedSignal Connect(
		Signal<Args...>& signal,
		typename Signal<Args...>::Slot&& slot,
		ConnectionType conn_type = ConnectionType::kUnique,
		InvokeType invoke_type = InvokeType::kAuto)
	{
		signal.Connect(this, std::move(slot), conn_type, invoke_type);
		return { this, &signal };
	}

	template<typename... Args, typename... Args2>
	void Emit(Signal<Args...>& signal, Args2&&... args) const {
		signal.Emit(this, std::forward<Args2>(args)...);
	}

	template<typename... Args>
	void DisConnect(Signal<Args...>& signal) const {
		signal.DisConnect(this);
	}

	bool IsInOwnerThread() const;
	void Invoke(Functor&& func, InvokeType type = InvokeType::kAuto) const override;

	Signal<> on_destroy_;

protected:
	std::thread::id owner_thread_id_;

	bool is_destroyed_;

private:
	std::vector<SignalBase*> auto_disconnect_signal_queue_;
};

template<std::derived_from<Object> T, typename... Args>
std::shared_ptr<T> Instantiate(Args&&... args) {
	return std::make_shared<T>(std::forward<Args>(args)...);
}
}