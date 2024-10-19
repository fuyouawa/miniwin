#include <miniwin/tools/variant.h>

namespace miniwin {
Variant::Variant(std::u8string_view str)
    : data_(std::u8string(str))
{
}

bool Variant::HasValue() const
{
    return data_.has_value();
}

const std::type_info& Variant::Type() const {
    return data_.type();
}

std::u8string Variant::ToString() const
{
    try
    {
        return ToRef<std::u8string>();
    }
    catch (const std::bad_any_cast&)
    {
        return u8"";
    }
}

const std::u8string& Variant::ToStringRef() const
{
    return ToRef<std::u8string>();
}

int32_t Variant::ToInt32() const
{
    return To<int32_t>();
}

int64_t Variant::ToInt64() const
{
    return To<int64_t>();
}

uint32_t Variant::ToUInt32() const
{
    return To<uint32_t>();
}

uint64_t Variant::ToUInt64() const
{
    return To<uint64_t>();
}
}
