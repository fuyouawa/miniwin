#include <miniwin/tools/mathf.h>

#include <algorithm>

namespace miniwin {
bool Mathf::Approximately(double a, double b, double epsilon)
{
    double diff = fabs(a - b);
    if (diff < epsilon) {
        return true;
    }
    // 使用相对误差比较
    return diff < epsilon * std::max(fabs(a), fabs(b));
}

bool Mathf::Approximately(float a, float b, float epsilon)
{
    return Approximately(static_cast<double>(a), static_cast<double>(b), static_cast<double>(epsilon));
}
}
