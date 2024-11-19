#include <miniwin/core/event_mgr.h>

namespace miniwin {
EventManager& EventManager::Instance() {
	static auto inst = Instantiate<EventManager>(nullptr);
	return *inst;
}
}
