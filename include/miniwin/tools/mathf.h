#pragma once

namespace miniwin {
class Mathf
{
public:
    static bool Approximately(float a, float b, float epsilon = 1e-6f);
};
}
