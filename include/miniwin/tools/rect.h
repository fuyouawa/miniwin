#pragma once
#include <miniwin/tools/vector2d.h>

namespace miniwin {
namespace internal {
template<class T>
class Rect
{
public:
    Rect() = default;
    Rect(T x = 0, T y = 0, T width = 0, T height = 0) : x_(x), y_(y), width_(width), height_(height) {}

    T x() const { return x_; }
    void set_x(T x) { x_ = x; }

    T y() const { return y_; }
    void set_y(T y) { y_ = y; }


    T width() const { return width_; }
    void set_width(T width) { width_ = width; }

    T height() const { return height_; }
    void set_height(T y) { height_ = height; }

    Vector2D<T> size() { return { width_, height_ }; }
    Vector2D<T> pos() { return { x_, y_ }; }

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