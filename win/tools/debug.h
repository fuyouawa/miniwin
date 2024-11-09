#pragma once
#include <format>

namespace miniwin {
void DebugOutput(std::string_view str) noexcept;

namespace internal {
void AssertionFailed(std::string_view file, std::string_view func, int line, std::string_view msg) noexcept;
std::string MsgOfThrow(std::string_view file, std::string_view func, int line, std::string_view msg) noexcept;
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
#define MW_ASSERT(cond, ...)	_MW_ASSERT(cond, std::format(__VA_ARGS__))

#else

#define MW_ASSERT_X(cond)
#define MW_ASSERT(cond, ...)

#endif

#define MW_THROW(...)			throw std::exception(miniwin::internal::MsgOfThrow(__FILE__, __FUNCTION__, __LINE__, std::format(__VA_ARGS__)).c_str())