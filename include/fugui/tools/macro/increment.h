#pragma once

// increment(0~64)
#define _MINIWIN_INC(n) __MINIWIN_INC(n)

/*--------------------------------------------------
*            Internal macros(Dont use!)             |
---------------------------------------------------*/
// Internal for _MINIWIN_INC
# define __MINIWIN_INC_0 1
# define __MINIWIN_INC_1 2
# define __MINIWIN_INC_2 3
# define __MINIWIN_INC_3 4
# define __MINIWIN_INC_4 5
# define __MINIWIN_INC_5 6
# define __MINIWIN_INC_6 7
# define __MINIWIN_INC_7 8
# define __MINIWIN_INC_8 9
# define __MINIWIN_INC_9 10
# define __MINIWIN_INC_10 11
# define __MINIWIN_INC_11 12
# define __MINIWIN_INC_12 13
# define __MINIWIN_INC_13 14
# define __MINIWIN_INC_14 15
# define __MINIWIN_INC_15 16
# define __MINIWIN_INC_16 17
# define __MINIWIN_INC_17 18
# define __MINIWIN_INC_18 19
# define __MINIWIN_INC_19 20
# define __MINIWIN_INC_20 21
# define __MINIWIN_INC_21 22
# define __MINIWIN_INC_22 23
# define __MINIWIN_INC_23 24
# define __MINIWIN_INC_24 25
# define __MINIWIN_INC_25 26
# define __MINIWIN_INC_26 27
# define __MINIWIN_INC_27 28
# define __MINIWIN_INC_28 29
# define __MINIWIN_INC_29 30
# define __MINIWIN_INC_30 31
# define __MINIWIN_INC_31 32
# define __MINIWIN_INC_32 33
# define __MINIWIN_INC_33 34
# define __MINIWIN_INC_34 35
# define __MINIWIN_INC_35 36
# define __MINIWIN_INC_36 37
# define __MINIWIN_INC_37 38
# define __MINIWIN_INC_38 39
# define __MINIWIN_INC_39 40
# define __MINIWIN_INC_40 41
# define __MINIWIN_INC_41 42
# define __MINIWIN_INC_42 43
# define __MINIWIN_INC_43 44
# define __MINIWIN_INC_44 45
# define __MINIWIN_INC_45 46
# define __MINIWIN_INC_46 47
# define __MINIWIN_INC_47 48
# define __MINIWIN_INC_48 49
# define __MINIWIN_INC_49 50
# define __MINIWIN_INC_50 51
# define __MINIWIN_INC_51 52
# define __MINIWIN_INC_52 53
# define __MINIWIN_INC_53 54
# define __MINIWIN_INC_54 55
# define __MINIWIN_INC_55 56
# define __MINIWIN_INC_56 57
# define __MINIWIN_INC_57 58
# define __MINIWIN_INC_58 59
# define __MINIWIN_INC_59 60
# define __MINIWIN_INC_60 61
# define __MINIWIN_INC_61 62
# define __MINIWIN_INC_62 63
# define __MINIWIN_INC_63 64
# define __MINIWIN_INC_64 65

#define _MINIWIN_PRIMITIVE_CAT(l, r) l ## r
#define _MINIWIN_CAT(l, r) _MINIWIN_PRIMITIVE_CAT(l, r)

#define __MINIWIN_INC(n) _MINIWIN_CAT(__MINIWIN_INC_, n)
