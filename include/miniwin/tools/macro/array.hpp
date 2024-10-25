#pragma once

#include <miniwin/tools/macro/array/index.hpp>
#include <miniwin/tools/macro/array/pop_front.hpp>
#include <miniwin/tools/macro/array/pop_back.hpp>
#include <miniwin/tools/macro/array/reserve.hpp>

#define META_SUB_ARGS(beg, end, ...) META_POP_FRONT_N(beg, META_RESERVE(META_INC(end), __VA_ARGS__))