#pragma once

namespace miniwin {
namespace internal {
template<class T>
class Vector2Template
{
public:
    Vector2Template(T x = 0, T y = 0) : x_(x), y_(y) {}

    T x() const { return x_; }
    void set_x(T x) { x_ = x; }

    T y() const { return y_; }
    void set_y(T y) { y_ = y; }

private:
    T x_;
    T y_;
};


template<class T>
class RectTemplate
{
public:
    RectTemplate() = default;
    RectTemplate(T x = 0, T y = 0, T width = 0, T height = 0) : x_(x), y_(y), width_(width), height_(height) {}

    T x() const { return x_; }
    void set_x(T x) { x_ = x; }

    T y() const { return y_; }
    void set_y(T y) { y_ = y; }


    T width() const { return width_; }
    void set_width(T width) { width_ = width; }

    T height() const { return height_; }
    void set_height(T y) { height_ = height; }

private:
    T x_;
    T y_;
    T width_;
    T height_;
};
}

using Vector2 = internal::Vector2Template<float>;
bool operator==(const Vector2& a, const Vector2& b);

using Vector2Int = internal::Vector2Template<int>;
bool operator==(const Vector2Int& a, const Vector2Int& b);

using Rect = internal::RectTemplate<float>;
using RectInt = internal::RectTemplate<int>;
}
