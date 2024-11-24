#pragma once
#include <type_traits>

namespace miniwin {
namespace internal {
bool EqualFloatingPoint(float x, float y);
bool EqualFloatingPoint(double x, double y);

template<class T>
class Vector2D
{
public:
    static Vector2D kZero;
    static Vector2D kOne;

    constexpr Vector2D() noexcept : Vector2D(0, 0) {}
    constexpr Vector2D(T x, T y) noexcept : x_(x), y_(y) {}
    constexpr Vector2D(const Vector2D& right) noexcept : Vector2D(right.x_, right.y_) {}
    constexpr Vector2D(Vector2D&& right) noexcept : Vector2D(right.x_, right.y_) { right.x_ = 0; right.y_ = 0; }

    constexpr Vector2D& operator=(const Vector2D& right) noexcept { x_ = right.x_; y_ = right.y_; return *this; }
    constexpr Vector2D& operator=(Vector2D&& right) noexcept { x_ = right.x_; y_ = right.y_; right.x_ = 0; right.y_ = 0; return *this;
    }

    constexpr T x() const noexcept { return x_; }
    constexpr void set_x(T x) noexcept { x_ = x; }

    constexpr T y() const noexcept { return y_; }
    constexpr void set_y(T y) noexcept { y_ = y; }

    bool operator==(const Vector2D& right) const noexcept {
        if constexpr (std::is_floating_point_v<T>) {
            return EqualFloatingPoint(x_, right.x_) && EqualFloatingPoint(y_, right.y_);
        }
        else {
            return x_ == right.x_ && y_ == right.y_;
        }
    }
    bool operator!=(const Vector2D& right) const noexcept {
        return !operator==(right);
    }
    constexpr Vector2D& operator*=(const Vector2D& right) noexcept {
        x_ *= right.x_;
        y_ *= right.y_;
        return *this;
    }
    
    constexpr Vector2D& operator*=(const T& right) noexcept {
        x_ *= right;
        y_ *= right;
        return *this;
    }
    constexpr Vector2D operator*(const Vector2D& right) const noexcept {
        Vector2D tmp = *this;
        tmp *= right;
        return tmp;
    }
    constexpr Vector2D operator*(const T& right) const noexcept {
        Vector2D tmp = *this;
        tmp *= right;
        return tmp;
    }
    constexpr Vector2D& operator+=(const Vector2D& right) noexcept {
        x_ += right.x_;
        y_ += right.y_;
        return *this;
    }
    constexpr Vector2D& operator+=(const T& right) noexcept {
        x_ += right;
        y_ += right;
        return *this;
    }
    constexpr Vector2D operator+(const Vector2D& right) const noexcept {
        Vector2D tmp = *this;
        tmp += right;
        return tmp;
    }
    constexpr Vector2D operator+(const T& right) const noexcept {
        Vector2D tmp = *this;
        tmp += right;
        return tmp;
    }
    constexpr Vector2D& operator-=(const Vector2D& right) noexcept {
        x_ -= right.x_;
        y_ -= right.y_;
        return *this;
    }
    constexpr Vector2D operator-(const Vector2D& right) const noexcept {
        Vector2D tmp = *this;
        tmp -= right;
        return tmp;
    }
    constexpr Vector2D operator-(const T& right) const noexcept {
        Vector2D tmp = *this;
        tmp -= right;
        return tmp;
    }

protected:
    T x_;
    T y_;
};

template<class T>
Vector2D<T> Vector2D<T>::kZero{ 0, 0 };
template<class T>
Vector2D<T> Vector2D<T>::kOne{ 1, 1 };
}

using Vector2D = internal::Vector2D<float>;
using Vector2DInt = internal::Vector2D<int>;

Vector2DInt VecToVecInt(const Vector2D& v);
Vector2D VecIntToVec(const Vector2DInt& v);
}
