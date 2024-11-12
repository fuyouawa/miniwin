#include <miniwin/tools/string.h>
#include <miniwin/tools/stringlist.h>

#include "debug.h"

namespace miniwin {
String String::FromStdString(const std::string& str) {
    String tmp;
    tmp.str_ = str;
    return tmp;
}

String String::FromStdString(std::string&& str) {
    String tmp;
    tmp.str_ = std::move(str);
    return tmp;
}

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

String& String::operator+=(char right) {
    str_ += right;
    return *this;
}

std::string String::ToStdString() const
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

String& String::Replace(const String& before, const String& after) {
    size_t start = 0;
    while ((start = IndexOf(before, start)) != kNPos) {
        str_.replace(start, before.size(), after.str_);
        start += after.size();
    }
    return *this;
}

StringList String::Split(const String& sep) const {
    StringList total;
    size_t start = 0;
    size_t end = IndexOf(sep);
    while (end != kNPos) {
        total.PushBack(Substr(start, end));
        start += end + sep.size();
        end = IndexOf(sep, start);
    }
    total.PushBack(Substr(start));
    return total;
}

size_t String::IndexOf(const String& str, size_t start) const {
    return str_.find(str.str_, start);
}

String String::Substr(size_t begin, size_t end) const {
    return FromStdString(str_.substr(begin, end - begin));
}

String operator+(const String& x, const String& y) {
	String x1(x);
	return x1 += y;
}

String operator+(const String& x, char y) {
	String x1(x);
	return x1 += y;
}
}