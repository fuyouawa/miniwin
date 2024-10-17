#pragma once

#define _MW_EXPAND(...)		    __VA_ARGS__
#define _MW_EMPTY(...)

#define _MW_GET_FST(x, ...)        x
#define _MW_GET_SEC(x, n, ...)     n

#define _MW_CHECK(...)		        _MW_EXPAND(_MW_GET_SEC(__VA_ARGS__, 0))
#define _MW_CHECK_TRUE		        0, 1
#define _MW_CHECK_FALSE		    0

// Concatenate macros
#define _MW_PRIMITIVE_CAT(x, y, ...) x ## y
// Expand macros first, then concatenate
#define _MW_CAT(x, y, ...)			  _MW_PRIMITIVE_CAT(x, y)

// 1 -> 0; 0 -> 1
#define _MW_COMPL(x)			    _MW_PRIMITIVE_CAT(__MW_COMPL_, x)
// anything -> 0; 0 -> 1
#define _MW_NOT(x)			        _MW_CHECK(_MW_PRIMITIVE_CAT(__MW_NOT_IS_, x))
// anything -> 1; 0 -> 0
#define _MW_BOOL(x)			    _MW_COMPL(_MW_NOT(x))
#define _MW_IS_1(x)			    _MW_CHECK(_MW_CAT(__MW_IS_1_, x), 0)

#define _MW_IS_PAREN(x)		    _MW_CHECK(__MW_IS_PAREN x)

#define _MW_DEFER(x)               x _MW_EMPTY()

#define _MW_PACK(...)              (__VA_ARGS__)
#define _MW_UNPACK(x)              _MW_EXPAND x

// Get the number of variable arguments
#define _MW_COUNT(...)             __MW_COUNT(__VA_ARGS__)

#define _MW_IS_EMPTY(...)		    _MW_IS_1(_MW_CHECK(_MW_CAT(_MW_PRIMITIVE_CAT(__MW_IS_EMPTY_, __VA_ARGS__), 0)))

#define _MW_IF(cond, true_func)    _MW_EXPAND(__MW_IF(cond)(true_func))
#define _MW_NOT_IF(cond, true_func)    _MW_EXPAND(__MW_NOT_IF(cond)(true_func))
#define _MW_IF_ELSE(cond, true_func, false_func)    _MW_EXPAND(__MW_IF_ELSE(cond)(true_func)(false_func))

/*--------------------------------------------------
*            Internal macros(Dont use!)             |
---------------------------------------------------*/

// Internal for _MW_COMPL
#define __MW_COMPL_0 1
#define __MW_COMPL_1 0
// Internal for _MW_IS_PAREN
#define __MW_IS_PAREN(...) _MW_CHECK_TRUE
// Internal for _MW_NOT
#define __MW_NOT_IS_0 _MW_CHECK_TRUE

#define __MW_IS_1_1 _MW_CHECK_TRUE
#define __MW_IS_EMPTY_0 _MW_CHECK_TRUE

// Internal for _MW_COUNT
#define __MW_COUNT_IMPL(\
	 _0,  _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, \
	_10, _11, _12, _13, _14, _15, _16, _17, _18, _19, \
	_20, _21, _22, _23, _24, _25, _26, _27, _28, _29, \
	_30, _31, _32, _33, _34, _35, _36, _37, _38, _39, \
	_40, _41, _42, _43, _44, _45, _46, _47, _48, _49, \
	_50, _51, _52, _53, _54, _55, _56, _57, _58, _59, \
	_60, _61, _62, _63, _64, N, ...) N

#define __MW_COUNT(...) _MW_EXPAND(__MW_COUNT_IMPL(0, ##__VA_ARGS__,\
	64, 63, 62, 61, 60, \
	59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
	49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
	39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
	29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
	19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
	 9,  8,  7,  6,  5,  4,  3,  2,  1,  0))

#define __MW_IF_1_ELSE(...)
#define __MW_IF_0_ELSE(...) __VA_ARGS__

#define __MW_IF_ELSE_1(...) __VA_ARGS__ __MW_IF_1_ELSE
#define __MW_IF_ELSE_0(...)             __MW_IF_0_ELSE

#define __MW_IF_1(...) __VA_ARGS__
#define __MW_IF_0(...)

#define __MW_IF(cond)               _MW_CAT(__MW_IF_, _MW_BOOL(cond))
#define __MW_NOT_IF(cond)           _MW_CAT(__MW_IF_, _MW_NOT(cond))
#define __MW_IF_ELSE(cond)          _MW_EXPAND(_MW_CAT(__MW_IF_ELSE_, _MW_BOOL(cond)))
