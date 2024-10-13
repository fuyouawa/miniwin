#pragma once
#include <functional>
#include <memory>

#include <fugui/tools/macro.h>

namespace fugui {
class Object;
namespace internal {
class SlotArgsStoreBase
{
public:
    virtual ~SlotArgsStoreBase() = default;
};

using SlotArgsStoreSharedPtr = std::shared_ptr<SlotArgsStoreBase>;

class SlotObjectBase
{
public:
    virtual ~SlotObjectBase() = default;

    virtual void Call(const Object* receiver, const SlotArgsStoreBase* args_store) const = 0;
    virtual bool Compare(const SlotObjectBase* x) const = 0;
};

using SlotObjectPtr = std::unique_ptr<SlotObjectBase>;

template<class... Args>
class SlotArgsStore : public SlotArgsStoreBase
{
public:
    explicit SlotArgsStore(Args&&... args)
    {
        store_ = std::tuple{ std::forward<Args>(args)... };
    }

    std::tuple<Args...> store_;
};

template<class Func, class... Args>
class MemberSlotObject : public SlotObjectBase
{
public:
    explicit MemberSlotObject(Func func) : func_{ func } {}

    void Call(const Object* receiver, const SlotArgsStoreBase* args_store) const override
    {
        const auto store = dynamic_cast<SlotArgsStore<Args...>*>(args_store);
        std::apply(func_, std::tuple_cat(std::tuple{receiver}, store->store_));
    }

    bool Compare(const SlotObjectBase* x) const override
    {
        const auto xx = dynamic_cast<MemberSlotObject*>(x);
        return xx != nullptr && xx.func_ == func_;
    }

    Func func_;
};

template<class... Args>
class FunctorSlotObject : public SlotObjectBase
{
public:
    FunctorSlotObject(std::function<Args...>&& func) : func_(std::move(func)) {}

    void Call(const Object* receiver, const SlotArgsStoreBase* args_store) const override
    {
        const auto store = dynamic_cast<SlotArgsStore<Args...>*>(args_store);
        std::apply(func_, store->store_);
    }

    bool Compare(const SlotObjectBase* x) const override
    {
        const auto xx = dynamic_cast<FunctorSlotObject*>(x);
        return xx != nullptr && xx.func_ == func_;
    }

    std::function<Args...> func_;
};
}//namespace internal

enum class InvokeType {
    // 如果非UI对象，则直接调用
    // 如果是UI对象，并且调用方也在UI线程，则直接调用；反之如果调用方不在UI线程，则加入UI调用队列
    kAuto,
    // 直接调用
    kDirect,
    // 如果非UI对象，则直接调用
    // 如果是UI对象，会加入UI调用队列
    kQueued
};

enum class ConnectionFlags {
    kNone = 0,
    kUnique = 1 << 0,    // 如果连接已存在, 将失败
    kReplace = 1 << 1,   // 如果连接已存在, 替换已有连接
    kSingle = 1 << 2     // 仅被调用一次, 发出信号时, 连接将自动断开
};

ConnectionFlags operator|(ConnectionFlags x, ConnectionFlags y);
ConnectionFlags operator&(ConnectionFlags x, ConnectionFlags y);

#define __MINIWIN_COMMON_IF_TRUE ,

#define _MW_SIGNAL_ARG_TO_DECL(arg) \
    _MINIWIN_EXPAND arg

#define _MW_SIGNAL_ARGS_DECL_IMPL(i, ...) \
    _MW_SIGNAL_ARG_TO_DECL(_MINIWIN_INDEX(i, __VA_ARGS__)) \
    _MINIWIN_NOT_IF(_MINIWIN_INDEX_IS_END(i, __VA_ARGS__), __MINIWIN_COMMON_IF_TRUE)

#define _MW_SIGNAL_ARGS_DECL(...) \
    _MINIWIN_FOR(_MW_SIGNAL_ARGS_DECL_IMPL, _MINIWIN_COUNT(__VA_ARGS__), __VA_ARGS__)

#define _MW_SIGNAL_NO_ARGS(name) public: void name() { EmitSignal(&_ObjectType::name); }

#define _MW_SIGNAL_HAS_ARGS(name, ...) \
    public: void name(_MW_SIGNAL_ARGS_DECL(__VA_ARGS__)) { EmitSignal(&_ObjectType::name, __VA_ARGS__); }

#define _MW_SIGNAL(name, ...) \
    _MINIWIN_IF_ELSE(_MINIWIN_IS_EMPTY(__VA_ARGS__), _MW_SIGNAL_NO_ARGS(name), _MW_SIGNAL_HAS_ARGS(name, __VA_ARGS__))

#define MW_OBJECT(o)     \
private:                        \
    using _ObjectType = o;

#define MW_SIGNAL(name, ...)  _MW_SIGNAL(name, __VA_ARGS__)
}
