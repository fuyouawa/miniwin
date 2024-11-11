#pragma once
#include <memory>

#define _MW_IMPL                    \
private:                            \
    class Impl;                     \
    std::unique_ptr<Impl> impl_;

namespace miniwin {
using FlagsType = int;
}
