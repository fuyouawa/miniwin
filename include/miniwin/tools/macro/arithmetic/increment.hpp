#pragma once
#include <miniwin/tools/macro/basic.hpp>

// increment(0~255)
#define META_INC(n) META_CAT(_META_INC_, n)


/*--------------------------------------------------
*            Internal macros(Dont use!)             |
---------------------------------------------------*/
// Internal for META_INC
# define _META_INC_0 1
# define _META_INC_1 2
# define _META_INC_2 3
# define _META_INC_3 4
# define _META_INC_4 5
# define _META_INC_5 6
# define _META_INC_6 7
# define _META_INC_7 8
# define _META_INC_8 9
# define _META_INC_9 10
# define _META_INC_10 11
# define _META_INC_11 12
# define _META_INC_12 13
# define _META_INC_13 14
# define _META_INC_14 15
# define _META_INC_15 16
# define _META_INC_16 17
# define _META_INC_17 18
# define _META_INC_18 19
# define _META_INC_19 20
# define _META_INC_20 21
# define _META_INC_21 22
# define _META_INC_22 23
# define _META_INC_23 24
# define _META_INC_24 25
# define _META_INC_25 26
# define _META_INC_26 27
# define _META_INC_27 28
# define _META_INC_28 29
# define _META_INC_29 30
# define _META_INC_30 31
# define _META_INC_31 32
# define _META_INC_32 33
# define _META_INC_33 34
# define _META_INC_34 35
# define _META_INC_35 36
# define _META_INC_36 37
# define _META_INC_37 38
# define _META_INC_38 39
# define _META_INC_39 40
# define _META_INC_40 41
# define _META_INC_41 42
# define _META_INC_42 43
# define _META_INC_43 44
# define _META_INC_44 45
# define _META_INC_45 46
# define _META_INC_46 47
# define _META_INC_47 48
# define _META_INC_48 49
# define _META_INC_49 50
# define _META_INC_50 51
# define _META_INC_51 52
# define _META_INC_52 53
# define _META_INC_53 54
# define _META_INC_54 55
# define _META_INC_55 56
# define _META_INC_56 57
# define _META_INC_57 58
# define _META_INC_58 59
# define _META_INC_59 60
# define _META_INC_60 61
# define _META_INC_61 62
# define _META_INC_62 63
# define _META_INC_63 64
# define _META_INC_64 65
# define _META_INC_65 66
# define _META_INC_66 67
# define _META_INC_67 68
# define _META_INC_68 69
# define _META_INC_69 70
# define _META_INC_70 71
# define _META_INC_71 72
# define _META_INC_72 73
# define _META_INC_73 74
# define _META_INC_74 75
# define _META_INC_75 76
# define _META_INC_76 77
# define _META_INC_77 78
# define _META_INC_78 79
# define _META_INC_79 80
# define _META_INC_80 81
# define _META_INC_81 82
# define _META_INC_82 83
# define _META_INC_83 84
# define _META_INC_84 85
# define _META_INC_85 86
# define _META_INC_86 87
# define _META_INC_87 88
# define _META_INC_88 89
# define _META_INC_89 90
# define _META_INC_90 91
# define _META_INC_91 92
# define _META_INC_92 93
# define _META_INC_93 94
# define _META_INC_94 95
# define _META_INC_95 96
# define _META_INC_96 97
# define _META_INC_97 98
# define _META_INC_98 99
# define _META_INC_99 100
# define _META_INC_100 101
# define _META_INC_101 102
# define _META_INC_102 103
# define _META_INC_103 104
# define _META_INC_104 105
# define _META_INC_105 106
# define _META_INC_106 107
# define _META_INC_107 108
# define _META_INC_108 109
# define _META_INC_109 110
# define _META_INC_110 111
# define _META_INC_111 112
# define _META_INC_112 113
# define _META_INC_113 114
# define _META_INC_114 115
# define _META_INC_115 116
# define _META_INC_116 117
# define _META_INC_117 118
# define _META_INC_118 119
# define _META_INC_119 120
# define _META_INC_120 121
# define _META_INC_121 122
# define _META_INC_122 123
# define _META_INC_123 124
# define _META_INC_124 125
# define _META_INC_125 126
# define _META_INC_126 127
# define _META_INC_127 128
# define _META_INC_128 129
# define _META_INC_129 130
# define _META_INC_130 131
# define _META_INC_131 132
# define _META_INC_132 133
# define _META_INC_133 134
# define _META_INC_134 135
# define _META_INC_135 136
# define _META_INC_136 137
# define _META_INC_137 138
# define _META_INC_138 139
# define _META_INC_139 140
# define _META_INC_140 141
# define _META_INC_141 142
# define _META_INC_142 143
# define _META_INC_143 144
# define _META_INC_144 145
# define _META_INC_145 146
# define _META_INC_146 147
# define _META_INC_147 148
# define _META_INC_148 149
# define _META_INC_149 150
# define _META_INC_150 151
# define _META_INC_151 152
# define _META_INC_152 153
# define _META_INC_153 154
# define _META_INC_154 155
# define _META_INC_155 156
# define _META_INC_156 157
# define _META_INC_157 158
# define _META_INC_158 159
# define _META_INC_159 160
# define _META_INC_160 161
# define _META_INC_161 162
# define _META_INC_162 163
# define _META_INC_163 164
# define _META_INC_164 165
# define _META_INC_165 166
# define _META_INC_166 167
# define _META_INC_167 168
# define _META_INC_168 169
# define _META_INC_169 170
# define _META_INC_170 171
# define _META_INC_171 172
# define _META_INC_172 173
# define _META_INC_173 174
# define _META_INC_174 175
# define _META_INC_175 176
# define _META_INC_176 177
# define _META_INC_177 178
# define _META_INC_178 179
# define _META_INC_179 180
# define _META_INC_180 181
# define _META_INC_181 182
# define _META_INC_182 183
# define _META_INC_183 184
# define _META_INC_184 185
# define _META_INC_185 186
# define _META_INC_186 187
# define _META_INC_187 188
# define _META_INC_188 189
# define _META_INC_189 190
# define _META_INC_190 191
# define _META_INC_191 192
# define _META_INC_192 193
# define _META_INC_193 194
# define _META_INC_194 195
# define _META_INC_195 196
# define _META_INC_196 197
# define _META_INC_197 198
# define _META_INC_198 199
# define _META_INC_199 200
# define _META_INC_200 201
# define _META_INC_201 202
# define _META_INC_202 203
# define _META_INC_203 204
# define _META_INC_204 205
# define _META_INC_205 206
# define _META_INC_206 207
# define _META_INC_207 208
# define _META_INC_208 209
# define _META_INC_209 210
# define _META_INC_210 211
# define _META_INC_211 212
# define _META_INC_212 213
# define _META_INC_213 214
# define _META_INC_214 215
# define _META_INC_215 216
# define _META_INC_216 217
# define _META_INC_217 218
# define _META_INC_218 219
# define _META_INC_219 220
# define _META_INC_220 221
# define _META_INC_221 222
# define _META_INC_222 223
# define _META_INC_223 224
# define _META_INC_224 225
# define _META_INC_225 226
# define _META_INC_226 227
# define _META_INC_227 228
# define _META_INC_228 229
# define _META_INC_229 230
# define _META_INC_230 231
# define _META_INC_231 232
# define _META_INC_232 233
# define _META_INC_233 234
# define _META_INC_234 235
# define _META_INC_235 236
# define _META_INC_236 237
# define _META_INC_237 238
# define _META_INC_238 239
# define _META_INC_239 240
# define _META_INC_240 241
# define _META_INC_241 242
# define _META_INC_242 243
# define _META_INC_243 244
# define _META_INC_244 245
# define _META_INC_245 246
# define _META_INC_246 247
# define _META_INC_247 248
# define _META_INC_248 249
# define _META_INC_249 250
# define _META_INC_250 251
# define _META_INC_251 252
# define _META_INC_252 253
# define _META_INC_253 254
# define _META_INC_254 255
# define _META_INC_255 256