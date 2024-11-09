#include "debug.h"

#include <iostream>
#if _WIN32
#include <Windows.h>
#endif // _WIN32

namespace miniwin {
void DebugOutput(std::string_view str) noexcept {
#if _WIN32
	::OutputDebugStringA(str.data());
#endif // _WIN32
}

namespace internal {
void AssertionFailed(std::string_view file, std::string_view func, int line, std::string_view msg) noexcept {
	DebugOutput(std::format("[Geek] Assertion failed at {} (func {}) (line {}): {}", file, func, msg));
	::abort();
}

std::string MsgOfThrow(std::string_view file, std::string_view func, int line, std::string_view msg) noexcept {
	return std::format("[Geek] Exception at {} (func {}) (line {}): {}", file, func, msg);
}
}
}
