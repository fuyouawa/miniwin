#pragma once

#define _MINIWIN_EXPAND(...)		    __VA_ARGS__
#define _MINIWIN_EMPTY(...)

#define _MINIWIN_GET_FST(x, ...)        x
#define _MINIWIN_GET_SEC(x, n, ...)     n

#define _MINIWIN_CHECK(...)		        _MINIWIN_EXPAND(_MINIWIN_GET_SEC(__VA_ARGS__, 0))
#define _MINIWIN_CHECK_TRUE		        0, 1
#define _MINIWIN_CHECK_FALSE		    0

// Concatenate macros
#define _MINIWIN_PRIMITIVE_CAT(l, r)    l ## r
// Expand macros first, then concatenate
#define _MINIWIN_CAT(l, r)			    _MINIWIN_PRIMITIVE_CAT(l, r)

// 1 -> 0; 0 -> 1
#define _MINIWIN_COMPL(x)			    _MINIWIN_PRIMITIVE_CAT(__MINIWIN_COMPL_, x)
// anything -> 0; 0 -> 1
#define _MINIWIN_NOT(x)			        _MINIWIN_CHECK(_MINIWIN_PRIMITIVE_CAT(__MINIWIN_NOT_IS_, x))
// anything -> 1; 0 -> 0
#define _MINIWIN_BOOL(x)			    _MINIWIN_COMPL(_MINIWIN_NOT(x))
#define _MINIWIN_IS_1(x)			    _MINIWIN_CHECK(_MINIWIN_CAT(__MINIWIN_IS_1_, x), 0)

#define _MINIWIN_IS_PAREN(x)		    _MINIWIN_CHECK(__MINIWIN_IS_PAREN x)

#define _MINIWIN_DEFER(x)               x _MINIWIN_EMPTY()

#define _MINIWIN_PACK(...)              (__VA_ARGS__)
#define _MINIWIN_UNPACK(x)              _MINIWIN_EXPAND x

// Get the number of variable arguments
#define _MINIWIN_COUNT(...)             __MINIWIN_COUNT(__VA_ARGS__)

#define _MINIWIN_IS_EMPTY(x)		    _MINIWIN_IS_1(_MINIWIN_CHECK(_MINIWIN_CAT(_MINIWIN_PRIMITIVE_CAT(__MINIWIN_IS_EMPTY_, x), 0)))

#define _MINIWIN_IF(cond, true_func)    _MINIWIN_EXPAND(__MINIWIN_IF(cond)(true_func))
#define _MINIWIN_NOT_IF(cond, true_func)    _MINIWIN_EXPAND(__MINIWIN_NOT_IF(cond)(true_func))
#define _MINIWIN_IF_ELSE(cond, true_func, false_func)    _MINIWIN_EXPAND(__MINIWIN_IF_ELSE(cond)(true_func)(false_func))

/*--------------------------------------------------
*            Internal macros(Dont use!)             |
---------------------------------------------------*/

// Internal for _MINIWIN_COMPL
#define __MINIWIN_COMPL_0 1
#define __MINIWIN_COMPL_1 0
// Internal for _MINIWIN_IS_PAREN
#define __MINIWIN_IS_PAREN(...) _MINIWIN_CHECK_TRUE
// Internal for _MINIWIN_NOT
#define __MINIWIN_NOT_IS_0 _MINIWIN_CHECK_TRUE

#define __MINIWIN_IS_1_1 _MINIWIN_CHECK_TRUE
#define __MINIWIN_IS_EMPTY_0 _MINIWIN_CHECK_TRUE

// Internal for _MINIWIN_COUNT
#define __MINIWIN_COUNT_IMPL(\
	 _0,  _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, \
	_10, _11, _12, _13, _14, _15, _16, _17, _18, _19, \
	_20, _21, _22, _23, _24, _25, _26, _27, _28, _29, \
	_30, _31, _32, _33, _34, _35, _36, _37, _38, _39, \
	_40, _41, _42, _43, _44, _45, _46, _47, _48, _49, \
	_50, _51, _52, _53, _54, _55, _56, _57, _58, _59, \
	_60, _61, _62, _63, _64, N, ...) N

#define __MINIWIN_COUNT(...) _MINIWIN_EXPAND(__MINIWIN_COUNT_IMPL(0, ##__VA_ARGS__,\
	64, 63, 62, 61, 60, \
	59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
	49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
	39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
	29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
	19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
	 9,  8,  7,  6,  5,  4,  3,  2,  1,  0))

#define __MINIWIN_IF_1_ELSE(...)
#define __MINIWIN_IF_0_ELSE(...) __VA_ARGS__

#define __MINIWIN_IF_ELSE_1(...) __VA_ARGS__ __MINIWIN_IF_1_ELSE
#define __MINIWIN_IF_ELSE_0(...)             __MINIWIN_IF_0_ELSE

#define __MINIWIN_IF_1(...) __VA_ARGS__
#define __MINIWIN_IF_0(...)

#define __MINIWIN_IF(cond)               _MINIWIN_CAT(__MINIWIN_IF_, _MINIWIN_BOOL(cond))
#define __MINIWIN_NOT_IF(cond)           _MINIWIN_CAT(__MINIWIN_IF_, _MINIWIN_NOT(cond))
#define __MINIWIN_IF_ELSE(cond)          _MINIWIN_EXPAND(_MINIWIN_CAT(__MINIWIN_IF_ELSE_, _MINIWIN_BOOL(cond)))
