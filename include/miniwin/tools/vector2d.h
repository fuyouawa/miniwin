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
    Vector2D() : Vector2D(0, 0) {}
    Vector2D(T x, T y) : x_(x), y_(y) {}

    T x() const { return x_; }
    void set_x(T x) { x_ = x; }

    T y() const { return y_; }
    void set_y(T y) { y_ = y; }

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
    Vector2D& operator*=(const Vector2D& right) {
        x_ *= right.x_;
        y_ *= right.y_;
        return *this;
    }
    Vector2D& operator*=(const T& right) {
        x_ *= right;
        y_ *= right;
        return *this;
    }
    Vector2D operator*(const Vector2D& right) const {
        Vector2D tmp = *this;
        tmp *= right;
        return tmp;
    }
    Vector2D operator*(const T& right) const {
        Vector2D tmp = *this;
        tmp *= right;
        return tmp;
    }
    Vector2D& operator+=(const Vector2D& right) {
        x_ += right.x_;
        y_ += right.y_;
        return *this;
    }
    Vector2D& operator+=(const T& right) {
        x_ += right;
        y_ += right;
        return *this;
    }
    Vector2D operator+(const Vector2D& right) const {
        Vector2D tmp = *this;
        tmp += right;
        return tmp;
    }
    Vector2D operator+(const T& right) const {
        Vector2D tmp = *this;
        tmp += right;
        return tmp;
    }
    Vector2D& operator-=(const Vector2D& right) {
        x_ -= right.x_;
        y_ -= right.y_;
        return *this;
    }
    Vector2D operator-(const Vector2D& right) const {
        Vector2D tmp = *this;
        tmp -= right;
        return tmp;
    }
    Vector2D operator-(const T& right) const {
        Vector2D tmp = *this;
        tmp -= right;
        return tmp;
    }

private:
    T x_;
    T y_;
};
}

using Vector2D = internal::Vector2D<float>;
using Vector2DInt = internal::Vector2D<int>;
}
