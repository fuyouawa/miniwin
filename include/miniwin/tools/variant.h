#pragma once
#include <variant>
#include <miniwin/tools/string.h>

enum class VariantType
{
    kEmpty,
    kNull,
    kChar,
    kBool,
    kInt32,
    kUInt32,
    kInt64,
    kUInt64,
    kFloat,
    kDouble,
    kString
};

namespace miniwin {
class Variant {
public:
    Variant();
    ~Variant();

    Variant(const Variant& other);
    Variant& operator=(const Variant& other);

    Variant(std::nullptr_t);
    Variant(char c);
    Variant(bool b);
    Variant(int32_t i32);
    Variant(uint32_t u32);
    Variant(int64_t i64);
    Variant(uint64_t u64);
    Variant(float f);
    Variant(double d);
    Variant(const String& str);

    VariantType Type() const;

    bool IsNull() const;
    bool IsEmpty() const;
    bool IsFloatingPoint() const;
    bool IsInteger() const;
    bool IsNumber() const;

    size_t ToInteger(bool* ok = nullptr) const;

    char ToChar(bool* ok = nullptr) const;
    bool ToBool(bool* ok = nullptr) const;
    int32_t ToInt32(bool* ok = nullptr) const;
    int64_t ToInt64(bool* ok = nullptr) const;
    uint32_t ToUInt32(bool* ok = nullptr) const;
    uint64_t ToUInt64(bool* ok = nullptr) const;
    String ToString(bool* ok = nullptr) const;

private:
    std::variant<std::monostate, std::nullptr_t, char, bool, int32_t, uint32_t, int64_t, uint64_t, float, double, char8_t*> var_;
};
}
