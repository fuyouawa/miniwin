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

    constexpr Vector2D() : Vector2D(0, 0) {}
    constexpr Vector2D(T x, T y) : x_(x), y_(y) {}

    constexpr T x() const { return x_; }
    constexpr void set_x(T x) { x_ = x; }

    constexpr T y() const { return y_; }
    constexpr void set_y(T y) { y_ = y; }

    bool operator==(const Vector2D& right) const {
        if constexpr (std::is_floating_point_v<T>) {
            return EqualFloatingPoint(x_, right.x_) && EqualFloatingPoint(y_, right.y_);
        }
        else {
            return x_ == right.x_ && y_ == right.y_;
        }
    }
    bool operator!=(const Vector2D& right) const {
        return !operator==(right);
    }
    constexpr Vector2D& operator*=(const Vector2D& right) {
        x_ *= right.x_;
        y_ *= right.y_;
        return *this;
    }
    constexpr Vector2D& operator*=(const T& right) {
        x_ *= right;
        y_ *= right;
        return *this;
    }
    constexpr Vector2D operator*(const Vector2D& right) const {
        Vector2D tmp = *this;
        tmp *= right;
        return tmp;
    }
    constexpr Vector2D operator*(const T& right) const {
        Vector2D tmp = *this;
        tmp *= right;
        return tmp;
    }
    constexpr Vector2D& operator+=(const Vector2D& right) {
        x_ += right.x_;
        y_ += right.y_;
        return *this;
    }
    constexpr Vector2D& operator+=(const T& right) {
        x_ += right;
        y_ += right;
        return *this;
    }
    constexpr Vector2D operator+(const Vector2D& right) const {
        Vector2D tmp = *this;
        tmp += right;
        return tmp;
    }
    constexpr Vector2D operator+(const T& right) const {
        Vector2D tmp = *this;
        tmp += right;
        return tmp;
    }
    constexpr Vector2D& operator-=(const Vector2D& right) {
        x_ -= right.x_;
        y_ -= right.y_;
        return *this;
    }
    constexpr Vector2D operator-(const Vector2D& right) const {
        Vector2D tmp = *this;
        tmp -= right;
        return tmp;
    }
    constexpr Vector2D operator-(const T& right) const {
        Vector2D tmp = *this;
        tmp -= right;
        return tmp;
    }

private:
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
}
