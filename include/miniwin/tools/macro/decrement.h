#pragma once

#define _MINIWIN_DEC(n) __MINIWIN_DEC(n)

/*--------------------------------------------------
*            Internal macros(Dont use!)             |
---------------------------------------------------*/
// Internal for _MINIWIN_DEC
#define __MINIWIN_DEC_0 0
# define __MINIWIN_DEC_1 0
# define __MINIWIN_DEC_2 1
# define __MINIWIN_DEC_3 2
# define __MINIWIN_DEC_4 3
# define __MINIWIN_DEC_5 4
# define __MINIWIN_DEC_6 5
# define __MINIWIN_DEC_7 6
# define __MINIWIN_DEC_8 7
# define __MINIWIN_DEC_9 8
# define __MINIWIN_DEC_10 9
# define __MINIWIN_DEC_11 10
# define __MINIWIN_DEC_12 11
# define __MINIWIN_DEC_13 12
# define __MINIWIN_DEC_14 13
# define __MINIWIN_DEC_15 14
# define __MINIWIN_DEC_16 15
# define __MINIWIN_DEC_17 16
# define __MINIWIN_DEC_18 17
# define __MINIWIN_DEC_19 18
# define __MINIWIN_DEC_20 19
# define __MINIWIN_DEC_21 20
# define __MINIWIN_DEC_22 21
# define __MINIWIN_DEC_23 22
# define __MINIWIN_DEC_24 23
# define __MINIWIN_DEC_25 24
# define __MINIWIN_DEC_26 25
# define __MINIWIN_DEC_27 26
# define __MINIWIN_DEC_28 27
# define __MINIWIN_DEC_29 28
# define __MINIWIN_DEC_30 29
# define __MINIWIN_DEC_31 30
# define __MINIWIN_DEC_32 31
# define __MINIWIN_DEC_33 32
# define __MINIWIN_DEC_34 33
# define __MINIWIN_DEC_35 34
# define __MINIWIN_DEC_36 35
# define __MINIWIN_DEC_37 36
# define __MINIWIN_DEC_38 37
# define __MINIWIN_DEC_39 38
# define __MINIWIN_DEC_40 39
# define __MINIWIN_DEC_41 40
# define __MINIWIN_DEC_42 41
# define __MINIWIN_DEC_43 42
# define __MINIWIN_DEC_44 43
# define __MINIWIN_DEC_45 44
# define __MINIWIN_DEC_46 45
# define __MINIWIN_DEC_47 46
# define __MINIWIN_DEC_48 47
# define __MINIWIN_DEC_49 48
# define __MINIWIN_DEC_50 49
# define __MINIWIN_DEC_51 50
# define __MINIWIN_DEC_52 51
# define __MINIWIN_DEC_53 52
# define __MINIWIN_DEC_54 53
# define __MINIWIN_DEC_55 54
# define __MINIWIN_DEC_56 55
# define __MINIWIN_DEC_57 56
# define __MINIWIN_DEC_58 57
# define __MINIWIN_DEC_59 58
# define __MINIWIN_DEC_60 59
# define __MINIWIN_DEC_61 60
# define __MINIWIN_DEC_62 61
# define __MINIWIN_DEC_63 62
# define __MINIWIN_DEC_64 63

#define _MINIWIN_PRIMITIVE_CAT(l, r) l ## r
#define _MINIWIN_CAT(l, r) _MINIWIN_PRIMITIVE_CAT(l, r)

#define __MINIWIN_DEC(n) _MINIWIN_CAT(__MINIWIN_DEC_, n)
