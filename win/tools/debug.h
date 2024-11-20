#pragma once
#include <miniwin/tools/string.h>

namespace miniwin {
namespace internal {
void DebugOutput(const String& str) noexcept;
void AssertionFailed(std::string_view file, std::string_view func, int line, const String& msg) noexcept;
String MsgOfThrow(std::string_view file, std::string_view func, int line, const String& msg) noexcept;
}

template<class... Args>
void DebugOutput(const String& fmt, const Args&... args) {
	internal::DebugOutput(String::Format(fmt, args...));
}
}

#if !defined(MINIWIN_BUILD_DEBUG) && !defined(MINIWIN_BUILD_RELEASE)
#if !defined(NDEBUG)
#define MINIWIN_BUILD_DEBUG
#else
#define MINIWIN_BUILD_RELEASE
#endif
#endif

#if defined(MINIWIN_BUILD_DEBUG)

#define _MW_ASSERT(cond, msg)								\
	do {													\
		if (!!(cond)) break;								\
			miniwin::internal::AssertionFailed(__FILE__, __FUNCTION__, __LINE__, msg); \
	} while (0)

#define MW_ASSERT_X(cond)		_MW_ASSERT(cond, #cond)
#define MW_ASSERT(cond, ...)	_MW_ASSERT(cond, miniwin::String::Format(__VA_ARGS__))

#else

#define MW_ASSERT_X(cond)
#define MW_ASSERT(cond, ...)

#endif

#define MW_THROW_EX(e, ...)		throw e(miniwin::internal::MsgOfThrow(__FILE__, __FUNCTION__, __LINE__, miniwin::String::Format(__VA_ARGS__)).data())
#define MW_THROW(...)			MW_THROW_EX(std::exception)