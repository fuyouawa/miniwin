#pragma once

#define _MW_IMPL                    \
private:                            \
    class Impl;                     \
    std::unique_ptr<Impl> impl_;