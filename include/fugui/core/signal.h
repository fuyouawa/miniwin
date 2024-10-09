#pragma once
#include <unordered_map>
#include <functional>
#include <fugui/core/base/abstract_object.h>
#include <assert.h>
#include <shared_mutex>
#include <fugui/tools/property.h>

namespace fugui {
class Object;

class SignalBase : NonCopyMoveable
{
public:
	virtual ~SignalBase() = default;

protected:
	friend class Object;
	virtual void DisConnect(const AbstractObject* const receiver) = 0;
};

template<typename... Args>
class Signal : public SignalBase
{
	friend class Object;
public:
	using Slot = std::function<void(Args...)>;
	Signal() = default;

protected:
	using SlotMap = std::unordered_map<const AbstractObject*, std::pair<Slot, InvokeType>>;

	void Connect(const AbstractObject* const receiver,
		Slot&& slot,
		ConnectionType conn_type,
		InvokeType invoke_type)
	{
		typename SlotMap::mapped_type slot_mapped{ std::move(slot), invoke_type };
		std::lock_guard<std::shared_mutex> lk{slots_mutex_};
		switch (conn_type)
		{
		case ConnectionType::kUnique:
		{
		insert:
			auto [_, suc] = slots_.insert({ receiver, std::move(slot_mapped) });
			assert(suc);
			break;
		}
		case ConnectionType::kReplace:
			slots_.insert_or_assign(receiver, std::move(slot_mapped));
			break;
		case ConnectionType::kSingle:
			slots_.clear();
			goto insert;
		default:
			assert(false);
			break;
		}
	}

	template<typename... Args2>
	void Emit(const AbstractObject* const sender, Args2&&... args) {
		std::shared_lock<std::shared_mutex> lk{slots_mutex_};
		for (auto [receiver, slot] : slots_) {
			receiver->Invoke([slot, args_tuple = std::tuple{ std::forward<Args2>(args)... }]() {
				std::apply([&](auto&&... captured_args) {
					slot.first(std::forward<decltype(captured_args)>(captured_args)...);
				}, args_tuple);
			}, slot.second);
		}
	}

	void DisConnect(const AbstractObject* const receiver) override {
		std::lock_guard<std::shared_mutex> lk{slots_mutex_};
		auto res = slots_.erase(receiver); assert(res > 0);
	}

	std::shared_mutex slots_mutex_;
	SlotMap slots_;
};
}