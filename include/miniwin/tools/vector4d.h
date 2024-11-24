#pragma once
#include <type_traits>

namespace miniwin {
namespace internal {
template<class T>
class Vector4D {
public:
    constexpr Vector4D() : Vector4D(0, 0, 0, 0) {}
    constexpr Vector4D(T x, T y, T z, T w) : x_(x), y_(y), z_(z), w_(w) {}

    constexpr T x() const { return x_; }
    constexpr void set_x(T x) { x_ = x; }

    constexpr T y() const { return y_; }
    constexpr void set_y(T y) { y_ = y; }

    constexpr T z() const { return z_; }
    constexpr void set_z(T z) { z_ = z; }

    constexpr T w() const { return w_; }
    constexpr void set_w(T w) { w_ = w; }

private:
    T x_;
    T y_;
    T z_;
    T w_;
};
}

using Vector4D = internal::Vector4D<float>;
using Vector4DInt = internal::Vector4D<int>;
}