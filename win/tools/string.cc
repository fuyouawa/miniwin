#include <miniwin/tools/string.h>

#include "debug.h"

namespace miniwin {
String::String(const char* str)
	: str_(str)
{
}

String::String(const char* str, size_t size) : str_(str, size) {}

String& String::operator=(const char* right)
{
    str_ = right;
    return *this;
}

String& String::operator+=(const String& right) {
    str_ += right.str_;
    return *this;
}

const std::string& String::ToStdString() const
{
	return str_;
}

std::wstring String::ToStdWString() const
{
    std::wstring wstr(str_.size(), L'\0');
    auto sz = std::mbstowcs(wstr.data(), str_.data(), str_.size());
    MW_ASSERT_X(sz == wstr.size());
    return wstr;
}

String operator+(const String& x, const String& y) {
	String x1(x);
	return x1 += y;
}
}
