#pragma once
#include <miniwin/core/object.h>

namespace miniwin {
class EventManager : public Object {
	MW_OBJECT
public:
	static EventManager& Instance();

	template <class Signal, std::derived_from<Object> Receiver, class Slot>
	SlotDisconnecter Register(
		Signal signal,
		const std::shared_ptr<Receiver>& receiver,
		Slot&& slot,
		ConnectionFlags connection_flags = ConnectionFlags::kUnique,
		InvokeType invoke_type = InvokeType::kAuto);

	MW_SIGNAL(OnBeginNewFrame, (size_t)frame_count)
};


template <class Signal, std::derived_from<Object> Receiver, class Slot>
SlotDisconnecter EventManager::Register(Signal signal, const std::shared_ptr<Receiver>& receiver, Slot&& slot,
	ConnectionFlags connection_flags, InvokeType invoke_type)
{
	return Connect(shared_from_this(), signal, receiver, std::forward<Slot>(slot), connection_flags, invoke_type);
}
}
