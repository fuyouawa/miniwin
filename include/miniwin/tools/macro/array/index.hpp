#pragma once
#include <miniwin/tools/macro/basic.hpp>

#define META_INDEX(i, ...)				META_EXPAND(META_CAT(_META_INDEX_,i)(__VA_ARGS__))
#define META_END(...)					META_INDEX(META_DEC(META_COUNT(__VA_ARGS__)), __VA_ARGS__)
#define META_BEGIN(...)					META_INDEX(0, __VA_ARGS__)

#define META_INDEX_IS_END(i, ...)		META_EQUAL(META_INC(i), META_COUNT(__VA_ARGS__))
#define META_INDEX_IS_NOT_END(i, ...)	META_NOT(META_INDEX_IS_END(i, __VA_ARGS__))
#define META_INDEX_IS_BEGIN(i, ...)		META_EQUAL(i, 0)

/*--------------------------------------------------
*            Internal macros(Dont use!)             |
---------------------------------------------------*/

#define _META_INDEX_0(_0,...) _0
#define _META_INDEX_1(_0,_1,...) _1
#define _META_INDEX_2(_0,_1,_2,...) _2
#define _META_INDEX_3(_0,_1,_2,_3,...) _3
#define _META_INDEX_4(_0,_1,_2,_3,_4,...) _4
#define _META_INDEX_5(_0,_1,_2,_3,_4,_5,...) _5
#define _META_INDEX_6(_0,_1,_2,_3,_4,_5,_6,...) _6
#define _META_INDEX_7(_0,_1,_2,_3,_4,_5,_6,_7,...) _7
#define _META_INDEX_8(_0,_1,_2,_3,_4,_5,_6,_7,_8,...) _8
#define _META_INDEX_9(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,...) _9
#define _META_INDEX_10(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,...) _10
#define _META_INDEX_11(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,...) _11
#define _META_INDEX_12(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,...) _12
#define _META_INDEX_13(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,...) _13
#define _META_INDEX_14(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,...) _14
#define _META_INDEX_15(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,...) _15
#define _META_INDEX_16(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,...) _16
#define _META_INDEX_17(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,...) _17
#define _META_INDEX_18(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,...) _18
#define _META_INDEX_19(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,...) _19
#define _META_INDEX_20(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,...) _20
#define _META_INDEX_21(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,...) _21
#define _META_INDEX_22(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,...) _22
#define _META_INDEX_23(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,...) _23
#define _META_INDEX_24(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,...) _24
#define _META_INDEX_25(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,...) _25
#define _META_INDEX_26(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,...) _26
#define _META_INDEX_27(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,...) _27
#define _META_INDEX_28(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,...) _28
#define _META_INDEX_29(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,...) _29
#define _META_INDEX_30(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,...) _30
#define _META_INDEX_31(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,...) _31
#define _META_INDEX_32(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,...) _32
#define _META_INDEX_33(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,...) _33
#define _META_INDEX_34(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,...) _34
#define _META_INDEX_35(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,...) _35
#define _META_INDEX_36(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,...) _36
#define _META_INDEX_37(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,...) _37
#define _META_INDEX_38(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,...) _38
#define _META_INDEX_39(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,...) _39
#define _META_INDEX_40(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,...) _40
#define _META_INDEX_41(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,...) _41
#define _META_INDEX_42(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,...) _42
#define _META_INDEX_43(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,...) _43
#define _META_INDEX_44(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,...) _44
#define _META_INDEX_45(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,...) _45
#define _META_INDEX_46(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,...) _46
#define _META_INDEX_47(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,...) _47
#define _META_INDEX_48(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,...) _48
#define _META_INDEX_49(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,...) _49
#define _META_INDEX_50(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,...) _50
#define _META_INDEX_51(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,...) _51
#define _META_INDEX_52(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,...) _52
#define _META_INDEX_53(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,...) _53
#define _META_INDEX_54(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,...) _54
#define _META_INDEX_55(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,...) _55
#define _META_INDEX_56(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,...) _56
#define _META_INDEX_57(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,...) _57
#define _META_INDEX_58(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,...) _58
#define _META_INDEX_59(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,...) _59
#define _META_INDEX_60(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,...) _60
#define _META_INDEX_61(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,...) _61
#define _META_INDEX_62(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,_62,...) _62
#define _META_INDEX_63(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,_62,_63,...) _63
#define _META_INDEX_64(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,_62,_63,_64,...) _64
#define _META_INDEX_65(x, ...) META_EXPAND(_META_INDEX_64(__VA_ARGS__))
#define _META_INDEX_66(x, ...) META_EXPAND(_META_INDEX_65(__VA_ARGS__))
#define _META_INDEX_67(x, ...) META_EXPAND(_META_INDEX_66(__VA_ARGS__))
#define _META_INDEX_68(x, ...) META_EXPAND(_META_INDEX_67(__VA_ARGS__))
#define _META_INDEX_69(x, ...) META_EXPAND(_META_INDEX_68(__VA_ARGS__))
#define _META_INDEX_70(x, ...) META_EXPAND(_META_INDEX_69(__VA_ARGS__))
#define _META_INDEX_71(x, ...) META_EXPAND(_META_INDEX_70(__VA_ARGS__))
#define _META_INDEX_72(x, ...) META_EXPAND(_META_INDEX_71(__VA_ARGS__))
#define _META_INDEX_73(x, ...) META_EXPAND(_META_INDEX_72(__VA_ARGS__))
#define _META_INDEX_74(x, ...) META_EXPAND(_META_INDEX_73(__VA_ARGS__))
#define _META_INDEX_75(x, ...) META_EXPAND(_META_INDEX_74(__VA_ARGS__))
#define _META_INDEX_76(x, ...) META_EXPAND(_META_INDEX_75(__VA_ARGS__))
#define _META_INDEX_77(x, ...) META_EXPAND(_META_INDEX_76(__VA_ARGS__))
#define _META_INDEX_78(x, ...) META_EXPAND(_META_INDEX_77(__VA_ARGS__))
#define _META_INDEX_79(x, ...) META_EXPAND(_META_INDEX_78(__VA_ARGS__))
#define _META_INDEX_80(x, ...) META_EXPAND(_META_INDEX_79(__VA_ARGS__))
#define _META_INDEX_81(x, ...) META_EXPAND(_META_INDEX_80(__VA_ARGS__))
#define _META_INDEX_82(x, ...) META_EXPAND(_META_INDEX_81(__VA_ARGS__))
#define _META_INDEX_83(x, ...) META_EXPAND(_META_INDEX_82(__VA_ARGS__))
#define _META_INDEX_84(x, ...) META_EXPAND(_META_INDEX_83(__VA_ARGS__))
#define _META_INDEX_85(x, ...) META_EXPAND(_META_INDEX_84(__VA_ARGS__))
#define _META_INDEX_86(x, ...) META_EXPAND(_META_INDEX_85(__VA_ARGS__))
#define _META_INDEX_87(x, ...) META_EXPAND(_META_INDEX_86(__VA_ARGS__))
#define _META_INDEX_88(x, ...) META_EXPAND(_META_INDEX_87(__VA_ARGS__))
#define _META_INDEX_89(x, ...) META_EXPAND(_META_INDEX_88(__VA_ARGS__))
#define _META_INDEX_90(x, ...) META_EXPAND(_META_INDEX_89(__VA_ARGS__))
#define _META_INDEX_91(x, ...) META_EXPAND(_META_INDEX_90(__VA_ARGS__))
#define _META_INDEX_92(x, ...) META_EXPAND(_META_INDEX_91(__VA_ARGS__))
#define _META_INDEX_93(x, ...) META_EXPAND(_META_INDEX_92(__VA_ARGS__))
#define _META_INDEX_94(x, ...) META_EXPAND(_META_INDEX_93(__VA_ARGS__))
#define _META_INDEX_95(x, ...) META_EXPAND(_META_INDEX_94(__VA_ARGS__))
#define _META_INDEX_96(x, ...) META_EXPAND(_META_INDEX_95(__VA_ARGS__))
#define _META_INDEX_97(x, ...) META_EXPAND(_META_INDEX_96(__VA_ARGS__))
#define _META_INDEX_98(x, ...) META_EXPAND(_META_INDEX_97(__VA_ARGS__))
#define _META_INDEX_99(x, ...) META_EXPAND(_META_INDEX_98(__VA_ARGS__))
#define _META_INDEX_100(x, ...) META_EXPAND(_META_INDEX_99(__VA_ARGS__))
#define _META_INDEX_101(x, ...) META_EXPAND(_META_INDEX_100(__VA_ARGS__))
#define _META_INDEX_102(x, ...) META_EXPAND(_META_INDEX_101(__VA_ARGS__))
#define _META_INDEX_103(x, ...) META_EXPAND(_META_INDEX_102(__VA_ARGS__))
#define _META_INDEX_104(x, ...) META_EXPAND(_META_INDEX_103(__VA_ARGS__))
#define _META_INDEX_105(x, ...) META_EXPAND(_META_INDEX_104(__VA_ARGS__))
#define _META_INDEX_106(x, ...) META_EXPAND(_META_INDEX_105(__VA_ARGS__))
#define _META_INDEX_107(x, ...) META_EXPAND(_META_INDEX_106(__VA_ARGS__))
#define _META_INDEX_108(x, ...) META_EXPAND(_META_INDEX_107(__VA_ARGS__))
#define _META_INDEX_109(x, ...) META_EXPAND(_META_INDEX_108(__VA_ARGS__))
#define _META_INDEX_110(x, ...) META_EXPAND(_META_INDEX_109(__VA_ARGS__))
#define _META_INDEX_111(x, ...) META_EXPAND(_META_INDEX_110(__VA_ARGS__))
#define _META_INDEX_112(x, ...) META_EXPAND(_META_INDEX_111(__VA_ARGS__))
#define _META_INDEX_113(x, ...) META_EXPAND(_META_INDEX_112(__VA_ARGS__))
#define _META_INDEX_114(x, ...) META_EXPAND(_META_INDEX_113(__VA_ARGS__))
#define _META_INDEX_115(x, ...) META_EXPAND(_META_INDEX_114(__VA_ARGS__))
#define _META_INDEX_116(x, ...) META_EXPAND(_META_INDEX_115(__VA_ARGS__))
#define _META_INDEX_117(x, ...) META_EXPAND(_META_INDEX_116(__VA_ARGS__))
#define _META_INDEX_118(x, ...) META_EXPAND(_META_INDEX_117(__VA_ARGS__))
#define _META_INDEX_119(x, ...) META_EXPAND(_META_INDEX_118(__VA_ARGS__))
#define _META_INDEX_120(x, ...) META_EXPAND(_META_INDEX_119(__VA_ARGS__))
#define _META_INDEX_121(x, ...) META_EXPAND(_META_INDEX_120(__VA_ARGS__))
#define _META_INDEX_122(x, ...) META_EXPAND(_META_INDEX_121(__VA_ARGS__))
#define _META_INDEX_123(x, ...) META_EXPAND(_META_INDEX_122(__VA_ARGS__))
#define _META_INDEX_124(x, ...) META_EXPAND(_META_INDEX_123(__VA_ARGS__))
#define _META_INDEX_125(x, ...) META_EXPAND(_META_INDEX_124(__VA_ARGS__))
#define _META_INDEX_126(x, ...) META_EXPAND(_META_INDEX_125(__VA_ARGS__))
#define _META_INDEX_127(x, ...) META_EXPAND(_META_INDEX_126(__VA_ARGS__))
#define _META_INDEX_128(x, ...) META_EXPAND(_META_INDEX_127(__VA_ARGS__))
#define _META_INDEX_129(x, ...) META_EXPAND(_META_INDEX_128(__VA_ARGS__))
#define _META_INDEX_130(x, ...) META_EXPAND(_META_INDEX_129(__VA_ARGS__))
#define _META_INDEX_131(x, ...) META_EXPAND(_META_INDEX_130(__VA_ARGS__))
#define _META_INDEX_132(x, ...) META_EXPAND(_META_INDEX_131(__VA_ARGS__))
#define _META_INDEX_133(x, ...) META_EXPAND(_META_INDEX_132(__VA_ARGS__))
#define _META_INDEX_134(x, ...) META_EXPAND(_META_INDEX_133(__VA_ARGS__))
#define _META_INDEX_135(x, ...) META_EXPAND(_META_INDEX_134(__VA_ARGS__))
#define _META_INDEX_136(x, ...) META_EXPAND(_META_INDEX_135(__VA_ARGS__))
#define _META_INDEX_137(x, ...) META_EXPAND(_META_INDEX_136(__VA_ARGS__))
#define _META_INDEX_138(x, ...) META_EXPAND(_META_INDEX_137(__VA_ARGS__))
#define _META_INDEX_139(x, ...) META_EXPAND(_META_INDEX_138(__VA_ARGS__))
#define _META_INDEX_140(x, ...) META_EXPAND(_META_INDEX_139(__VA_ARGS__))
#define _META_INDEX_141(x, ...) META_EXPAND(_META_INDEX_140(__VA_ARGS__))
#define _META_INDEX_142(x, ...) META_EXPAND(_META_INDEX_141(__VA_ARGS__))
#define _META_INDEX_143(x, ...) META_EXPAND(_META_INDEX_142(__VA_ARGS__))
#define _META_INDEX_144(x, ...) META_EXPAND(_META_INDEX_143(__VA_ARGS__))
#define _META_INDEX_145(x, ...) META_EXPAND(_META_INDEX_144(__VA_ARGS__))
#define _META_INDEX_146(x, ...) META_EXPAND(_META_INDEX_145(__VA_ARGS__))
#define _META_INDEX_147(x, ...) META_EXPAND(_META_INDEX_146(__VA_ARGS__))
#define _META_INDEX_148(x, ...) META_EXPAND(_META_INDEX_147(__VA_ARGS__))
#define _META_INDEX_149(x, ...) META_EXPAND(_META_INDEX_148(__VA_ARGS__))
#define _META_INDEX_150(x, ...) META_EXPAND(_META_INDEX_149(__VA_ARGS__))
#define _META_INDEX_151(x, ...) META_EXPAND(_META_INDEX_150(__VA_ARGS__))
#define _META_INDEX_152(x, ...) META_EXPAND(_META_INDEX_151(__VA_ARGS__))
#define _META_INDEX_153(x, ...) META_EXPAND(_META_INDEX_152(__VA_ARGS__))
#define _META_INDEX_154(x, ...) META_EXPAND(_META_INDEX_153(__VA_ARGS__))
#define _META_INDEX_155(x, ...) META_EXPAND(_META_INDEX_154(__VA_ARGS__))
#define _META_INDEX_156(x, ...) META_EXPAND(_META_INDEX_155(__VA_ARGS__))
#define _META_INDEX_157(x, ...) META_EXPAND(_META_INDEX_156(__VA_ARGS__))
#define _META_INDEX_158(x, ...) META_EXPAND(_META_INDEX_157(__VA_ARGS__))
#define _META_INDEX_159(x, ...) META_EXPAND(_META_INDEX_158(__VA_ARGS__))
#define _META_INDEX_160(x, ...) META_EXPAND(_META_INDEX_159(__VA_ARGS__))
#define _META_INDEX_161(x, ...) META_EXPAND(_META_INDEX_160(__VA_ARGS__))
#define _META_INDEX_162(x, ...) META_EXPAND(_META_INDEX_161(__VA_ARGS__))
#define _META_INDEX_163(x, ...) META_EXPAND(_META_INDEX_162(__VA_ARGS__))
#define _META_INDEX_164(x, ...) META_EXPAND(_META_INDEX_163(__VA_ARGS__))
#define _META_INDEX_165(x, ...) META_EXPAND(_META_INDEX_164(__VA_ARGS__))
#define _META_INDEX_166(x, ...) META_EXPAND(_META_INDEX_165(__VA_ARGS__))
#define _META_INDEX_167(x, ...) META_EXPAND(_META_INDEX_166(__VA_ARGS__))
#define _META_INDEX_168(x, ...) META_EXPAND(_META_INDEX_167(__VA_ARGS__))
#define _META_INDEX_169(x, ...) META_EXPAND(_META_INDEX_168(__VA_ARGS__))
#define _META_INDEX_170(x, ...) META_EXPAND(_META_INDEX_169(__VA_ARGS__))
#define _META_INDEX_171(x, ...) META_EXPAND(_META_INDEX_170(__VA_ARGS__))
#define _META_INDEX_172(x, ...) META_EXPAND(_META_INDEX_171(__VA_ARGS__))
#define _META_INDEX_173(x, ...) META_EXPAND(_META_INDEX_172(__VA_ARGS__))
#define _META_INDEX_174(x, ...) META_EXPAND(_META_INDEX_173(__VA_ARGS__))
#define _META_INDEX_175(x, ...) META_EXPAND(_META_INDEX_174(__VA_ARGS__))
#define _META_INDEX_176(x, ...) META_EXPAND(_META_INDEX_175(__VA_ARGS__))
#define _META_INDEX_177(x, ...) META_EXPAND(_META_INDEX_176(__VA_ARGS__))
#define _META_INDEX_178(x, ...) META_EXPAND(_META_INDEX_177(__VA_ARGS__))
#define _META_INDEX_179(x, ...) META_EXPAND(_META_INDEX_178(__VA_ARGS__))
#define _META_INDEX_180(x, ...) META_EXPAND(_META_INDEX_179(__VA_ARGS__))
#define _META_INDEX_181(x, ...) META_EXPAND(_META_INDEX_180(__VA_ARGS__))
#define _META_INDEX_182(x, ...) META_EXPAND(_META_INDEX_181(__VA_ARGS__))
#define _META_INDEX_183(x, ...) META_EXPAND(_META_INDEX_182(__VA_ARGS__))
#define _META_INDEX_184(x, ...) META_EXPAND(_META_INDEX_183(__VA_ARGS__))
#define _META_INDEX_185(x, ...) META_EXPAND(_META_INDEX_184(__VA_ARGS__))
#define _META_INDEX_186(x, ...) META_EXPAND(_META_INDEX_185(__VA_ARGS__))
#define _META_INDEX_187(x, ...) META_EXPAND(_META_INDEX_186(__VA_ARGS__))
#define _META_INDEX_188(x, ...) META_EXPAND(_META_INDEX_187(__VA_ARGS__))
#define _META_INDEX_189(x, ...) META_EXPAND(_META_INDEX_188(__VA_ARGS__))
#define _META_INDEX_190(x, ...) META_EXPAND(_META_INDEX_189(__VA_ARGS__))
#define _META_INDEX_191(x, ...) META_EXPAND(_META_INDEX_190(__VA_ARGS__))
#define _META_INDEX_192(x, ...) META_EXPAND(_META_INDEX_191(__VA_ARGS__))
#define _META_INDEX_193(x, ...) META_EXPAND(_META_INDEX_192(__VA_ARGS__))
#define _META_INDEX_194(x, ...) META_EXPAND(_META_INDEX_193(__VA_ARGS__))
#define _META_INDEX_195(x, ...) META_EXPAND(_META_INDEX_194(__VA_ARGS__))
#define _META_INDEX_196(x, ...) META_EXPAND(_META_INDEX_195(__VA_ARGS__))
#define _META_INDEX_197(x, ...) META_EXPAND(_META_INDEX_196(__VA_ARGS__))
#define _META_INDEX_198(x, ...) META_EXPAND(_META_INDEX_197(__VA_ARGS__))
#define _META_INDEX_199(x, ...) META_EXPAND(_META_INDEX_198(__VA_ARGS__))
#define _META_INDEX_200(x, ...) META_EXPAND(_META_INDEX_199(__VA_ARGS__))
#define _META_INDEX_201(x, ...) META_EXPAND(_META_INDEX_200(__VA_ARGS__))
#define _META_INDEX_202(x, ...) META_EXPAND(_META_INDEX_201(__VA_ARGS__))
#define _META_INDEX_203(x, ...) META_EXPAND(_META_INDEX_202(__VA_ARGS__))
#define _META_INDEX_204(x, ...) META_EXPAND(_META_INDEX_203(__VA_ARGS__))
#define _META_INDEX_205(x, ...) META_EXPAND(_META_INDEX_204(__VA_ARGS__))
#define _META_INDEX_206(x, ...) META_EXPAND(_META_INDEX_205(__VA_ARGS__))
#define _META_INDEX_207(x, ...) META_EXPAND(_META_INDEX_206(__VA_ARGS__))
#define _META_INDEX_208(x, ...) META_EXPAND(_META_INDEX_207(__VA_ARGS__))
#define _META_INDEX_209(x, ...) META_EXPAND(_META_INDEX_208(__VA_ARGS__))
#define _META_INDEX_210(x, ...) META_EXPAND(_META_INDEX_209(__VA_ARGS__))
#define _META_INDEX_211(x, ...) META_EXPAND(_META_INDEX_210(__VA_ARGS__))
#define _META_INDEX_212(x, ...) META_EXPAND(_META_INDEX_211(__VA_ARGS__))
#define _META_INDEX_213(x, ...) META_EXPAND(_META_INDEX_212(__VA_ARGS__))
#define _META_INDEX_214(x, ...) META_EXPAND(_META_INDEX_213(__VA_ARGS__))
#define _META_INDEX_215(x, ...) META_EXPAND(_META_INDEX_214(__VA_ARGS__))
#define _META_INDEX_216(x, ...) META_EXPAND(_META_INDEX_215(__VA_ARGS__))
#define _META_INDEX_217(x, ...) META_EXPAND(_META_INDEX_216(__VA_ARGS__))
#define _META_INDEX_218(x, ...) META_EXPAND(_META_INDEX_217(__VA_ARGS__))
#define _META_INDEX_219(x, ...) META_EXPAND(_META_INDEX_218(__VA_ARGS__))
#define _META_INDEX_220(x, ...) META_EXPAND(_META_INDEX_219(__VA_ARGS__))
#define _META_INDEX_221(x, ...) META_EXPAND(_META_INDEX_220(__VA_ARGS__))
#define _META_INDEX_222(x, ...) META_EXPAND(_META_INDEX_221(__VA_ARGS__))
#define _META_INDEX_223(x, ...) META_EXPAND(_META_INDEX_222(__VA_ARGS__))
#define _META_INDEX_224(x, ...) META_EXPAND(_META_INDEX_223(__VA_ARGS__))
#define _META_INDEX_225(x, ...) META_EXPAND(_META_INDEX_224(__VA_ARGS__))
#define _META_INDEX_226(x, ...) META_EXPAND(_META_INDEX_225(__VA_ARGS__))
#define _META_INDEX_227(x, ...) META_EXPAND(_META_INDEX_226(__VA_ARGS__))
#define _META_INDEX_228(x, ...) META_EXPAND(_META_INDEX_227(__VA_ARGS__))
#define _META_INDEX_229(x, ...) META_EXPAND(_META_INDEX_228(__VA_ARGS__))
#define _META_INDEX_230(x, ...) META_EXPAND(_META_INDEX_229(__VA_ARGS__))
#define _META_INDEX_231(x, ...) META_EXPAND(_META_INDEX_230(__VA_ARGS__))
#define _META_INDEX_232(x, ...) META_EXPAND(_META_INDEX_231(__VA_ARGS__))
#define _META_INDEX_233(x, ...) META_EXPAND(_META_INDEX_232(__VA_ARGS__))
#define _META_INDEX_234(x, ...) META_EXPAND(_META_INDEX_233(__VA_ARGS__))
#define _META_INDEX_235(x, ...) META_EXPAND(_META_INDEX_234(__VA_ARGS__))
#define _META_INDEX_236(x, ...) META_EXPAND(_META_INDEX_235(__VA_ARGS__))
#define _META_INDEX_237(x, ...) META_EXPAND(_META_INDEX_236(__VA_ARGS__))
#define _META_INDEX_238(x, ...) META_EXPAND(_META_INDEX_237(__VA_ARGS__))
#define _META_INDEX_239(x, ...) META_EXPAND(_META_INDEX_238(__VA_ARGS__))
#define _META_INDEX_240(x, ...) META_EXPAND(_META_INDEX_239(__VA_ARGS__))
#define _META_INDEX_241(x, ...) META_EXPAND(_META_INDEX_240(__VA_ARGS__))
#define _META_INDEX_242(x, ...) META_EXPAND(_META_INDEX_241(__VA_ARGS__))
#define _META_INDEX_243(x, ...) META_EXPAND(_META_INDEX_242(__VA_ARGS__))
#define _META_INDEX_244(x, ...) META_EXPAND(_META_INDEX_243(__VA_ARGS__))
#define _META_INDEX_245(x, ...) META_EXPAND(_META_INDEX_244(__VA_ARGS__))
#define _META_INDEX_246(x, ...) META_EXPAND(_META_INDEX_245(__VA_ARGS__))
#define _META_INDEX_247(x, ...) META_EXPAND(_META_INDEX_246(__VA_ARGS__))
#define _META_INDEX_248(x, ...) META_EXPAND(_META_INDEX_247(__VA_ARGS__))
#define _META_INDEX_249(x, ...) META_EXPAND(_META_INDEX_248(__VA_ARGS__))
#define _META_INDEX_250(x, ...) META_EXPAND(_META_INDEX_249(__VA_ARGS__))
#define _META_INDEX_251(x, ...) META_EXPAND(_META_INDEX_250(__VA_ARGS__))
#define _META_INDEX_252(x, ...) META_EXPAND(_META_INDEX_251(__VA_ARGS__))
#define _META_INDEX_253(x, ...) META_EXPAND(_META_INDEX_252(__VA_ARGS__))
#define _META_INDEX_254(x, ...) META_EXPAND(_META_INDEX_253(__VA_ARGS__))
#define _META_INDEX_255(x, ...) META_EXPAND(_META_INDEX_254(__VA_ARGS__))