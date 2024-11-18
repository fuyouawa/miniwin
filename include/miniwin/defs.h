#pragma once
#include <cstdint>

namespace miniwin {
using FlagsType = int32_t;
using WidgetId = uint16_t;
}

#define _MW_IMPL                    \
private:                            \
    class Impl;                     \
    std::unique_ptr<Impl> impl_;