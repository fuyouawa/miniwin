#pragma once
#include <miniwin/core/objectdefs.h>
#include <miniwin/tools/function_traits.h>
#include <string_view>

#define MW_SIGNAL(name, ...)  _MW_SIGNAL(name, __VA_ARGS__)

namespace miniwin {
class Object
{
public:
    class Disconnecter
    {
    public:
        Disconnecter() = default;
        Disconnecter(std::function<bool()>&& func);

        bool Disconnect() const;

    private:
        std::function<bool()> func_;
    };

    Object(Object* parent, std::u8string_view name);
    virtual ~Object();

    const Object* Parent() const;
    void SetParent(Object* parent) const;
    const std::vector<Object*>& Children() const;

    std::u8string_view Name() const;
    void SetName(std::u8string_view name) const;

    virtual void Invoke(std::function<void()>&& func, InvokeType invoke_type = InvokeType::kAuto) const;

    MW_SIGNAL(OnDestroy)

    template<std::derived_from<Object> Sender, class Signal, std::derived_from<Object> Receiver, class Slot>
    static Disconnecter Connect(
        const Sender* sender,
        Signal signal,
        const Receiver* receiver,
        Slot&& slot,
        ConnectionFlags connection_flags = ConnectionFlags::kUnique,
        InvokeType invoke_type = InvokeType::kAuto)
    {
        static_assert(internal::kIsArgumentsMatchableFunctions<Signal, Slot>);
        using Traits = internal::FunctionTraits<Slot>;

        return [&] <class... Args> (std::tuple<Args...>) -> Disconnecter {
            if constexpr (std::is_member_function_pointer_v<Slot>)
            {
                using Func = typename Traits::Return(Receiver::*)(Args...);
                using SlotObject = internal::MemberSlotObject<Func, Args...>;

                return ConnectImpl(sender,
                    typeid(signal),
                    receiver,
                    std::make_unique<SlotObject>(slot),
                    connection_flags,
                    invoke_type);
            }
            else
            {
                using Functor = std::function<void(Args...)>;
                using SlotObject = internal::FunctorSlotObject<Args...>;

                Functor func = [s = std::forward<Slot>(slot)](Args&&... args) {
                    s(std::forward<Args>(args)...);
                    };

                return ConnectImpl(sender,
                    typeid(signal),
                    receiver,
                    std::make_unique<SlotObject>(std::move(func)),
                    connection_flags,
                    invoke_type);
            }
        }(typename Traits::Arguments{});
    }

protected:
    template<class Signal, class... Args>
    void EmitSignal(Signal signal, Args&&... args) const {
        using SlotArgsStore = internal::SlotArgsStore<Args...>;

        EmitSignalImpl(typeid(signal),
            std::make_shared<SlotArgsStore>(std::forward<Args>(args)...));
    }

private:
    static Disconnecter ConnectImpl(
        const Object* sender,
        const std::type_info& signal_info,
        const Object* receiver,
        internal::SlotObjectPtr&& slot_obj,
        ConnectionFlags connection_flags,
        InvokeType invoke_type);

    void EmitSignalImpl(const std::type_info& signal_info,
        const internal::SlotArgsStoreSharedPtr& args_store) const;

    _MW_IMPL
};
}
