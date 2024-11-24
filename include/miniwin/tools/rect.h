#pragma once
#include <miniwin/tools/vector2d.h>

namespace miniwin {
namespace internal {
template<class T>
class Rect
{
public:
    constexpr Rect() : Rect(0, 0, 0, 0) {}
    constexpr Rect(T x, T y, T width, T height) : x_(x), y_(y), width_(width), height_(height) {}
    constexpr Rect(const Rect& right) : Rect(right.x_, right.y_, right.width_, right.height_) {}
    constexpr Rect(Rect&& right) noexcept : Rect(right.x_, right.y_, right.width_, right.height_) { right.x_ = 0; right.y_ = 0; right.width_ = 0; right.height_ = 0; }

    constexpr T x() const { return x_; }
    constexpr void set_x(T x) { x_ = x; }

    constexpr T y() const { return y_; }
    constexpr void set_y(T y) { y_ = y; }

    constexpr T width() const { return width_; }
    constexpr void set_width(T width) { width_ = width; }

    constexpr T height() const { return height_; }
    constexpr void set_height(T y) { height_ = height; }

    constexpr Vector2D<T> size() { return { width_, height_ }; }
    constexpr Vector2D<T> pos() { return { x_, y_ }; }

private:
    T x_;
    T y_;
    T width_;
    T height_;
};
}

using Rect = internal::Rect<float>;
using RectInt = internal::Rect<int>;
}