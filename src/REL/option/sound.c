#include "REL/option.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/msm.h"
#include "game/process.h"
#include "game/window.h"

#include "dolphin.h"
#include "math.h"

typedef struct {
    /* 0x000 */ omObjData *unk00[26];
    /* 0x068 */ UnkWindowDataStruct *unk68[13];
    /* 0x09C */ s32 unk9C;
    /* 0x0A0 */ s16 unkA0[19];
    /* 0x0C6 */ char unkC6[2];
    /* 0x0C8 */ s32 unkC8;
    /* 0x0CC */ s32 unkCC;
    /* 0x0D0 */ s32 unkD0;
    /* 0x0D4 */ s32 unkD4;
    /* 0x0D8 */ s32 unkD8;
    /* 0x0DC */ s32 unkDC;
    /* 0x0E0 */ s16 unkE0;
    /* 0x0E2 */ char unkE2[2];
    /* 0x0E4 */ s32 unkE4;
    /* 0x0E8 */ s32 unkE8;
    /* 0x0EC */ s32 unkEC;
    /* 0x0F0 */ s16 unkF0;
    /* 0x0F2 */ s16 unkF2;
    /* 0x0F4 */ s16 unkF4;
    /* 0x0F6 */ s16 unkF6;
    /* 0x0F8 */ s32 unkF8;
    /* 0x0FC */ s32 unkFC;
    /* 0x100 */ s32 unk100;
    /* 0x104 */ float unk104;
    /* 0x108 */ float unk108;
    /* 0x10C */ Process *unk10C;
} UnkSoundDataStruct00; // Size 0x110

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ float unk10;
} UnkSoundDataStruct01; // Size 0x14

typedef struct {
    /* 0x00 */ BOOL unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s32 unk0C;
} lbl_1_rodata_1E0_Data; // Size 0x10

static void fn_1_43E8(omObjData *arg0);
static void fn_1_4658(omObjData *arg0);
static void fn_1_4A7C(omObjData *arg0);
static void fn_1_4E50(omObjData *arg0);
static void fn_1_578C(omObjData *arg0);
static void fn_1_6044(omObjData *arg0, s32 arg1);
static void fn_1_613C(omObjData *arg0);
static omObjData *fn_1_61A0(void);
static void fn_1_629C(omObjData *arg0);
static omObjData *fn_1_62F0(void);
static void fn_1_63EC(omObjData *arg0);
static omObjData *fn_1_6440(void);
static void fn_1_64D4(omObjData *arg0);
static omObjData *fn_1_6528(s32 arg0, s32 arg1);
static void fn_1_6640(omObjData *arg0);
static void fn_1_6694(omObjData *arg0);
static void fn_1_66CC(omObjData *arg0);
static void fn_1_6704(omObjData *arg0);
static void fn_1_67C8(omObjData *arg0);
static void fn_1_6828(omObjData *arg0);
static void fn_1_6A0C(omObjData *arg0);
static void fn_1_6A80(omObjData *arg0);
static void fn_1_6C5C(omObjData *arg0);
static void fn_1_6CD0(omObjData *arg0, s32 arg1);
static void fn_1_6EA4(omObjData *arg0);
static void fn_1_6F48(omObjData *arg0, s32 arg1);
static void fn_1_711C(omObjData *arg0);
static omObjData *fn_1_71C0(s32 arg0);
static void fn_1_72A8(omObjData *arg0);
static void fn_1_7310(omObjData *arg0);
static void fn_1_7710(omObjData *arg0, s32 arg1, s32 arg2, s32 arg3);
static void fn_1_78A0(omObjData *arg0);
static void fn_1_7900(omObjData *arg0);
static void fn_1_793C(void);
static void fn_1_7F00(omObjData *arg0);
static void fn_1_8048(omObjData *arg0);

omObjData *lbl_1_bss_38;

static const s32 lbl_1_rodata_1A8[] = {
    MAKE_MESSID(47,  70),
    MAKE_MESSID(47,  81),
    MAKE_MESSID(47, 172),
    MAKE_MESSID(47,  92),
    MAKE_MESSID(47, 101),
    MAKE_MESSID(47, 109),
    MAKE_MESSID(47, 119),
    MAKE_MESSID(47, 173),
    MAKE_MESSID(47, 174),
    MAKE_MESSID(47, 129),
    MAKE_MESSID(47, 140),
    MAKE_MESSID(47, 149),
    MAKE_MESSID(47, 156),
    MAKE_MESSID(47, 176)
};

static const lbl_1_rodata_1E0_Data lbl_1_rodata_1E0[14][10] = {
    {
        {  TRUE, MAKE_MESSID(47, 71),  1,  0, 20 },
        {  TRUE, MAKE_MESSID(47, 72),  2, 79, 43 },
        {  TRUE, MAKE_MESSID(47, 73),  3, 81, 44 },
        {  TRUE, MAKE_MESSID(47, 74), 29, 80, 45 },
        {  TRUE, MAKE_MESSID(47, 76), 30, 82, 47 },
        {  TRUE, MAKE_MESSID(47, 78),  1,  0, 12 },
        {  TRUE, MAKE_MESSID(47, 77),  4, 83, 48 },
        {  TRUE, MAKE_MESSID(47, 80), 11, 90, 40 },
        { FALSE, MAKE_MESSID(47, 69),  0,  0,  0 },
        { FALSE, MAKE_MESSID(47, 69),  0,  0,  0 }
    },
    {
        {  TRUE, MAKE_MESSID(47,  79),  1, 0,  5 },
        {  TRUE, MAKE_MESSID(47, 170), 33, 0, 12 },
        {  TRUE, MAKE_MESSID(47,  82), 33, 0,  7 },
        {  TRUE, MAKE_MESSID(47,  83), 33, 0,  4 },
        {  TRUE, MAKE_MESSID(47, 171), 33, 0, 10 },
        {  TRUE, MAKE_MESSID(47,  84), 33, 0,  9 },
        {  TRUE, MAKE_MESSID(47,  85), 33, 0,  1 },
        {  TRUE, MAKE_MESSID(47,  86), 33, 0,  3 },
        {  TRUE, MAKE_MESSID(47,  87), 33, 0,  2 },
        { FALSE, MAKE_MESSID(47,  69),  0, 0,  0 }
    },
    {
        { TRUE, MAKE_MESSID(47,  88), 33,  0,  5 },
        { TRUE, MAKE_MESSID(47,  89), 33,  0,  6 },
        { TRUE, MAKE_MESSID(47,  90), 33,  0, 11 },
        { TRUE, MAKE_MESSID(47,  91), 33,  0,  8 },
        { TRUE, MAKE_MESSID(47, 125),  1,  0,  2 },
        { TRUE, MAKE_MESSID(47, 126),  1,  0,  6 },
        { TRUE, MAKE_MESSID(47, 127),  1,  0,  9 },
        { TRUE, MAKE_MESSID(47, 128),  1,  0, 10 },
        { TRUE, MAKE_MESSID(47, 124), 12, 93, 49 },
        { TRUE, MAKE_MESSID(47, 123), 12, 93, 50 }
    },
    {
        {  TRUE, MAKE_MESSID(47, 93), 5, 84, 13 },
        {  TRUE, MAKE_MESSID(47, 94), 5, 84, 14 },
        {  TRUE, MAKE_MESSID(47, 95), 5, 84, 15 },
        {  TRUE, MAKE_MESSID(47, 96), 5, 84, 16 },
        { FALSE, MAKE_MESSID(47, 69), 0,  0,  0 },
        { FALSE, MAKE_MESSID(47, 69), 0,  0,  0 },
        { FALSE, MAKE_MESSID(47, 69), 0,  0,  0 },
        { FALSE, MAKE_MESSID(47, 69), 0,  0,  0 },
        { FALSE, MAKE_MESSID(47, 69), 0,  0,  0 },
        { FALSE, MAKE_MESSID(47, 69), 0,  0,  0 }
    },
    {
        {  TRUE, MAKE_MESSID(47,  97), 6, 85, 17 },
        {  TRUE, MAKE_MESSID(47,  98), 6, 85, 18 },
        {  TRUE, MAKE_MESSID(47,  99), 6, 85, 19 },
        {  TRUE, MAKE_MESSID(47, 100), 6, 85, 20 },
        { FALSE, MAKE_MESSID(47,  69), 0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69), 0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69), 0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69), 0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69), 0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69), 0,  0,  0 }
    },
    {
        {  TRUE, MAKE_MESSID(47, 102), 7, 86, 21 },
        {  TRUE, MAKE_MESSID(47, 103), 7, 86, 22 },
        {  TRUE, MAKE_MESSID(47, 104), 7, 86, 23 },
        {  TRUE, MAKE_MESSID(47, 105), 7, 86, 24 },
        {  TRUE, MAKE_MESSID(47, 106), 7, 86, 25 },
        {  TRUE, MAKE_MESSID(47, 107), 7, 86, 26 },
        {  TRUE, MAKE_MESSID(47, 108), 7, 86, 27 },
        { FALSE, MAKE_MESSID(47,  69), 0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69), 0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69), 0,  0,  0 }
    },
    {
        {  TRUE, MAKE_MESSID(47, 110), 8, 87, 28 },
        {  TRUE, MAKE_MESSID(47, 111), 8, 87, 30 },
        {  TRUE, MAKE_MESSID(47, 112), 8, 87, 29 },
        {  TRUE, MAKE_MESSID(47, 113), 8, 87, 31 },
        {  TRUE, MAKE_MESSID(47, 114), 8, 87, 32 },
        { FALSE, MAKE_MESSID(47,  69), 0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69), 0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69), 0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69), 0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69), 0,  0,  0 }
    },
    {
        {  TRUE, MAKE_MESSID(47, 115), 9, 88, 33 },
        {  TRUE, MAKE_MESSID(47, 116), 9, 88, 34 },
        {  TRUE, MAKE_MESSID(47, 117), 9, 88, 35 },
        {  TRUE, MAKE_MESSID(47, 118), 9, 88, 36 },
        { FALSE, MAKE_MESSID(47,  69), 0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69), 0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69), 0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69), 0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69), 0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69), 0,  0,  0 }
    },
    {
        {  TRUE, MAKE_MESSID(47, 120), 10, 89, 37 },
        {  TRUE, MAKE_MESSID(47, 121), 10, 89, 38 },
        {  TRUE, MAKE_MESSID(47, 122), 10, 89, 39 },
        { FALSE, MAKE_MESSID(47,  69),  0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69),  0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69),  0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69),  0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69),  0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69),  0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69),  0,  0,  0 }
    },
    {
        { TRUE, MAKE_MESSID(47, 130), 13,  94, 59 },
        { TRUE, MAKE_MESSID(47, 131), 13,  94, 57 },
        { TRUE, MAKE_MESSID(47, 132), 14,  95, 67 },
        { TRUE, MAKE_MESSID(47, 133), 15,  96, 68 },
        { TRUE, MAKE_MESSID(47, 134), 16,  97, 69 },
        { TRUE, MAKE_MESSID(47, 135), 17,  98, 70 },
        { TRUE, MAKE_MESSID(47, 136), 18,  99, 71 },
        { TRUE, MAKE_MESSID(47, 137), 19, 100, 72 },
        { TRUE, MAKE_MESSID(47, 138), 20, 101, 73 },
        { TRUE, MAKE_MESSID(47, 139), 21, 102, 74 }
    },
    {
        {  TRUE, MAKE_MESSID(47, 141), 22, 103, 75 },
        {  TRUE, MAKE_MESSID(47, 142), 23, 104, 76 },
        {  TRUE, MAKE_MESSID(47, 143), 24, 105, 77 },
        {  TRUE, MAKE_MESSID(47, 144), 13,  94, 58 },
        {  TRUE, MAKE_MESSID(47, 175), 13,  94, 60 },
        {  TRUE, MAKE_MESSID(47, 145),  1,   0,  1 },
        {  TRUE, MAKE_MESSID(47, 146),  1,   0,  3 },
        {  TRUE, MAKE_MESSID(47, 147),  1,   0,  4 },
        {  TRUE, MAKE_MESSID(47, 148),  1,   0, 11 },
        { FALSE, MAKE_MESSID(47,  69),  0,   0,  0 }
    },
    {
        {  TRUE, MAKE_MESSID(47, 152), 25, 106, 61 },
        {  TRUE, MAKE_MESSID(47, 150), 25, 106, 62 },
        {  TRUE, MAKE_MESSID(47, 151), 25, 106, 63 },
        {  TRUE, MAKE_MESSID(47, 155), 26, 107, 65 },
        {  TRUE, MAKE_MESSID(47, 153), 26, 107, 64 },
        {  TRUE, MAKE_MESSID(47, 154), 26, 107, 66 },
        {  TRUE, MAKE_MESSID(47, 164),  1,   0, 13 },
        { FALSE, MAKE_MESSID(47,  69),  0,   0,  0 },
        { FALSE, MAKE_MESSID(47,  69),  0,   0,  0 },
        { FALSE, MAKE_MESSID(47,  69),  0,   0,  0 }
    },
    {
        {  TRUE, MAKE_MESSID(47, 157), 27, 108, 51 },
        {  TRUE, MAKE_MESSID(47, 158), 27, 108, 53 },
        {  TRUE, MAKE_MESSID(47, 159), 27, 108, 54 },
        {  TRUE, MAKE_MESSID(47, 160), 27, 108, 52 },
        {  TRUE, MAKE_MESSID(47, 161), 27, 108, 55 },
        {  TRUE, MAKE_MESSID(47, 162), 27, 108, 56 },
        {  TRUE, MAKE_MESSID(47, 163),  1,   0,  7 },
        {  TRUE, MAKE_MESSID(47, 165),  1,   0, 22 },
        { FALSE, MAKE_MESSID(47,  69),  0,   0,  0 },
        { FALSE, MAKE_MESSID(47,  69),  0,   0,  0 }
    },
    {
        {  TRUE, MAKE_MESSID(47, 177), 32, 92, 46 },
        {  TRUE, MAKE_MESSID(47, 178), 31, 91, 41 },
        { FALSE, MAKE_MESSID(47,  69),  0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69),  0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69),  0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69),  0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69),  0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69),  0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69),  0,  0,  0 },
        { FALSE, MAKE_MESSID(47,  69),  0,  0,  0 }
    }
};

static const s32 lbl_1_rodata_AA0[12] = {
    MAKE_MESSID( 0,  0),
    MAKE_MESSID( 0,  1),
    MAKE_MESSID( 0,  2),
    MAKE_MESSID( 0,  3),
    MAKE_MESSID( 0,  4),
    MAKE_MESSID( 0,  5),
    MAKE_MESSID( 0,  6),
    MAKE_MESSID( 0,  7),
    MAKE_MESSID(47, 34),
    MAKE_MESSID(47, 44),
    MAKE_MESSID(47, 55),
    MAKE_MESSID(47, 62)
};

static const lbl_1_rodata_1E0_Data lbl_1_rodata_AD0[12][10] = {
    {
        {  TRUE, MAKE_MESSID(47, 26), 28, 109, 2217 },
        {  TRUE, MAKE_MESSID(47, 27), 28, 109, 2219 },
        {  TRUE, MAKE_MESSID(47, 28), 28, 109, 2216 },
        {  TRUE, MAKE_MESSID(47, 29), 28, 109, 2223 },
        {  TRUE, MAKE_MESSID(47, 30), 28, 109, 2220 },
        {  TRUE, MAKE_MESSID(47, 31), 28, 109, 2221 },
        {  TRUE, MAKE_MESSID(47, 32), 28, 109, 2222 },
        {  TRUE, MAKE_MESSID(47, 33), 28, 109, 2218 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,    0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,    0 }
    },
    {
        {  TRUE, MAKE_MESSID(47, 26), 28, 109, 2208 },
        {  TRUE, MAKE_MESSID(47, 27), 28, 109, 2210 },
        {  TRUE, MAKE_MESSID(47, 28), 28, 109, 2207 },
        {  TRUE, MAKE_MESSID(47, 29), 28, 109, 2214 },
        {  TRUE, MAKE_MESSID(47, 30), 28, 109, 2211 },
        {  TRUE, MAKE_MESSID(47, 31), 28, 109, 2212 },
        {  TRUE, MAKE_MESSID(47, 32), 28, 109, 2213 },
        {  TRUE, MAKE_MESSID(47, 33), 28, 109, 2209 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,    0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,    0 }
    },
    {
        {  TRUE, MAKE_MESSID(47, 26), 28, 109, 2226 },
        {  TRUE, MAKE_MESSID(47, 27), 28, 109, 2228 },
        {  TRUE, MAKE_MESSID(47, 28), 28, 109, 2225 },
        {  TRUE, MAKE_MESSID(47, 29), 28, 109, 2232 },
        {  TRUE, MAKE_MESSID(47, 30), 28, 109, 2229 },
        {  TRUE, MAKE_MESSID(47, 31), 28, 109, 2230 },
        {  TRUE, MAKE_MESSID(47, 32), 28, 109, 2231 },
        {  TRUE, MAKE_MESSID(47, 33), 28, 109, 2227 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,    0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,    0 }
    },
    {
        {  TRUE, MAKE_MESSID(47, 26), 28, 109, 2253 },
        {  TRUE, MAKE_MESSID(47, 27), 28, 109, 2255 },
        {  TRUE, MAKE_MESSID(47, 28), 28, 109, 2252 },
        {  TRUE, MAKE_MESSID(47, 29), 28, 109, 2259 },
        {  TRUE, MAKE_MESSID(47, 30), 28, 109, 2256 },
        {  TRUE, MAKE_MESSID(47, 31), 28, 109, 2257 },
        {  TRUE, MAKE_MESSID(47, 32), 28, 109, 2258 },
        {  TRUE, MAKE_MESSID(47, 33), 28, 109, 2254 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,    0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,    0 }
    },
    {
        {  TRUE, MAKE_MESSID(47, 26), 28, 109, 2244 },
        {  TRUE, MAKE_MESSID(47, 27), 28, 109, 2246 },
        {  TRUE, MAKE_MESSID(47, 28), 28, 109, 2243 },
        {  TRUE, MAKE_MESSID(47, 29), 28, 109, 2250 },
        {  TRUE, MAKE_MESSID(47, 30), 28, 109, 2247 },
        {  TRUE, MAKE_MESSID(47, 31), 28, 109, 2248 },
        {  TRUE, MAKE_MESSID(47, 32), 28, 109, 2249 },
        {  TRUE, MAKE_MESSID(47, 33), 28, 109, 2245 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,    0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,    0 }
    },
    {
        {  TRUE, MAKE_MESSID(47, 26), 28, 109, 2199 },
        {  TRUE, MAKE_MESSID(47, 27), 28, 109, 2201 },
        {  TRUE, MAKE_MESSID(47, 28), 28, 109, 2198 },
        {  TRUE, MAKE_MESSID(47, 29), 28, 109, 2205 },
        {  TRUE, MAKE_MESSID(47, 30), 28, 109, 2202 },
        {  TRUE, MAKE_MESSID(47, 31), 28, 109, 2203 },
        {  TRUE, MAKE_MESSID(47, 32), 28, 109, 2204 },
        {  TRUE, MAKE_MESSID(47, 33), 28, 109, 2200 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,    0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,    0 }
    },
    {
        {  TRUE, MAKE_MESSID(47, 26), 28, 109, 2190 },
        {  TRUE, MAKE_MESSID(47, 27), 28, 109, 2192 },
        {  TRUE, MAKE_MESSID(47, 28), 28, 109, 2189 },
        {  TRUE, MAKE_MESSID(47, 29), 28, 109, 2196 },
        {  TRUE, MAKE_MESSID(47, 30), 28, 109, 2193 },
        {  TRUE, MAKE_MESSID(47, 31), 28, 109, 2194 },
        {  TRUE, MAKE_MESSID(47, 32), 28, 109, 2195 },
        {  TRUE, MAKE_MESSID(47, 33), 28, 109, 2191 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,    0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,    0 }
    },
    {
        {  TRUE, MAKE_MESSID(47, 26), 28, 109, 2235 },
        {  TRUE, MAKE_MESSID(47, 27), 28, 109, 2237 },
        {  TRUE, MAKE_MESSID(47, 28), 28, 109, 2234 },
        {  TRUE, MAKE_MESSID(47, 29), 28, 109, 2241 },
        {  TRUE, MAKE_MESSID(47, 30), 28, 109, 2238 },
        {  TRUE, MAKE_MESSID(47, 31), 28, 109, 2239 },
        {  TRUE, MAKE_MESSID(47, 32), 28, 109, 2240 },
        {  TRUE, MAKE_MESSID(47, 33), 28, 109, 2236 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,    0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,    0 }
    },
    {
        {  TRUE, MAKE_MESSID(47, 35), 28, 109, 54 },
        {  TRUE, MAKE_MESSID(47, 36), 28, 109, 55 },
        {  TRUE, MAKE_MESSID(47, 37), 28, 109, 56 },
        {  TRUE, MAKE_MESSID(47, 38), 28, 109, 67 },
        {  TRUE, MAKE_MESSID(47, 39), 28, 109, 68 },
        {  TRUE, MAKE_MESSID(47, 40), 28, 109, 69 },
        {  TRUE, MAKE_MESSID(47, 41), 28, 109, 64 },
        {  TRUE, MAKE_MESSID(47, 42), 28, 109, 65 },
        {  TRUE, MAKE_MESSID(47, 43), 28, 109, 66 },
        { FALSE, MAKE_MESSID(47, 24),  0,   0,  0 }
    },
    {
        { TRUE, MAKE_MESSID(47, 45), 28, 109, 75 },
        { TRUE, MAKE_MESSID(47, 46), 28, 109, 76 },
        { TRUE, MAKE_MESSID(47, 47), 28, 109, 77 },
        { TRUE, MAKE_MESSID(47, 48), 28, 109, 70 },
        { TRUE, MAKE_MESSID(47, 49), 28, 109, 71 },
        { TRUE, MAKE_MESSID(47, 50), 28, 109, 72 },
        { TRUE, MAKE_MESSID(47, 51), 28, 109, 58 },
        { TRUE, MAKE_MESSID(47, 52), 28, 109, 59 },
        { TRUE, MAKE_MESSID(47, 53), 28, 109, 60 },
        { TRUE, MAKE_MESSID(47, 54), 28, 109, 61 }
    },
    {
        {  TRUE, MAKE_MESSID(47, 56), 28, 109, 62 },
        {  TRUE, MAKE_MESSID(47, 57), 28, 109, 63 },
        {  TRUE, MAKE_MESSID(47, 58), 28, 109, 79 },
        {  TRUE, MAKE_MESSID(47, 59), 28, 109, 80 },
        {  TRUE, MAKE_MESSID(47, 60), 28, 109, 73 },
        {  TRUE, MAKE_MESSID(47, 61), 28, 109, 74 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,  0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,  0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,  0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,  0 }
    },
    {
        {  TRUE, MAKE_MESSID(47, 63), 28, 109, 36 },
        {  TRUE, MAKE_MESSID(47, 64), 28, 109, 37 },
        {  TRUE, MAKE_MESSID(47, 65), 28, 109, 38 },
        {  TRUE, MAKE_MESSID(47, 67), 28, 109, 40 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,  0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,  0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,  0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,  0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,  0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109,  0 }
    }
};

static s32 lbl_1_data_118[14] = {
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 0
};

static omObjFunc lbl_1_data_150[] = {
    NULL,
    fn_1_43E8,
    fn_1_4658,
    fn_1_4A7C,
    fn_1_4E50,
    fn_1_578C
};

static s32 lbl_1_data_168[] = {
    MAKE_MESSID(47,  8),
    MAKE_MESSID(47, 10),
    MAKE_MESSID(47,  9)
};

omObjData *fn_1_4028(void) {
    omObjData *temp_r29;
    UnkSoundDataStruct00 *temp_r3;
    s32 i;

    temp_r29 = omAddObjEx(lbl_1_bss_8, 1003, 0, 0, 1, NULL);
    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkSoundDataStruct00), MEMORY_DEFAULT_NUM);
    temp_r29->data = temp_r3;
    temp_r3->unkCC = 0;
    temp_r3->unkE8 = 0;
    temp_r3->unkE4 = 0;
    temp_r3->unkF0 = -2;
    temp_r3->unkF2 = -1;
    temp_r3->unkF4 = -1;
    temp_r3->unkF6 = -1;
    temp_r3->unk10C = NULL;
    switch (GWGameStat.sound_mode) {
        case 0:
            temp_r3->unkD0 = 1;
            break;
        case 2:
        default:
            temp_r3->unkD0 = 0;
            break;
    }
    temp_r3->unk00[0] = fn_1_6440();
    for (i = 0; i < 6; i++) {
        temp_r3->unk00[i + 1] = fn_1_6528(i % 3, (i / 3) > 0);
    }
    fn_1_613C(temp_r29);
    temp_r3->unk00[7] = fn_1_61A0();
    temp_r3->unk00[8] = fn_1_62F0();
    for (i = 0; i < 16; i++) {
        temp_r3->unk00[i + 10] = fn_1_71C0((i / 8) == 0 ? 0 : 1);
    }
    fn_1_6704(temp_r29);
    fn_1_4388(temp_r29, 0);
    for (i = 0; i < 6; i++) {
        lbl_1_data_118[i + 3] = (GWGameStat.board_play_count[i] != 0) ? 1 : 0;
    }
    lbl_1_data_118[11] = (GWGameStat.field10E_bit6 != 0) ? 1 : 0;
    lbl_1_data_118[12] = (GWGameStat.field10E_bit6 != 0) ? 1 : 0;
    lbl_1_data_118[13] = (GWGameStat.field10E_bit6 != 0) ? 1 : 0;
    return temp_r29;
}

void fn_1_42DC(omObjData *arg0) {
    UnkSoundDataStruct00 *temp_r31 = arg0->data;
    s32 i;

    fn_1_629C(temp_r31->unk00[7]);
    fn_1_63EC(temp_r31->unk00[8]);
    fn_1_64D4(temp_r31->unk00[0]);
    for (i = 0; i < 6; i++) {
        fn_1_6640(temp_r31->unk00[i + 1]);
    }
    for (i = 0; i < 16; i++) {
        fn_1_72A8(temp_r31->unk00[i + 10]);
    }
    fn_1_67C8(arg0);
    HuMemDirectFree(temp_r31);
}

void fn_1_4388(omObjData *arg0, s32 arg1) {
    UnkSoundDataStruct00 *temp_r31 = arg0->data;

    temp_r31->unk9C = arg1;
    arg0->func = lbl_1_data_150[arg1];
    arg0->unk10 = 0;
    arg0->unk10 = 0;
}

s32 fn_1_43CC(omObjData *arg0) {
    UnkSoundDataStruct00 *temp_r31 = arg0->data;

    return temp_r31->unk9C;
}

static void fn_1_43E8(omObjData *arg0) {
    UnkSoundDataStruct00 *temp_r30 = arg0->data;
    s32 i;

    switch (arg0->unk10) {
        case 0:
            if (temp_r30->unkE8 == 0) {
                temp_r30->unk68[0] = fn_1_A44C(0);
                temp_r30->unk68[1] = fn_1_A44C(1);
                temp_r30->unk68[2] = fn_1_A44C(2);
                for (i = 0; i < 10; i++) {
                    temp_r30->unk68[i + 3] = fn_1_A44C(3);
                }
                fn_1_AF0(lbl_1_bss_10, 0.0f, 120.0f, -600.0f, 0x28);
                fn_1_A6C(lbl_1_bss_10, 0.0f, 120.0f, -350.0f, 0x28);
                temp_r30->unkE8 = 1;
                temp_r30->unkCC = 0;
                temp_r30->unkE4 = 0;
                arg0->unk10 = 1;
            } else {
                arg0->unk10 = 2;
            }
            break;
        case 1:
            if (fn_1_CB8(lbl_1_bss_10) == 0) {
                fn_1_4388(arg0, 2);
            }
            break;
        case 2:
            for (i = 0; i < 13; i++) {
                fn_1_A6AC(temp_r30->unk68[i]);
            }
            fn_1_AF0(lbl_1_bss_10, 0.0f, 120.0f, -600.0f, 0x28);
            fn_1_A6C(lbl_1_bss_10, 0.0f, 120.0f, 0.0f, 0x28);
            temp_r30->unkE8 = 0;
            temp_r30->unkE4 = 0;
            fn_1_4388(arg0, 0);
            break;
    }
}

static void fn_1_4658(omObjData *arg0) {
    UnkSoundDataStruct00 *temp_r31 = arg0->data;

    switch (arg0->unk10) {
        case 0:
            fn_1_613C(arg0);
            temp_r31->unkD8 = temp_r31->unkCC;
            if (temp_r31->unkE4 == 0) {
                fn_1_3D54(lbl_1_bss_30);
            } else {
                fn_1_6C5C(arg0);
                fn_1_6EA4(arg0);
                fn_1_711C(arg0);
            }
            temp_r31->unkE4 = 0;
            temp_r31->unkEC = 0;
            arg0->unk10 = 1;
            /* fallthrough */
        case 1:
            fn_1_6828(arg0);
            fn_1_A6EC(temp_r31->unk68[1]);
            fn_1_A71C(temp_r31->unk68[1], MAKE_MESSID(47, 168));
            fn_1_A6EC(temp_r31->unk68[0]);
            fn_1_A71C(temp_r31->unk68[0], lbl_1_data_168[temp_r31->unkD8]);
            if (temp_r31->unkEC == 0) {
                Hu3DModelAttrReset(temp_r31->unk00[7]->model[0], 1);
                temp_r31->unkEC = 1;
            }
            omSetTra(temp_r31->unk00[7], -34.0f + 40.0f * temp_r31->unkD8, 120.0f, -500.0f);
            arg0->unk10 = 2;
            /* fallthrough */
        case 2:
            if (temp_r31->unk68[0]->unk20 == 0 && temp_r31->unk68[1]->unk20 == 0) {
                if (fn_1_550(0x100) != 0) {
                    temp_r31->unkCC = temp_r31->unkD8;
                    temp_r31->unkE4 = 1;
                    fn_1_6044(arg0, temp_r31->unkCC);
                    HuAudFXPlay(2);
                    arg0->unk10 = 3;
                } else if (fn_1_550(0x200) != 0) {
                    HuAudFXPlay(3);
                    arg0->unk10 = 3;
                } else if (fn_1_584(1) != 0 && temp_r31->unkD8 > 0) {
                    temp_r31->unkD8--;
                    HuAudFXPlay(0);
                    arg0->unk10 = 1;
                } else if (fn_1_584(2) != 0 && temp_r31->unkD8 < 2) {
                    temp_r31->unkD8++;
                    HuAudFXPlay(0);
                    arg0->unk10 = 1;
                }
            }
            break;
        case 3:
            fn_1_A704(temp_r31->unk68[1]);
            fn_1_A704(temp_r31->unk68[0]);
            if (temp_r31->unkE4 == 0) {
                fn_1_3E1C(lbl_1_bss_30);
            }
            Hu3DModelAttrSet(temp_r31->unk00[7]->model[0], 1);
            arg0->unk10 = 4;
            /* fallthrough */
        case 4:
            if ((temp_r31->unkE4 != 0 || fn_1_3ED0(lbl_1_bss_30) == 0) && temp_r31->unk68[0]->unk20 == 0 && temp_r31->unk68[1]->unk20 == 0) {
                if (temp_r31->unkE4 != 0) {
                    switch (temp_r31->unkCC) {
                        case 0:
                            fn_1_4388(arg0, 3);
                            break;
                        case 1:
                            fn_1_4388(arg0, 4);
                            break;
                        case 2:
                            fn_1_4388(arg0, 5);
                            break;
                    }
                } else {
                    fn_1_6A0C(arg0);
                    fn_1_4388(arg0, 1);
                }
            }
            break;
    }
}

static const s32 lbl_1_rodata_1278[] = { 2, 0 };
static const s32 lbl_1_rodata_1280[] = { 1, 0 };

static const s32 lbl_1_rodata_1288[] = {
    MAKE_MESSID(47, 11),
    MAKE_MESSID(47, 12)
};

static void fn_1_4A7C(omObjData *arg0) {
    UnkSoundDataStruct00 *temp_r31 = arg0->data;
    Vec sp8;

    switch (arg0->unk10) {
        case 0:
            fn_1_6A0C(arg0);
            temp_r31->unkE4 = 0;
            temp_r31->unkD8 = temp_r31->unkD0;
            temp_r31->unkEC = 0;
            temp_r31->unkE4 = 0;
            fn_1_78A0(arg0);
            arg0->unk10 = 1;
            /* fallthrough */
        case 1:
            fn_1_6A80(arg0);
            fn_1_A6EC(temp_r31->unk68[1]);
            fn_1_A71C(temp_r31->unk68[1], MAKE_MESSID(47, 168));
            fn_1_A6EC(temp_r31->unk68[0]);
            fn_1_A71C(temp_r31->unk68[0], lbl_1_rodata_1288[temp_r31->unkD0]);
            if (temp_r31->unkEC == 0) {
                Hu3DModelAttrReset(temp_r31->unk00[8]->model[0], 1);
                temp_r31->unkEC = 1;
            }
            sp8.x = -38.0f;
            sp8.y = 140.0f - 15.0f * temp_r31->unkD8;
            sp8.z = -500.0f;
            omSetTra(temp_r31->unk00[8], sp8.x, sp8.y, sp8.z);
            arg0->unk10 = 2;
            /* fallthrough */
        case 2:
            if (temp_r31->unk68[0]->unk20 == 0 && temp_r31->unk68[1]->unk20 == 0) {
                if (fn_1_550(0x100) != 0) {
                    temp_r31->unkD0 = temp_r31->unkD8;
                    if (temp_r31->unkD0 == 0) {
                        HuAudFXPlay(0x841);
                    } else {
                        HuAudFXPlay(0x842);
                    }
                    GWGameStat.sound_mode = lbl_1_rodata_1278[temp_r31->unkD8];
                    msmSysSetOutputMode(lbl_1_rodata_1278[temp_r31->unkD8]);
                    OSSetSoundMode(lbl_1_rodata_1280[temp_r31->unkD8]);
                    temp_r31->unkE4 = 1;
                    fn_1_6A80(arg0);
                    temp_r31->unkC8 = 0;
                    arg0->unk10 = 3;
                } else if (fn_1_550(0x200) != 0) {
                    HuAudFXPlay(3);
                    arg0->unk10 = 4;
                } else if (fn_1_584(8) != 0 && temp_r31->unkD8 > 0) {
                    temp_r31->unkD8--;
                    HuAudFXPlay(0);
                    arg0->unk10 = 1;
                } else if (fn_1_584(4) != 0 && temp_r31->unkD8 < 1) {
                    temp_r31->unkD8++;
                    HuAudFXPlay(0);
                    arg0->unk10 = 1;
                }
            }
            break;
        case 3:
            if (temp_r31->unkC8++ >= 60) {
                arg0->unk10 = 4;
                return;
            }
            break;
        case 4:
            fn_1_7900(arg0);
            fn_1_A704(temp_r31->unk68[1]);
            fn_1_A704(temp_r31->unk68[0]);
            Hu3DModelAttrSet(temp_r31->unk00[8]->model[0], 1);
            arg0->unk10 = 5;
            /* fallthrough */
        case 5:
            if (temp_r31->unk68[0]->unk20 == 0 && temp_r31->unk68[1]->unk20 == 0) {
                temp_r31->unkE4 = 0;
                fn_1_6A80(arg0);
                temp_r31->unkE4 = 1;
                fn_1_4388(arg0, 2);
            }
            break;
    }
}

static void fn_1_4E50(omObjData *arg0) {
    UnkSoundDataStruct00 *temp_r31 = arg0->data;
    float temp_f31;
    float temp_f30;
    float temp_f29;
    float temp_f28;
    float temp_f27;
    float temp_f26;
    s32 var_r28;
    s32 var_r29;
    s32 sp8;

    sp8 = temp_r31->unkD8;
    switch (arg0->unk10) {
        case 0:
            fn_1_6A0C(arg0);
            temp_r31->unkD4 = 0;
            temp_r31->unk100 = 0;
            temp_r31->unkFC = 0;
            espBankSet(temp_r31->unkA0[14], 0);
            espBankSet(temp_r31->unkA0[15], 2);
            espPosSet(temp_r31->unkA0[14], 36.0f, 222.0f);
            espPosSet(temp_r31->unkA0[15], 544.0f, 222.0f);
            fn_1_160(temp_r31->unkA0[14], 1, 5);
            fn_1_160(temp_r31->unkA0[15], 1, 5);
            temp_r31->unkF8 = 0;
            arg0->unk10 = 1;
            /* fallthrough */
        case 1:
            temp_r31->unkD8 = 0;
            temp_r31->unkDC = 0;
            if (temp_r31->unkFC != 0) {
                do {
                    temp_r31->unkD4 += temp_r31->unkFC;
                    if (temp_r31->unkD4 >= 14) {
                        temp_r31->unkD4 = 0;
                    } else if (temp_r31->unkD4 < 0) {
                        temp_r31->unkD4 = 13;
                    }
                } while (lbl_1_data_118[temp_r31->unkD4] == 0);
                HuAudFXPlay(0x840);
                if (temp_r31->unkFC > 0) {
                    espBankSet(temp_r31->unkA0[15], 3);
                } else {
                    espBankSet(temp_r31->unkA0[14], 1);
                }
                temp_r31->unkF8 = 5;
                temp_r31->unkFC = 0;
            }
            arg0->unk10 = 2;
            /* fallthrough */
        case 2:
            if (temp_r31->unk100 != 0) {
                var_r29 = temp_r31->unkD8 + temp_r31->unk100;
                if (var_r29 > 9) {
                    var_r29 = 9;
                } else if (var_r29 < 0) {
                    var_r29 = 0;
                }
                if (!lbl_1_rodata_1E0[temp_r31->unkD4][var_r29].unk00) {
                    if (temp_r31->unkD8 < 5) {
                        for (var_r28 = var_r29; var_r28 >= 5; var_r28--) {
                            if (lbl_1_rodata_1E0[temp_r31->unkD4][var_r28].unk00) {
                                var_r29 = var_r28;
                                break;
                            }
                        }
                        if (var_r28 < 5) {
                            var_r29 = temp_r31->unkD8;
                        }
                    } else {
                        var_r29 = temp_r31->unkD8;
                    }
                }
                temp_r31->unkDC = temp_r31->unkD8;
                if (temp_r31->unkD8 != var_r29) {
                    temp_r31->unkD8 = var_r29;
                    HuAudFXPlay(0x840);
                }
                temp_r31->unk100 = 0;
            }
            arg0->unk10 = 3;
            /* fallthrough */
        case 3:
            fn_1_6CD0(arg0, temp_r31->unkD4);
            fn_1_A6EC(temp_r31->unk68[0]);
            fn_1_A71C(temp_r31->unk68[0], MAKE_MESSID(47, 10));
            fn_1_A6EC(temp_r31->unk68[1]);
            fn_1_A71C(temp_r31->unk68[1], MAKE_MESSID(47, 18));
            espDispOn(temp_r31->unkA0[18]);
            temp_r31->unk104 = 0.0f;
            temp_r31->unk108 = 0.0625f;
            if (temp_r31->unkF8 > 0) {
                arg0->unk10 = 5;
            } else {
                arg0->unk10 = 4;
            }
            /* fallthrough */
        case 4:
            temp_f31 = 166.0f + 244.0f * (temp_r31->unkDC / 5);
            temp_f30 = 144.0f + 29.0f * (temp_r31->unkDC % 5);
            temp_f27 = 166.0f + 244.0f * (temp_r31->unkD8 / 5);
            temp_f26 = 144.0f + 29.0f * (temp_r31->unkD8 % 5);
            temp_f29 = temp_f31 + temp_r31->unk104 * (temp_f27 - temp_f31);
            temp_f28 = temp_f30 + temp_r31->unk104 * (temp_f26 - temp_f30);
            espPosSet(temp_r31->unkA0[18], temp_f29, temp_f28);
            if ((temp_r31->unk104 += temp_r31->unk108) < 1.0f) {
                break;
            }
            espPosSet(temp_r31->unkA0[18], 166.0f + 244.0f * (temp_r31->unkD8 / 5), 144.0f + 29.0f * (temp_r31->unkD8 % 5));
            arg0->unk10 = 6;
            break;
        case 5:
            if (temp_r31->unkF8 > 0) {
                temp_r31->unkF8--;
                break;
            }
            espBankSet(temp_r31->unkA0[14], 0);
            espBankSet(temp_r31->unkA0[15], 2);
            arg0->unk10 = 6;
            /* fallthrough */
        case 6:
            if (temp_r31->unk68[0]->unk20 == 0 && temp_r31->unk68[1]->unk20 == 0) {
                if (fn_1_550(0x100) != 0) {
                    if (temp_r31->unkF0 == -2) {
                        HuAudFadeOut(0x64);
                        temp_r31->unkF0 = -1;
                    } else if (temp_r31->unkF0 != -1) {
                        HuAudSeqFadeOut(temp_r31->unkF0, 0x64);
                        temp_r31->unkF0 = -1;
                    }
                    fn_1_7F00(arg0);
                } else if (fn_1_550(0x200) != 0) {
                    HuAudFXPlay(3);
                    temp_r31->unkC8 = 0;
                    arg0->unk10 = 7;
                } else {
                    if (fn_1_5B8(1) != 0 && temp_r31->unkD8 >= 5) {
                        temp_r31->unk100 -= 5;
                    } else if (fn_1_5B8(2) != 0 && temp_r31->unkD8 < 5) {
                        temp_r31->unk100 += 5;
                    }
                    if (fn_1_5B8(8) != 0 && temp_r31->unkD8 % 5 > 0) {
                        temp_r31->unk100--;
                    } else if (fn_1_5B8(4) != 0 && temp_r31->unkD8 % 5 < 4) {
                        temp_r31->unk100++;
                    }
                    if (temp_r31->unk100 != 0) {
                        arg0->unk10 = 2;
                    } else if (fn_1_550(0x40) != 0) {
                        temp_r31->unkFC = -1;
                    } else if (fn_1_550(0x20) != 0) {
                        temp_r31->unkFC = 1;
                    }
                    if (temp_r31->unkFC != 0) {
                        arg0->unk10 = 1;
                    }
                }
            }
            break;
        case 7:
            fn_1_A704(temp_r31->unk68[1]);
            fn_1_A704(temp_r31->unk68[0]);
            fn_1_8048(arg0);
            fn_1_160(temp_r31->unkA0[14], 0, 5);
            fn_1_160(temp_r31->unkA0[15], 0, 5);
            arg0->unk10 = 8;
            /* fallthrough */
        case 8:
            if (temp_r31->unk68[0]->unk20 == 0 && temp_r31->unk68[1]->unk20 == 0) {
                espDispOff(temp_r31->unkA0[18]);
                if (temp_r31->unkF0 == -1) {
                    temp_r31->unkF0 = HuAudSeqPlay(0x2D);
                }
                fn_1_4388(arg0, 2);
            }
            break;
    }
}

static void fn_1_578C(omObjData *arg0) {
    UnkSoundDataStruct00 *temp_r31 = arg0->data;
    float temp_f31;
    float temp_f30;
    float temp_f29;
    float temp_f28;
    float temp_f27;
    float temp_f26;
    s32 var_r28;
    s32 var_r29;

    switch (arg0->unk10) {
        case 0:
            fn_1_6A0C(arg0);
            temp_r31->unkD4 = 0;
            temp_r31->unk100 = 0;
            temp_r31->unkFC = 0;
            espBankSet(temp_r31->unkA0[14], 0);
            espBankSet(temp_r31->unkA0[15], 2);
            espPosSet(temp_r31->unkA0[14], 36.0f, 222.0f);
            espPosSet(temp_r31->unkA0[15], 544.0f, 222.0f);
            fn_1_160(temp_r31->unkA0[14], 1, 5);
            fn_1_160(temp_r31->unkA0[15], 1, 5);
            temp_r31->unkF8 = 0;
            arg0->unk10 = 3;
            /* fallthrough */
        case 1:
            temp_r31->unkD8 = 0;
            temp_r31->unkDC = 0;
            if (temp_r31->unkFC != 0) {
                temp_r31->unkD4 += temp_r31->unkFC;
                if (temp_r31->unkD4 > 11) {
                    temp_r31->unkD4 = 0;
                } else if (temp_r31->unkD4 < 0) {
                    temp_r31->unkD4 = 11;
                }
                HuAudFXPlay(0x840);
                if (temp_r31->unkFC > 0) {
                    espBankSet(temp_r31->unkA0[15], 3);
                } else {
                    espBankSet(temp_r31->unkA0[14], 1);
                }
                temp_r31->unkF8 = 5;
                temp_r31->unkFC = 0;
            }
            arg0->unk10 = 2;
            /* fallthrough */
        case 2:
            if (temp_r31->unk100 != 0) {
                var_r29 = temp_r31->unkD8 + temp_r31->unk100;
                if (var_r29 > 9) {
                    var_r29 = 9;
                } else if (var_r29 < 0) {
                    var_r29 = 0;
                }
                if (!lbl_1_rodata_AD0[temp_r31->unkD4][var_r29].unk00) {
                    if (temp_r31->unkD8 < 5) {
                        for (var_r28 = var_r29; var_r28 >= 5; var_r28--) {
                            if (lbl_1_rodata_AD0[temp_r31->unkD4][var_r28].unk00) {
                                var_r29 = var_r28;
                                break;
                            }
                        }
                        if (var_r28 < 5) {
                            var_r29 = temp_r31->unkD8;
                        }
                    } else {
                        var_r29 = temp_r31->unkD8;
                    }
                }
                temp_r31->unkDC = temp_r31->unkD8;
                if (temp_r31->unkD8 != var_r29) {
                    temp_r31->unkD8 = var_r29;
                    HuAudFXPlay(0x840);
                }
                temp_r31->unk100 = 0;
            }
            arg0->unk10 = 3;
            /* fallthrough */
        case 3:
            fn_1_6F48(arg0, temp_r31->unkD4);
            fn_1_A6EC(temp_r31->unk68[0]);
            fn_1_A71C(temp_r31->unk68[0], MAKE_MESSID(47, 9));
            fn_1_A6EC(temp_r31->unk68[1]);
            fn_1_A71C(temp_r31->unk68[1], MAKE_MESSID(47, 18));
            espDispOn(temp_r31->unkA0[18]);
            temp_r31->unk104 = 0.0f;
            temp_r31->unk108 = 0.0625f;
            if (temp_r31->unkF8 > 0) {
                arg0->unk10 = 5;
            } else {
                arg0->unk10 = 4;
            }
            /* fallthrough */
        case 4:
            temp_f31 = 166.0f + 244.0f * (temp_r31->unkDC / 5);
            temp_f30 = 144.0f + 29.0f * (temp_r31->unkDC % 5);
            temp_f27 = 166.0f + 244.0f * (temp_r31->unkD8 / 5);
            temp_f26 = 144.0f + 29.0f * (temp_r31->unkD8 % 5);
            temp_f29 = temp_f31 + temp_r31->unk104 * (temp_f27 - temp_f31);
            temp_f28 = temp_f30 + temp_r31->unk104 * (temp_f26 - temp_f30);
            espPosSet(temp_r31->unkA0[18], temp_f29, temp_f28);
            if ((temp_r31->unk104 += temp_r31->unk108) < 1.0f) {
                break;
            }
            espPosSet(temp_r31->unkA0[18], 166.0f + 244.0f * (temp_r31->unkD8 / 5), 144.0f + 29.0f * (temp_r31->unkD8 % 5));
            arg0->unk10 = 6;
            break;
        case 5:
            if (temp_r31->unkF8 > 0) {
                temp_r31->unkF8--;
                break;
            }
            espBankSet(temp_r31->unkA0[14], 0);
            espBankSet(temp_r31->unkA0[15], 2);
            arg0->unk10 = 6;
            /* fallthrough */
        case 6:
            if (temp_r31->unk68[0]->unk20 == 0 && temp_r31->unk68[1]->unk20 == 0) {
                if (fn_1_550(0x100) != 0) {
                    fn_1_7F00(arg0);
                } else if (fn_1_550(0x200) != 0) {
                    HuAudFXPlay(3);
                    temp_r31->unkC8 = 0;
                    arg0->unk10 = 7;
                } else {
                    if (fn_1_5B8(1) != 0 && temp_r31->unkD8 >= 5) {
                        temp_r31->unk100 -= 5;
                    } else if (fn_1_5B8(2) != 0 && temp_r31->unkD8 < 5) {
                        temp_r31->unk100 += 5;
                    }
                    if (fn_1_5B8(8) != 0 && temp_r31->unkD8 % 5 > 0) {
                        temp_r31->unk100--;
                    } else if (fn_1_5B8(4) != 0 && temp_r31->unkD8 % 5 < 4) {
                        temp_r31->unk100++;
                    }
                    if (temp_r31->unk100 != 0) {
                        arg0->unk10 = 2;
                    } else if (fn_1_550(0x40) != 0) {
                        temp_r31->unkFC = -1;
                    } else if (fn_1_550(0x20) != 0) {
                        temp_r31->unkFC = 1;
                    }
                    if (temp_r31->unkFC != 0) {
                        arg0->unk10 = 1;
                    }
                }
            }
            break;
        case 7:
            fn_1_A704(temp_r31->unk68[1]);
            fn_1_A704(temp_r31->unk68[0]);
            fn_1_8048(arg0);
            fn_1_160(temp_r31->unkA0[14], 0, 5);
            fn_1_160(temp_r31->unkA0[15], 0, 5);
            arg0->unk10 = 8;
            /* fallthrough */
        case 8:
            if (temp_r31->unk68[0]->unk20 == 0 && temp_r31->unk68[1]->unk20 == 0) {
                espDispOff(temp_r31->unkA0[18]);
                fn_1_4388(arg0, 2);
            }
            break;
    }
}

static void fn_1_6044(omObjData *arg0, s32 arg1) {
    UnkSoundDataStruct00 *temp_r31 = arg0->data;

    switch (arg1) {
        case 0:
            fn_1_6694(temp_r31->unk00[1]);
            fn_1_6694(temp_r31->unk00[5]);
            fn_1_6694(temp_r31->unk00[6]);
            fn_1_66CC(temp_r31->unk00[4]);
            fn_1_66CC(temp_r31->unk00[2]);
            fn_1_66CC(temp_r31->unk00[3]);
            break;
        case 1:
            fn_1_6694(temp_r31->unk00[4]);
            fn_1_6694(temp_r31->unk00[2]);
            fn_1_6694(temp_r31->unk00[6]);
            fn_1_66CC(temp_r31->unk00[1]);
            fn_1_66CC(temp_r31->unk00[5]);
            fn_1_66CC(temp_r31->unk00[3]);
            break;
        case 2:
            fn_1_6694(temp_r31->unk00[4]);
            fn_1_6694(temp_r31->unk00[5]);
            fn_1_6694(temp_r31->unk00[3]);
            fn_1_66CC(temp_r31->unk00[1]);
            fn_1_66CC(temp_r31->unk00[2]);
            fn_1_66CC(temp_r31->unk00[6]);
            break;
    }
}

static void fn_1_613C(omObjData *arg0) {
    UnkSoundDataStruct00 *temp_r31 = arg0->data;

    fn_1_6694(temp_r31->unk00[4]);
    fn_1_6694(temp_r31->unk00[5]);
    fn_1_6694(temp_r31->unk00[6]);
    fn_1_66CC(temp_r31->unk00[1]);
    fn_1_66CC(temp_r31->unk00[2]);
    fn_1_66CC(temp_r31->unk00[3]);
}

static omObjData *fn_1_61A0(void) {
    omObjData *temp_r31;

    temp_r31 = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    temp_r31->model[0] = Hu3DModelCreateFile(0x69000D);
    Hu3DModelLayerSet(temp_r31->model[0], 2);
    Hu3DModelAttrSet(temp_r31->model[0], 0x40000001);
    omSetRot(temp_r31, -80.0f, 45.0f, 0.0f);
    omSetSca(temp_r31, 0.6f, 0.6f, 0.6f);
    Hu3DModelAttrSet(temp_r31->model[0], 1);
    return temp_r31;
}

static void fn_1_629C(omObjData *arg0) {
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(arg0->model[i]);
    }
}

static omObjData *fn_1_62F0(void) {
    omObjData *temp_r31;

    temp_r31 = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    temp_r31->model[0] = Hu3DModelCreateFile(0x69000E);
    Hu3DModelLayerSet(temp_r31->model[0], 2);
    Hu3DModelAttrSet(temp_r31->model[0], 0x40000001);
    omSetRot(temp_r31, 0.0f, -90.0f, 0.0f);
    omSetSca(temp_r31, 0.6f, 0.6f, 0.6f);
    Hu3DModelAttrSet(temp_r31->model[0], 1);
    return temp_r31;
}

static void fn_1_63EC(omObjData *arg0) {
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(arg0->model[i]);
    }
}

static omObjData *fn_1_6440(void) {
    omObjData *temp_r31;

    temp_r31 = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    temp_r31->model[0] = Hu3DModelCreateFile(0x690003);
    Hu3DModelAttrSet(temp_r31->model[0], 0x40000001);
    Hu3DModelLayerSet(temp_r31->model[0], 0);
    return temp_r31;
}

static void fn_1_64D4(omObjData *arg0) {
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(arg0->model[i]);
    }
}

static const Vec lbl_1_rodata_12D0[3] = {
    { -40.0f, 0.0f, 0.0f },
    {   0.0f, 0.0f, 0.0f },
    {  40.0f, 0.0f, 0.0f }
};

static omObjData *fn_1_6528(s32 arg0, s32 arg1) {
    omObjData *temp_r31;

    temp_r31 = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    if (arg1 != 0) {
        temp_r31->model[0] = Hu3DModelCreateFile(0x690005);
    } else {
        temp_r31->model[0] = Hu3DModelCreateFile(0x690004);
    }
    Hu3DModelAttrSet(temp_r31->model[0], 0x40000001);
    Hu3DModelLayerSet(temp_r31->model[0], 0);
    omSetTra(temp_r31, lbl_1_rodata_12D0[arg0].x, lbl_1_rodata_12D0[arg0].y, lbl_1_rodata_12D0[arg0].z);
    return temp_r31;
}

static void fn_1_6640(omObjData *arg0) {
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(arg0->model[i]);
    }
}

static void fn_1_6694(omObjData *arg0) {
    Hu3DModelAttrReset(arg0->model[0], 1);
}

static void fn_1_66CC(omObjData *arg0) {
    Hu3DModelAttrSet(arg0->model[0], 1);
}

static s32 lbl_1_data_1BC[] = {
    DATA_MAKE_NUM(DATADIR_OPTION, 38),
    DATA_MAKE_NUM(DATADIR_OPTION, 39),
    DATA_MAKE_NUM(DATADIR_OPTION, 40),
    DATA_MAKE_NUM(DATADIR_OPTION, 35),
    DATA_MAKE_NUM(DATADIR_OPTION, 36),
    DATA_MAKE_NUM(DATADIR_OPTION, 37),
    DATA_MAKE_NUM(DATADIR_OPTION, 41),
    DATA_MAKE_NUM(DATADIR_OPTION, 43),
    DATA_MAKE_NUM(DATADIR_OPTION, 42),
    DATA_MAKE_NUM(DATADIR_OPTION, 44),
    DATA_MAKE_NUM(DATADIR_OPTION, 45),
    DATA_MAKE_NUM(DATADIR_OPTION, 46),
    DATA_MAKE_NUM(DATADIR_OPTION, 47),
    DATA_MAKE_NUM(DATADIR_OPTION, 48),
    DATA_MAKE_NUM(DATADIR_OPTION, 49),
    DATA_MAKE_NUM(DATADIR_OPTION, 49),
    DATA_MAKE_NUM(DATADIR_OPTION, 63),
    DATA_MAKE_NUM(DATADIR_OPTION, 64),
    DATA_MAKE_NUM(DATADIR_OPTION, 65)
};

static void fn_1_6704(omObjData *arg0) {
    UnkSoundDataStruct00 *temp_r31 = arg0->data;
    s32 i;

    for (i = 0; i < 19; i++) {
        temp_r31->unkA0[i] = espEntry(lbl_1_data_1BC[i], 0, 0);
        espDrawNoSet(temp_r31->unkA0[i], 0x40);
        espDispOff(temp_r31->unkA0[i]);
    }
    espBankSet(temp_r31->unkA0[14], 0);
    espBankSet(temp_r31->unkA0[15], 2);
    HuSprExecLayerSet(0x40, 1);
}

static void fn_1_67C8(omObjData *arg0) {
    UnkSoundDataStruct00 *temp_r31 = arg0->data;
    s32 i;

    for (i = 0; i < 19; i++) {
        espKill(temp_r31->unkA0[i]);
    }
}

static void fn_1_6828(omObjData *arg0) {
    UnkSoundDataStruct00 *temp_r31 = arg0->data;
    float temp_f31 = 288.0f;
    float temp_f30 = 188.0f;

    espPosSet(temp_r31->unkA0[12], 288.0f, 72.0f);
    espPosSet(temp_r31->unkA0[0], temp_f31 + -112.0f, temp_f30);
    espPosSet(temp_r31->unkA0[3], temp_f31 + -112.0f, temp_f30);
    espPosSet(temp_r31->unkA0[1], temp_f31, temp_f30);
    espPosSet(temp_r31->unkA0[4], temp_f31, temp_f30);
    espPosSet(temp_r31->unkA0[2], temp_f31 + 112.0f, temp_f30);
    espPosSet(temp_r31->unkA0[5], temp_f31 + 112.0f, temp_f30);
    espDispOn(temp_r31->unkA0[12]);
    switch (temp_r31->unkD8) {
        case 0:
            espDispOn(temp_r31->unkA0[3]);
            espDispOn(temp_r31->unkA0[1]);
            espDispOn(temp_r31->unkA0[2]);
            espDispOff(temp_r31->unkA0[0]);
            espDispOff(temp_r31->unkA0[4]);
            espDispOff(temp_r31->unkA0[5]);
            break;
        case 1:
            espDispOn(temp_r31->unkA0[0]);
            espDispOn(temp_r31->unkA0[4]);
            espDispOn(temp_r31->unkA0[2]);
            espDispOff(temp_r31->unkA0[3]);
            espDispOff(temp_r31->unkA0[1]);
            espDispOff(temp_r31->unkA0[5]);
            break;
        case 2:
            espDispOn(temp_r31->unkA0[0]);
            espDispOn(temp_r31->unkA0[1]);
            espDispOn(temp_r31->unkA0[5]);
            espDispOff(temp_r31->unkA0[3]);
            espDispOff(temp_r31->unkA0[4]);
            espDispOff(temp_r31->unkA0[2]);
            break;
    }
}

static const s32 lbl_1_rodata_1308[] = { 12, 0, 1, 2, 3, 4, 5 };

static void fn_1_6A0C(omObjData *arg0) {
    UnkSoundDataStruct00 *temp_r30 = arg0->data;
    s32 i;

    for (i = 0; i < 7; i++) {
        espDispOff(temp_r30->unkA0[lbl_1_rodata_1308[i]]);
    }
}

static void fn_1_6A80(omObjData *arg0) {
    UnkSoundDataStruct00 *temp_r31 = arg0->data;
    float temp_f31 = 290.0f;
    float temp_f30 = 192.0f;

    espPosSet(temp_r31->unkA0[13], 288.0f, 72.0f);
    espPosSet(temp_r31->unkA0[6], temp_f31, temp_f30 - 32.0f);
    espPosSet(temp_r31->unkA0[7], temp_f31, temp_f30 - 32.0f);
    espPosSet(temp_r31->unkA0[8], temp_f31, temp_f30 + 32.0f);
    espPosSet(temp_r31->unkA0[9], temp_f31, temp_f30 + 32.0f);
    switch (temp_r31->unkD8) {
        case 0:
            espPosSet(temp_r31->unkA0[17], temp_f31, temp_f30 - 32.0f);
            break;
        case 1:
            espPosSet(temp_r31->unkA0[17], temp_f31, temp_f30 + 32.0f);
            break;
    }
    espDispOn(temp_r31->unkA0[13]);
    switch (temp_r31->unkD8) {
        case 0:
            espDispOn(temp_r31->unkA0[6]);
            espDispOn(temp_r31->unkA0[9]);
            espDispOff(temp_r31->unkA0[7]);
            espDispOff(temp_r31->unkA0[8]);
            break;
        case 1:
            espDispOn(temp_r31->unkA0[7]);
            espDispOn(temp_r31->unkA0[8]);
            espDispOff(temp_r31->unkA0[6]);
            espDispOff(temp_r31->unkA0[9]);
            break;
    }
    if (temp_r31->unkE4 != 0) {
        espDispOn(temp_r31->unkA0[17]);
    } else {
        espDispOff(temp_r31->unkA0[17]);
    }
}

static const s32 lbl_1_rodata_1330[] = { 13, 6, 7, 8, 9 };

static void fn_1_6C5C(omObjData *arg0) {
    UnkSoundDataStruct00 *temp_r30 = arg0->data;
    s32 i;

    for (i = 0; i < 5; i++) {
        espDispOff(temp_r30->unkA0[lbl_1_rodata_1330[i]]);
    }
}

static void fn_1_6CD0(omObjData *arg0, s32 arg1) {
    UnkSoundDataStruct00 *temp_r31 = arg0->data;
    s32 i;

    espPosSet(temp_r31->unkA0[10], 288.0f, 72.0f);
    espDispOn(temp_r31->unkA0[10]);
    fn_1_A7F0(temp_r31->unk68[2]);
    for (i = 0; i < 10; i++) {
        fn_1_A7F0(temp_r31->unk68[i + 3]);
        fn_1_A7B0(temp_r31->unk68[i + 3], 52.0f + 244.0f * (i / 5), 124.0f + 29.0f * (i % 5));
    }
    fn_1_A71C(temp_r31->unk68[2], lbl_1_rodata_1A8[arg1]);
    for (i = 0; i < 10; i++) {
        fn_1_A71C(temp_r31->unk68[i + 3], lbl_1_rodata_1E0[arg1][i].unk04);
    }
}

static const s32 lbl_1_rodata_134C[] = { 10 };

static void fn_1_6EA4(omObjData *arg0) {
    UnkSoundDataStruct00 *temp_r30 = arg0->data;
    s32 i;

    for (i = 0; i < 1; i++) {
        espDispOff(temp_r30->unkA0[lbl_1_rodata_134C[i]]);
    }
    fn_1_A828(temp_r30->unk68[2]);
    for (i = 0; i < 10; i++) {
        fn_1_A828(temp_r30->unk68[i + 3]);
    }
}

static void fn_1_6F48(omObjData *arg0, s32 arg1) {
    UnkSoundDataStruct00 *temp_r31 = arg0->data;
    s32 i;

    espPosSet(temp_r31->unkA0[11], 288.0f, 72.0f);
    espDispOn(temp_r31->unkA0[11]);
    fn_1_A7F0(temp_r31->unk68[2]);
    for (i = 0; i < 10; i++) {
        fn_1_A7F0(temp_r31->unk68[i + 3]);
        fn_1_A7B0(temp_r31->unk68[i + 3], 52.0f + 244.0f * (i / 5), 124.0f + 29.0f * (i % 5));
    }
    fn_1_A71C(temp_r31->unk68[2], lbl_1_rodata_AA0[arg1]);
    for (i = 0; i < 10; i++) {
        fn_1_A71C(temp_r31->unk68[i + 3], lbl_1_rodata_AD0[arg1][i].unk04);
    }
}

static const s32 lbl_1_rodata_1350[] = { 11, 0 };

static void fn_1_711C(omObjData *arg0) {
    UnkSoundDataStruct00 *temp_r30 = arg0->data;
    s32 i;

    for (i = 0; i < 1; i++) {
        espDispOff(temp_r30->unkA0[lbl_1_rodata_1350[i]]);
    }
    fn_1_A828(temp_r30->unk68[2]);
    for (i = 0; i < 10; i++) {
        fn_1_A828(temp_r30->unk68[i + 3]);
    }
}

static s32 lbl_1_data_208[] = {
    DATA_MAKE_NUM(DATADIR_OPTION, 7),
    DATA_MAKE_NUM(DATADIR_OPTION, 8)
};

static omObjData *fn_1_71C0(s32 arg0) {
    omObjData *temp_r31;
    UnkSoundDataStruct01 *temp_r3;

    temp_r31 = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkSoundDataStruct01), MEMORY_DEFAULT_NUM);
    temp_r31->data = temp_r3;
    temp_r3->unk00 = 0;
    temp_r3->unk04 = arg0;
    temp_r31->model[0] = Hu3DModelCreateFile(lbl_1_data_208[arg0]);
    Hu3DModelAttrSet(temp_r31->model[0], 0x40000001);
    Hu3DModelLayerSet(temp_r31->model[0], 2);
    Hu3DModelAttrReset(temp_r31->model[0], 2);
    return temp_r31;
}

static void fn_1_72A8(omObjData *arg0) {
    UnkSoundDataStruct01 *temp_r30 = arg0->data;
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(arg0->model[i]);
    }
    HuMemDirectFree(temp_r30);
}

static void fn_1_7310(omObjData *arg0) {
    UnkSoundDataStruct01 *temp_r31 = arg0->data;
    float temp_f31;
    float temp_f30;
    float var_f29;
    float var_f28;
    float temp_f27;
    float temp_f26;
    float temp_f25;
    float temp_f24;
    float temp_f23;

    Hu3DModelAttrReset(arg0->model[0], 1);
    temp_f31 = sin(45.0f * temp_r31->unk0C * M_PI / 180.0);
    temp_f31 = temp_f31 * temp_f31;
    switch (temp_r31->unk08) {
        case 0:
            var_f29 = 174.5f + 7.0f * temp_f31;
            var_f28 = -15.0 + 30.0 * sin(1440.0f * temp_f31 * M_PI / 180.0);
            break;
        case 1:
            var_f29 = 185.5f - (7.0f * temp_f31);
            var_f28 = 15.0 - 30.0 * sin(1440.0f * temp_f31 * M_PI / 180.0);
            break;
    }
    temp_f23 = sin(180.0f * temp_r31->unk0C * M_PI / 180.0);
    temp_f27 = 500.0f - 25.0f * temp_f31;
    temp_f26 = temp_f27 * -sin(var_f29 * M_PI / 180.0);
    temp_f25 = temp_f27 * cos(var_f29 * M_PI / 180.0);
    temp_f24 = 160.0f - 15.0f * temp_r31->unk0C;
    temp_f30 = 0.5 + 2.0 * sin(90.0f * temp_f31 * M_PI / 180.0);
    omSetTra(arg0, temp_f26, temp_f24, temp_f25);
    Hu3DModelTPLvlSet(arg0->model[0], temp_f23);
    omSetSca(arg0, temp_f30, temp_f30, temp_f30);
    omSetRot(arg0, 0.0f, 0.0f, var_f28);
    if ((temp_r31->unk0C += temp_r31->unk10) < 1.0f) {
        return;
    }
    temp_r31->unk00 = 0;
    Hu3DModelAttrSet(arg0->model[0], 1);
    arg0->func = NULL;
    arg0->unk10 = 0;
}

static void fn_1_7710(omObjData *arg0, s32 arg1, s32 arg2, s32 arg3) {
    omObjData *var_r30;
    UnkSoundDataStruct01 *var_r31;
    s32 i;

    for (i = 0; i < 16; i++) {
        var_r30 = ((UnkSoundDataStruct00*) arg0->data)->unk00[i + 10];
        var_r31 = var_r30->data;
        if (var_r31->unk00 == 0 && var_r31->unk04 == arg1) {
            break;
        }
    }
    if (i != 16) {
        Hu3DMotionTimeSet(var_r30->model[0], 2.0f * arg3);
        Hu3DMotionStartEndSet(var_r30->model[0], 2.0f * arg3, 2.0f * arg3 + 1.0f);
        var_r31->unk00 = 1;
        var_r31->unk08 = arg2;
        var_r31->unk0C = 0.0f;
        var_r31->unk10 = 0.011111111f;
        var_r30->func = fn_1_7310;
        var_r30->unk10 = 0;
    }
}

static void fn_1_78A0(omObjData *arg0) {
    UnkSoundDataStruct00 *temp_r31 = arg0->data;

    temp_r31->unk10C = HuPrcChildCreate(fn_1_793C, 0x64, 0x2000, 0, HuPrcCurrentGet());
    temp_r31->unk10C->user_data = arg0;
}

static void fn_1_7900(omObjData *arg0) {
    UnkSoundDataStruct00 *temp_r31 = arg0->data;

    HuPrcKill(temp_r31->unk10C);
}

static void fn_1_793C(void) {
    omObjData *temp_r26;
    UnkSoundDataStruct00 *sp8;
    s32 var_r21;
    s32 temp_r31;

    temp_r26 = HuPrcCurrentGet()->user_data;
    sp8 = temp_r26->data;
    while (1) {
        switch (sp8->unkD8) {
            case 0:
                var_r21 = 1;
                temp_r31 = frandmod(7);
                fn_1_7710(temp_r26, var_r21, 0, temp_r31);
                var_r21 = 0;
                temp_r31 = frandmod(7);
                fn_1_7710(temp_r26, var_r21, 1, temp_r31);
                break;
            case 1:
                var_r21 = 0;
                temp_r31 = frandmod(7);
                fn_1_7710(temp_r26, var_r21, 0, temp_r31);
                fn_1_7710(temp_r26, var_r21, 1, temp_r31);
                break;
        }
        HuPrcSleep(0x18);
    }
}

static void fn_1_7F00(omObjData *arg0) {
    UnkSoundDataStruct00 *temp_r30 = arg0->data;
    lbl_1_rodata_1E0_Data *var_r31;

    if (temp_r30->unkCC == 1) {
        var_r31 = (lbl_1_rodata_1E0_Data*) &lbl_1_rodata_1E0[temp_r30->unkD4][temp_r30->unkD8];
    } else {
        var_r31 = (lbl_1_rodata_1E0_Data*) &lbl_1_rodata_AD0[temp_r30->unkD4][temp_r30->unkD8];
    }
    if (var_r31->unk00 != 0) {
        fn_1_8048(arg0);
        switch (var_r31->unk08) {
            case 1:
                temp_r30->unkF4 = HuAudSStreamPlay(var_r31->unk0C);
                break;
            case 28:
                if (var_r31->unk0A != temp_r30->unkE0) {
                    HuAudSndGrpSetSet(var_r31->unk0A);
                }
                temp_r30->unkF6 = HuAudFXPlay(var_r31->unk0C);
                break;
            default:
                if (var_r31->unk0A != temp_r30->unkE0 && var_r31->unk0A != 2) {
                    HuAudSndGrpSetSet(var_r31->unk0A);
                }
                temp_r30->unkF2 = HuAudSeqPlay(var_r31->unk0C);
                break;
        }
        temp_r30->unkE0 = var_r31->unk0A;
        HuPrcSleep(40);
    }
}

static void fn_1_8048(omObjData *arg0) {
    UnkSoundDataStruct00 *temp_r31 = arg0->data;

    if (temp_r31->unkF2 != -1) {
        HuAudSeqFadeOut(temp_r31->unkF2, 0x64);
        temp_r31->unkF2 = -1;
    }
    if (temp_r31->unkF4 != -1) {
        HuAudSStreamFadeOut(temp_r31->unkF4, 0x64);
        temp_r31->unkF4 = -1;
    }
    if (temp_r31->unkF6 != -1) {
        HuAudFXFadeOut(temp_r31->unkF6, 0x64);
        temp_r31->unkF6 = -1;
    }
    HuPrcSleep(20);
}
