#include <miniwin/tools/string.h>

#include <cassert>

namespace miniwin {
String::String(const char8_t* str)
	: str_(str)
{
}

String::String(std::u8string_view str)
	: str_(str)
{
}

String& String::operator=(const char8_t* other)
{
    str_ = other;
    return *this;
}

String& String::operator=(std::u8string_view other)
{
    str_ = other;
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
    assert(sz == wstr.size());
    return wstr;
}

StringList::StringList(std::initializer_list<String> args)
    : Inherit(args)
{
}
}
