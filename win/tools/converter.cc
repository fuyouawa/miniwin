#include <miniwin/tools/converter.h>

#include <cassert>

#include <codecvt>
#include <string>

namespace miniwin {
std::wstring Converter::Utf8ToWideString(std::u8string_view str)
{
    std::wstring wstr(str.size(), L'\0');
    auto sz = std::mbstowcs(wstr.data(), reinterpret_cast<const char*>(str.data()), str.size());
    assert(sz == wstr.size());
    return wstr;
}
}
