#include "application_impl.h"

namespace miniwin {
Application::~Application() {}

Application& Application::Instance() {
	static ApplicationImpl inst;
	return inst;
}
}