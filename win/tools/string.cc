#include <miniwin/tools/string.h>

#include "debug.h"

namespace miniwin {
String::String(const char8_t* str)
	: str_(str)
{
}

String::String(std::u8string_view str)
	: str_(str)
{
}

String& String::operator=(const char8_t* right)
{
    str_ = right;
    return *this;
}

String& String::operator=(std::u8string_view right)
{
    str_ = right;
    return *this;
}

std::string String::ToStdString() const
{
	return { reinterpret_cast<const char*>(str_.data()), str_.size() };
}

std::wstring String::ToStdWString() const
{
    std::wstring wstr(str_.size(), L'\0');
    auto sz = std::mbstowcs(wstr.data(), reinterpret_cast<const char*>(str_.data()), str_.size());
    MW_ASSERT_X(sz == wstr.size());
    return wstr;
}
}
