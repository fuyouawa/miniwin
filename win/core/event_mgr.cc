#include <miniwin/core/event_mgr.h>

namespace miniwin {
EventManager& EventManager::Instance() {
	static auto inst = Create<EventManager>(nullptr);
	return *inst;
}
}
