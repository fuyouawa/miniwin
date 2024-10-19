#pragma once
#include <miniwin/tools/macro/arithmetic.hpp>

#define META_WHILE(f, cond, cond_data, ...) _META_WHILE(f, cond, cond_data, __VA_ARGS__)
#define META_WHILE_EX(n, f, cond, cond_data, ...) _META_WHILE_EX(n, f, cond, cond_data, __VA_ARGS__)


/*--------------------------------------------------
*            Internal macros(Dont use!)             |
---------------------------------------------------*/

// Internal META_WHILE
#define _META_WHILE_IMPL(f, i, cond, cond_data, ...) META_CAT(_META_WHILE_IMPL_, cond(i, cond_data))(f, i, cond, cond_data, __VA_ARGS__)
#define _META_WHILE_IMPL_1(f, i, cond, cond_data, ...) META_EXPAND(f(i, __VA_ARGS__)) META_DEFER(_META_WHILE_IMPL_I)()(f, META_INC(i), cond, cond_data, __VA_ARGS__)
#define _META_WHILE_IMPL_0(f, i, cond, cond_data, ...) META_EXPAND(f(i, __VA_ARGS__))
#define _META_WHILE_IMPL_I() _META_WHILE_IMPL

#define _META_WHILE(f, cond, cond_data, ...) META_EVAL(256, _META_WHILE_IMPL(f, 0, cond, cond_data, __VA_ARGS__))
#define _META_WHILE_EX(n, f, cond, cond_data, ...) META_EVAL(n, _META_WHILE_IMPL(f, 0, cond, cond_data, __VA_ARGS__))