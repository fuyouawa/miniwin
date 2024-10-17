#pragma once

// increment(0~64)
#define _MW_INC(n) __MW_INC(n)

/*--------------------------------------------------
*            Internal macros(Dont use!)             |
---------------------------------------------------*/
// Internal for _MW_INC
# define __MW_INC_0 1
# define __MW_INC_1 2
# define __MW_INC_2 3
# define __MW_INC_3 4
# define __MW_INC_4 5
# define __MW_INC_5 6
# define __MW_INC_6 7
# define __MW_INC_7 8
# define __MW_INC_8 9
# define __MW_INC_9 10
# define __MW_INC_10 11
# define __MW_INC_11 12
# define __MW_INC_12 13
# define __MW_INC_13 14
# define __MW_INC_14 15
# define __MW_INC_15 16
# define __MW_INC_16 17
# define __MW_INC_17 18
# define __MW_INC_18 19
# define __MW_INC_19 20
# define __MW_INC_20 21
# define __MW_INC_21 22
# define __MW_INC_22 23
# define __MW_INC_23 24
# define __MW_INC_24 25
# define __MW_INC_25 26
# define __MW_INC_26 27
# define __MW_INC_27 28
# define __MW_INC_28 29
# define __MW_INC_29 30
# define __MW_INC_30 31
# define __MW_INC_31 32
# define __MW_INC_32 33
# define __MW_INC_33 34
# define __MW_INC_34 35
# define __MW_INC_35 36
# define __MW_INC_36 37
# define __MW_INC_37 38
# define __MW_INC_38 39
# define __MW_INC_39 40
# define __MW_INC_40 41
# define __MW_INC_41 42
# define __MW_INC_42 43
# define __MW_INC_43 44
# define __MW_INC_44 45
# define __MW_INC_45 46
# define __MW_INC_46 47
# define __MW_INC_47 48
# define __MW_INC_48 49
# define __MW_INC_49 50
# define __MW_INC_50 51
# define __MW_INC_51 52
# define __MW_INC_52 53
# define __MW_INC_53 54
# define __MW_INC_54 55
# define __MW_INC_55 56
# define __MW_INC_56 57
# define __MW_INC_57 58
# define __MW_INC_58 59
# define __MW_INC_59 60
# define __MW_INC_60 61
# define __MW_INC_61 62
# define __MW_INC_62 63
# define __MW_INC_63 64
# define __MW_INC_64 65

#define __MW_INC(n) _MW_CAT(__MW_INC_, n)
