#pragma once
#include <miniwin/core/objectdefs.h>
#include <miniwin/tools/function_traits.h>
#include <miniwin/core/global.h>
#include <miniwin/tools/string.h>
#include <miniwin/tools/list.h>

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

    Object(Object* parent, const String& name);
    virtual ~Object();

    const Object* Parent() const;
    Object* Parent();
    virtual void SetParent(Object* parent) const;
    List<Object*> Children() const;

    bool IsWidget() const;

    const String& Name() const;
    void SetName(const String& name) const;

    FlagsType Flags() const;
    void SetFlags(FlagsType flags);
    void EnableFlags(FlagsType flags, bool enable);

    virtual void Invoke(std::function<void()>&& func, InvokeType invoke_type = InvokeType::kAuto) const;

    MW_SIGNAL(OnDestroy)
    MW_SIGNAL(OnNameChanged, (String) name, (String) prev_name)

    template<std::derived_from<Object> Sender, class Signal, std::derived_from<Object> Receiver, class Slot>
    static Disconnecter Connect(
        const Sender* sender,
        Signal signal,
        const Receiver* receiver,
        Slot&& slot,
        ConnectionFlags connection_flags = ConnectionFlags::kUnique,
        InvokeType invoke_type = InvokeType::kAuto);

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
        internal::UniqueSlotObject&& slot_obj,
        ConnectionFlags connection_flags,
        InvokeType invoke_type);

    void EmitSignalImpl(const std::type_info& signal_info,
        const internal::SharedSlotArgsStore& args_store) const;

    friend class Widget;
    friend class WidgetsDriver;

    _MW_IMPL
};

template <std::derived_from<Object> Sender, class Signal, std::derived_from<Object> Receiver, class Slot>
Object::Disconnecter Object::Connect(const Sender* sender, Signal signal, const Receiver* receiver, Slot&& slot,
	ConnectionFlags connection_flags, InvokeType invoke_type) {
	using Traits = internal::FunctionTraits<Slot>;

	return [&] <class... Args> (std::tuple<Args...>) -> Disconnecter {
		if constexpr (std::is_member_function_pointer_v<Slot>) {
			using SlotObject = internal::MemberSlotObject<Slot, Receiver, Args...>;

			return ConnectImpl(sender,
			                   typeid(signal),
			                   receiver,
			                   std::make_unique<SlotObject>(slot),
			                   connection_flags,
			                   invoke_type);
		}
		else
		{
			using SlotObject = internal::FunctorSlotObject<Args...>;
            
			return ConnectImpl(sender,
			                   typeid(signal),
			                   receiver,
			                   std::make_unique<SlotObject>(std::forward<Slot>(slot)),
			                   connection_flags,
			                   invoke_type);
		}
	}(typename Traits::Arguments());
}
}
