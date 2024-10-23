#pragma once

namespace miniwin {
class Mathf
{
public:
    static bool Approximately(double a, double b, double epsilon = 1e-6);
    static bool Approximately(float a, float b, float epsilon = 1e-6f);
};
}
