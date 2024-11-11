#pragma once
#include <functional>
#include <memory>

#include <miniwin/tools/macro.h>

namespace miniwin {
class Object;

namespace internal {
class SlotArgsStoreBase {
public:
	virtual ~SlotArgsStoreBase() = default;
};

using SlotArgsStoreSharedPtr = std::shared_ptr<SlotArgsStoreBase>;

class SlotObjectBase {
public:
	virtual ~SlotObjectBase() = default;

	virtual void Call(const Object* receiver, const SlotArgsStoreBase* args_store) const = 0;
	virtual bool Compare(const SlotObjectBase* x) const = 0;
};

using SlotObjectPtr = std::unique_ptr<SlotObjectBase>;

template <class... Args>
class SlotArgsStore : public SlotArgsStoreBase {
public:
	explicit SlotArgsStore(Args&&... args): args_(std::forward<Args>(args)...) {}

	std::tuple<Args...> args_;
};

template <class Func, class Receiver, class... Args>
class MemberSlotObject : public SlotObjectBase {
public:
	explicit MemberSlotObject(Func func) : func_(func) {}

	void Call(const Object* receiver, const SlotArgsStoreBase* args_store) const override {
		auto store = dynamic_cast<const SlotArgsStore<Args...>*>(args_store);
		auto r = dynamic_cast<const Receiver*>(receiver);

		std::apply([r, this](const Args&... args) { std::invoke(func_, r, args...); }, store->args_);
	}

	bool Compare(const SlotObjectBase* x) const override {
		auto xx = dynamic_cast<const MemberSlotObject*>(x);
		return xx != nullptr && xx->func_ == func_;
	}

	Func func_;
};

template <class... Args>
class FunctorSlotObject : public SlotObjectBase {
public:
	using Func = std::function<void(Args...)>;

	FunctorSlotObject(const Func& func) : func_(func) {}
	FunctorSlotObject(Func&& func) : func_(std::move(func)) {}

	void Call(const Object* receiver, const SlotArgsStoreBase* args_store) const override {
		auto store = dynamic_cast<const SlotArgsStore<Args...>*>(args_store);
		std::apply(func_, store->args_);
	}

	bool Compare(const SlotObjectBase* x) const override {
		auto xx = dynamic_cast<const FunctorSlotObject*>(x);
		if (xx == nullptr
			|| !!xx->func_ != !!func_
			|| xx->func_.target_type() != func_.target_type())
			return false;

		if (auto t1 = xx->func_.template target<void(*)(Args...)>()) {
			auto t2 = func_.template target<void(*)(Args...)>();
			return t2 && *t1 == *t2;
		}
		return false;
	}

	Func func_;
};
} //namespace internal

enum class InvokeType {
	/**
	 * 如果非UI对象，则直接调用。
	 * 如果是UI对象，并且调用方也在UI线程，则直接调用；反之如果调用方不在UI线程，则加入UI调用队列。（如果程序还没初始化，则都加入队列）
	 */
	kAuto,
	/**
	 * 直接调用。
	 */
	kDirect,
	/**
	 * 如果非UI对象，则直接调用。
	 * 如果是UI对象，会加入UI调用队列。
	 */
	kQueued
};

enum class ConnectionFlags {
	kNone = 0,
	kUnique = 1 << 0, // 如果连接已存在, 将失败
	kReplace = 1 << 1, // 如果连接已存在, 替换已有连接
	kSingle = 1 << 2 // 仅被调用一次, 发出信号时, 连接将自动断开
};

ConnectionFlags operator|(ConnectionFlags x, ConnectionFlags y);
ConnectionFlags operator&(ConnectionFlags x, ConnectionFlags y);

template <class T>
using PureType = std::remove_cvref_t<std::remove_pointer_t<T>>;

#define _MW_COMMON_IF_TRUE ,

#define _MW_SIGNAL_ARGS_DECL_IMPL(i, ...) \
    META_UNPACK(META_INDEX(i, __VA_ARGS__)) \
    META_NOT_IF(META_INDEX_IS_END(i, __VA_ARGS__), _MW_COMMON_IF_TRUE)

#define _MW_SIGNAL_ARGS_DECL(...) \
    META_FOR(_MW_SIGNAL_ARGS_DECL_IMPL, 0, META_COUNT(__VA_ARGS__), __VA_ARGS__)

#define _MW_SIGNAL_NO_ARGS(name)                       \
public:                                                \
    void name() const {                                \
        EmitSignal(&PureType<decltype(this)>::name);   \
    }
#define _MW_SIGNAL_HAS_ARGS(name, ...)                             \
public:                                                            \
    void name(_MW_SIGNAL_ARGS_DECL(__VA_ARGS__)) const {           \
        EmitSignal(&PureType<decltype(this)>::name, __VA_ARGS__);  \
    }
#define _MW_SIGNAL(name, ...) \
    META_IF_ELSE(META_IS_EMPTY(__VA_ARGS__), _MW_SIGNAL_NO_ARGS(name), _MW_SIGNAL_HAS_ARGS(name, __VA_ARGS__))
}
