#pragma once
#include <functional>
#include <memory>

#include <miniwin/defs.h>
#include <miniwin/tools/macro.h>
#include <miniwin/tools/list.h>

namespace miniwin {
class Object;

using SharedObject = std::shared_ptr<Object>;
using SharedConstObject = std::shared_ptr<const Object>;
using WeakObject = std::weak_ptr<Object>;
using WeakConstObject = std::weak_ptr<const Object>;

class Widget;
using SharedWidget = std::shared_ptr<Widget>;
using SharedConstWidget = std::shared_ptr<const Widget>;
using WeakWidget = std::weak_ptr<Widget>;
using WeakConstWidget = std::weak_ptr<const Widget>;

class AbstractItemModel;
using SharedItemModel = std::shared_ptr<AbstractItemModel>;
using SharedConstItemModel = std::shared_ptr<const AbstractItemModel>;
using WeakItemModel = std::weak_ptr<AbstractItemModel>;
using WeakConstItemModel = std::weak_ptr<const AbstractItemModel>;

class AbstractItemView;
using SharedItemView = std::shared_ptr<AbstractItemView>;
using SharedConstItemView = std::shared_ptr<const AbstractItemView>;
using WeakItemView = std::weak_ptr<AbstractItemView>;
using WeakConstItemView = std::weak_ptr<const AbstractItemView>;

class AbstractItemDelegate;
using SharedItemDelegate = std::shared_ptr<AbstractItemDelegate>;
using SharedConstItemDelegate = std::shared_ptr<const AbstractItemDelegate>;
using WeakItemDelegate = std::weak_ptr<AbstractItemDelegate>;
using WeakConstItemDelegate = std::weak_ptr<const AbstractItemDelegate>;

class ItemSelectionModel;
using SharedItemSelectionModel = std::shared_ptr<ItemSelectionModel>;
using SharedConstItemSelectionModel = std::shared_ptr<const ItemSelectionModel>;
using WeakItemSelectionModel = std::weak_ptr<ItemSelectionModel>;
using WeakConstItemSelectionModel = std::weak_ptr<const ItemSelectionModel>;

class Layout;
using SharedLayout = std::shared_ptr<Layout>;
using SharedConstLayout = std::shared_ptr<const Layout>;
using WeakLayout = std::weak_ptr<Layout>;
using WeakConstLayout = std::weak_ptr<const Layout>;

class Window;
using SharedWindow = std::shared_ptr<Window>;
using SharedConstWindow = std::shared_ptr<const Window>;
using WeakWindow = std::weak_ptr<Window>;
using WeakConstWindow = std::weak_ptr<const Window>;

namespace internal {
class SlotArgsStoreBase {
public:
	virtual ~SlotArgsStoreBase() = default;
};

using SharedSlotArgsStore = std::shared_ptr<SlotArgsStoreBase>;

class SlotObjectBase {
public:
	virtual ~SlotObjectBase() = default;

	virtual void Call(const SharedObject& receiver, const SharedSlotArgsStore& args_store) const = 0;
	virtual bool Compare(const SlotObjectBase& x) const = 0;
};

using UniqueSlotObject = std::unique_ptr<SlotObjectBase>;

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
	~MemberSlotObject() override = default;

	void Call(const SharedObject& receiver, const SharedSlotArgsStore& args_store) const override {
		auto store = dynamic_cast<SlotArgsStore<Args...>*>(args_store.get());
		auto r = dynamic_cast<Receiver*>(receiver.get());

		std::apply([r, this](const Args&... args) { std::invoke(func_, r, args...); }, store->args_);
	}

	bool Compare(const SlotObjectBase& x) const override {
		auto xx = dynamic_cast<const MemberSlotObject*>(&x);
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
	~FunctorSlotObject() override = default;

	void Call(const SharedObject& receiver, const SharedSlotArgsStore& args_store) const override {
		auto store = dynamic_cast<SlotArgsStore<Args...>*>(args_store.get());
		std::apply(func_, store->args_);
	}

	bool Compare(const SlotObjectBase& x) const override {
		auto xx = dynamic_cast<const FunctorSlotObject*>(&x);
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

template<class T>
concept IsUseObjectParent = std::is_base_of_v<Object, T> && !std::is_base_of_v<Widget, T>;
template<class T>
concept IsUseWidgetParent = std::is_base_of_v<Widget, T>;

template<class T, class E>
std::shared_ptr<T> Instantiate(const std::shared_ptr<E>& parent) {
	auto p = std::make_shared<T>();
	p->Initialize(parent);
	return p;
}
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

template<internal::IsUseObjectParent T>
std::shared_ptr<T> Instantiate(const SharedObject& parent) {
	return internal::Instantiate<T>(parent);
}

template<internal::IsUseWidgetParent T>
std::shared_ptr<T> Instantiate(const SharedWidget& parent) {
	return internal::Instantiate<T>(parent);
}
}

#define _MW_COMMON_IF_TRUE ,

#define _MW_FIELD_TO_DECL(field) META_EXTRACT_PAREN_UNPACK(field) META_EMPTY field

#define _MW_FIELDS_TO_ARGS_DECL_IMPL(i, ...) \
    _MW_FIELD_TO_DECL(META_INDEX(i, __VA_ARGS__)) \
    META_NOT_IF(META_INDEX_IS_END(i, __VA_ARGS__), _MW_COMMON_IF_TRUE)

#define _MW_FIELDS_TO_ARGS_DECL(...) \
    META_FOR(_MW_FIELDS_TO_ARGS_DECL_IMPL, 0, META_COUNT(__VA_ARGS__), __VA_ARGS__)

#define _MW_SIGNAL_IS_EMPTY_1(name, ...)               \
public:                                                \
    void name() const {                                \
        EmitSignal(&PureType<decltype(this)>::name);   \
    }

#define _MW_SIGNAL_IS_EMPTY_0(name, ...)                           \
public:                                                            \
    void name(_MW_FIELDS_TO_ARGS_DECL(__VA_ARGS__)) const {        \
        EmitSignal(&PureType<decltype(this)>::name, __VA_ARGS__);  \
    }

#define _MW_SIGNAL(name, ...) META_CAT(_MW_SIGNAL_IS_EMPTY_, META_IS_EMPTY(__VA_ARGS__))(name, __VA_ARGS__)

#define MW_OBJECT																		\
public:																					\
	auto shared_from_this() {															\
		using ThisType = PureType<decltype(this)>;										\
		using RetType = std::shared_ptr<ThisType>;										\
		return RetType(std::dynamic_pointer_cast<ThisType>(Object::shared_from_this()));\
	}																					\
	auto shared_from_this() const {														\
		using ThisType = const PureType<decltype(this)>;								\
		using RetType = std::shared_ptr<ThisType>;										\
		return RetType(std::dynamic_pointer_cast<ThisType>(Object::shared_from_this()));\
	}																					\
	auto weak_from_this() {																\
		using ThisType = PureType<decltype(this)>;										\
		using RetType = std::weak_ptr<ThisType>;										\
		return RetType(std::dynamic_pointer_cast<ThisType>(Object::shared_from_this()));\
	}																					\
	auto weak_from_this() const {														\
		using ThisType = const PureType<decltype(this)>;								\
		using RetType = std::weak_ptr<ThisType>;										\
		return RetType(std::dynamic_pointer_cast<ThisType>(Object::shared_from_this()));\
	}																					\
	const std::type_info& Type() const override { return typeid(this); }				\
private:																				\
