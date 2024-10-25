#pragma once
#include <functional>
#include <memory>

#include <miniwin/tools/macro.h>

namespace miniwin {
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
        store_ = std::tuple(std::forward<Args>(args)...);
    }

    std::tuple<Args...> store_;
};

template<class Func, class... Args>
class MemberSlotObject : public SlotObjectBase
{
public:
    explicit MemberSlotObject(Func func) : func_(func) {}

    void Call(const Object* receiver, const SlotArgsStoreBase* args_store) const override
    {
        const auto store = dynamic_cast<SlotArgsStore<Args...>*>(args_store);
        std::apply(func_, std::tuple_cat(std::tuple(receiver), store->store_));
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
    // �����UI������ֱ�ӵ���
    // �����UI���󣬲��ҵ��÷�Ҳ��UI�̣߳���ֱ�ӵ��ã���֮������÷�����UI�̣߳������UI���ö���
    kAuto,
    // ֱ�ӵ���
    kDirect,
    // �����UI������ֱ�ӵ���
    // �����UI���󣬻����UI���ö���
    kQueued
};

enum class ConnectionFlags {
    kNone = 0,
    kUnique = 1 << 0,    // ��������Ѵ���, ��ʧ��
    kReplace = 1 << 1,   // ��������Ѵ���, �滻��������
    kSingle = 1 << 2     // ��������һ��, �����ź�ʱ, ���ӽ��Զ��Ͽ�
};

ConnectionFlags operator|(ConnectionFlags x, ConnectionFlags y);
ConnectionFlags operator&(ConnectionFlags x, ConnectionFlags y);

template<class T>
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
    }                                                  \

#define _MW_SIGNAL_HAS_ARGS(name, ...)                             \
public:                                                            \
    void name(_MW_SIGNAL_ARGS_DECL(__VA_ARGS__)) const {           \
        EmitSignal(&PureType<decltype(this)>::name, __VA_ARGS__);  \
    }                                                              \

#define _MW_SIGNAL(name, ...) \
    META_IF_ELSE(META_IS_EMPTY(__VA_ARGS__), _MW_SIGNAL_NO_ARGS(name), _MW_SIGNAL_HAS_ARGS(name, __VA_ARGS__))

#define _MW_IMPL                    \
private:                            \
    class Impl;                     \
    std::unique_ptr<Impl> impl_;
}
