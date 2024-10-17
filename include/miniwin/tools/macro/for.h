#pragma once

#define _MW_FOR(f, count, ...) _MW_CAT(__MW_FOR_, count)(f, 0, __VA_ARGS__)

/*--------------------------------------------------
*            Internal macros(Dont use!)             |
---------------------------------------------------*/

#define __MW_FOR_0(f, i, ...)
#define __MW_FOR_1(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_0(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_2(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_1(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_3(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_2(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_4(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_3(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_5(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_4(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_6(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_5(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_7(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_6(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_8(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_7(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_9(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_8(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_10(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_9(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_11(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_10(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_12(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_11(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_13(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_12(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_14(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_13(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_15(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_14(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_16(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_15(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_17(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_16(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_18(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_17(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_19(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_18(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_20(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_19(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_21(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_20(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_22(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_21(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_23(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_22(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_24(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_23(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_25(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_24(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_26(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_25(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_27(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_26(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_28(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_27(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_29(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_28(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_30(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_29(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_31(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_30(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_32(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_31(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_33(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_32(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_34(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_33(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_35(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_34(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_36(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_35(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_37(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_36(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_38(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_37(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_39(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_38(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_40(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_39(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_41(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_40(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_42(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_41(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_43(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_42(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_44(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_43(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_45(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_44(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_46(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_45(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_47(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_46(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_48(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_47(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_49(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_48(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_50(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_49(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_51(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_50(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_52(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_51(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_53(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_52(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_54(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_53(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_55(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_54(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_56(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_55(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_57(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_56(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_58(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_57(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_59(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_58(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_60(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_59(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_61(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_60(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_62(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_61(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_63(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_62(f, _MW_INC(i), __VA_ARGS__)
#define __MW_FOR_64(f, i, ...) _MW_EXPAND(f(i, __VA_ARGS__)) __MW_FOR_63(f, _MW_INC(i), __VA_ARGS__)
