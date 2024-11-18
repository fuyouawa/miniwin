#include "debug.h"

#include <iostream>
#if _WIN32
#include <Windows.h>
#endif // _WIN32

namespace miniwin {
namespace internal {
void DebugOutput(const String& str) noexcept {
#ifdef MINIWIN_BUILD_DEBUG

	std::cout << str.ToStdString();
#if _WIN32
	::OutputDebugStringA(str.data());
#endif // _WIN32

#endif // MINIWIN_BUILD_DEBUG
}
void AssertionFailed(std::string_view file, std::string_view func, int line, const String& msg) noexcept {
	DebugOutput(String::Format("[Geek] Assertion failed at{} (func{}) (line{}) : {}", file, func, line, msg));
	::abort();
}

String MsgOfThrow(std::string_view file, std::string_view func, int line, const String& msg) noexcept {
	return String::Format("[Geek] Exception at {} (func {}) (line {}): {}", file, func, line, msg);
}
}
}
