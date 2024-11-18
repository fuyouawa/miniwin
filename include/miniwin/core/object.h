#pragma once
#include <miniwin/core/objectdefs.h>
#include <miniwin/tools/function_traits.h>
#include <miniwin/tools/string.h>
#include <miniwin/tools/list.h>

#define MW_SIGNAL(name, ...)  _MW_SIGNAL(name, __VA_ARGS__)

namespace miniwin {
class Widget;
class WidgetsDriver;
class Layout;

class Object : public std::enable_shared_from_this<Object> {
public:
	class Disconnecter {
	public:
		Disconnecter() = default;
		Disconnecter(std::function<bool()>&& func);

		bool Disconnect() const;

	private:
		std::function<bool()> func_;
	};

	Object();
	virtual ~Object();

	SharedObject Parent() const;
	virtual void SetParent(const SharedObject& parent) const;
	List<SharedObject> Children() const;

	bool IsWidget() const;
	bool IsLayout() const;

	String Name() const;
	void SetName(const String& name) const;

	String DebugName() const;
	String ClassName() const;
	virtual const std::type_info& Type() const;
	bool Orphaned() const;
	FlagsType Flags() const;
	void SetFlags(FlagsType flags);
	void EnableFlags(FlagsType flags, bool enable);

	virtual void Invoke(std::function<void()> func, InvokeType invoke_type = InvokeType::kAuto) const;

	MW_SIGNAL(OnDestroy)

	template <std::derived_from<Object> Sender, class Signal, std::derived_from<Object> Receiver, class Slot>
	static Disconnecter Connect(
		const std::shared_ptr<Sender>& sender,
		Signal signal,
		const std::shared_ptr<Receiver>& receiver,
		Slot&& slot,
		ConnectionFlags connection_flags = ConnectionFlags::kUnique,
		InvokeType invoke_type = InvokeType::kAuto);

	virtual void Initialize(const SharedObject& parent);

protected:
	template <class Signal, class... Args>
	void EmitSignal(Signal signal, Args&&... args) const {
		using SlotArgsStore = internal::SlotArgsStore<Args...>;

		EmitSignalImpl(typeid(signal),
		               std::make_shared<SlotArgsStore>(std::forward<Args>(args)...));
	}

private:
	static Disconnecter ConnectImpl(
		const SharedObject& sender,
		const std::type_info& signal_info,
		const SharedObject& receiver,
		internal::UniqueSlotObject&& slot_obj,
		ConnectionFlags connection_flags,
		InvokeType invoke_type);

	void EmitSignalImpl(const std::type_info& signal_info,
	                    const internal::SharedSlotArgsStore& args_store) const;

	friend class Widget;
	friend class WidgetsDriver;
	friend class Layout;

	_MW_IMPL
};

template <std::derived_from<Object> Sender, class Signal, std::derived_from<Object> Receiver, class Slot>
Object::Disconnecter Object::Connect(const std::shared_ptr<Sender>& sender, Signal signal,
                                     const std::shared_ptr<Receiver>& receiver, Slot&& slot,
                                     ConnectionFlags connection_flags, InvokeType invoke_type) {
	using Traits = internal::FunctionTraits<Slot>;

	return [&] <class... Args>(std::tuple<Args...>) -> Disconnecter {
		if constexpr (std::is_member_function_pointer_v<Slot>) {
			using SlotObject = internal::MemberSlotObject<Slot, Receiver, Args...>;

			return ConnectImpl(sender,
			                   typeid(signal),
			                   receiver,
			                   std::make_unique<SlotObject>(slot),
			                   connection_flags,
			                   invoke_type);
		}
		else {
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
