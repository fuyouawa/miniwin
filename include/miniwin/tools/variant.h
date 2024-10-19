#pragma once
#include <any>
#include <string>

namespace miniwin {
class Variant;

template <class T>
concept IsVariantable = !std::is_same_v<std::decay_t<T>, Variant> && std::is_copy_constructible_v<std::decay_t<T>>;

class Variant {
public:
    Variant() = default;

    Variant(std::u8string_view str);

    template <IsVariantable T>
    Variant(T&& val)
        : data_(std::forward<T>(val))
    {
    }

    template <IsVariantable T>
    auto ToRef() -> decltype(auto) {
        using Type = std::add_lvalue_reference_t<std::remove_cvref_t<T>>;
        return std::any_cast<Type>(data_);
    }

    template <IsVariantable T>
    auto ToRef() const -> decltype(auto) {
        using Type = std::add_lvalue_reference_t<std::add_const_t<std::remove_cvref_t<T>>>;
        return std::any_cast<Type>(data_);
    }

    template <IsVariantable T>
    auto To() const -> decltype(auto) {
        using Type = std::add_const_t<std::remove_cvref_t<T>>;
        try
        {
            return std::any_cast<Type>(data_);
        }
        catch (const std::bad_any_cast& e)
        {
            if constexpr (std::is_default_constructible_v<T>)
                return Type{};
            else
                throw std::bad_any_cast{ e };
        }
    }

    bool HasValue() const;

    const std::type_info& Type() const;

    const std::u8string& ToStringRef() const;
    std::u8string ToString() const;

    int32_t ToInt32() const;
    int64_t ToInt64() const;

    uint32_t ToUInt32() const;
    uint64_t ToUInt64() const;

private:
    std::any data_;
};
}
