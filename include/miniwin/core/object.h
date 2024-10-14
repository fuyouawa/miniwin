#pragma once
#include <miniwin/core/objectdefs.h>
#include <string_view>

namespace miniwin {
enum class ObjectType
{
    Widget,
    Model,
    Delegate,
    SelectionModel
};

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

    Object(Object* parent, std::u8string_view name, ObjectType object_type);
    virtual ~Object();

    const Object* parent() const;
    void set_parent(Object* parent) const;

    std::u8string_view name() const;
    void set_name(std::u8string_view name) const;

    ObjectType object_type() const;
    int flags() const;
    void set_flags(int flags);
    void set_flags_active(int flags, bool b);

    const std::vector<Object*>& children() const;

    virtual void Invoke(std::function<void()>&& func, InvokeType invoke_type = InvokeType::kAuto) const;

    MW_SIGNAL(OnDestroy)

    template<typename Signal, typename Func, typename... Args>
        requires std::is_member_function_pointer_v<Signal> && std::is_member_function_pointer_v<Func>
    Disconnecter Connect(
        Signal signal,
        const Object* receiver,
        Func slot,
        ConnectionFlags connection_flags = ConnectionFlags::kUnique,
        InvokeType invoke_type = InvokeType::kAuto) const
    {
        using SlotObject = internal::MemberSlotObject<Func, Args...>;

        return ConnectImpl(typeid(signal),
            receiver,
            std::make_unique<SlotObject>(slot),
            connection_flags,
            invoke_type);
    }

    template<typename Signal, typename... Args>
        requires std::is_member_function_pointer_v<Signal>
    Disconnecter Connect(
        Signal signal,
        const Object* receiver,
        std::function<Args...> slot,
        ConnectionFlags connection_flags = ConnectionFlags::kUnique,
        InvokeType invoke_type = InvokeType::kAuto) const
    {
        using SlotObject = internal::FunctorSlotObject<Args...>;

        return ConnectImpl(typeid(signal),
            receiver,
            std::make_unique<SlotObject>(slot),
            connection_flags,
            invoke_type);
    }

protected:
    template<class Signal, class... Args>
    void EmitSignal(Signal signal, Args&&... args) const {
        using SlotArgsStore = internal::SlotArgsStore<Args...>;

        EmitSignalImpl(typeid(signal),
            std::make_shared<SlotArgsStore>(std::forward<Args>(args)...));
    }

private:
    Disconnecter ConnectImpl(const std::type_info& signal_info,
        const Object* receiver,
        internal::SlotObjectPtr&& slot_obj,
        ConnectionFlags connection_flags,
        InvokeType invoke_type) const;

    void EmitSignalImpl(const std::type_info& signal_info,
        const internal::SlotArgsStoreSharedPtr& args_store) const;

    class Impl;
    std::unique_ptr<Impl> impl_;
};
}
