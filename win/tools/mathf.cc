#include <miniwin/tools/mathf.h>
#include <algorithm>

namespace miniwin {
bool Mathf::Approximately(float a, float b, float epsilon)
{
    float diff = fabs(a - b);
    if (diff < epsilon) {
        return true;
    }
    // 使用相对误差比较
    return diff < epsilon * std::max(fabs(a), fabs(b));
}
}
