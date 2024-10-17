#pragma once
#include <string_view>
#include <string>

namespace miniwin {
class Converter {
public:
    static std::wstring Utf8ToWideString(std::u8string_view str);
};
}
