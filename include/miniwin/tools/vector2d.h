#pragma once

namespace miniwin {
namespace internal {
template<class T>
class Vector2DTemplate
{
public:
    Vector2DTemplate(T x = 0, T y = 0) : x_(x), y_(y) {}

    T x() const { return x_; }
    void set_x(T x) { x_ = x; }

    T y() const { return y_; }
    void set_y(T y) { y_ = y; }

private:
    T x_;
    T y_;
};
}

using Vector2D = internal::Vector2DTemplate<float>;
bool operator==(const Vector2D& a, const Vector2D& b);

using Vector2DInt = internal::Vector2DTemplate<int>;
bool operator==(const Vector2DInt& a, const Vector2DInt& b);
}
