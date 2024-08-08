#ifndef ZTARDLL_H
#define ZTARDLL_H

#include "game/object.h"

#include "dolphin/types.h"

typedef struct ZtarDllUnkStruct {
    char unk00[0x30];
    s16 unk_30;
    s16 unk_32;
    char unk34[6];
    s16 unk_3A[16];
    s16 unk_5A[16];
} ZtarDllUnkStruct; /* size = 0x7A */

s32 fn_1_7754(ZtarDllUnkStruct *arg0, u8 *arg1);
void fn_1_7C00(void);
void fn_1_7D6C(Process *arg0);
s32 fn_1_97D0(s32 arg0, s32 arg1);
void fn_1_11020(void);
void fn_1_111E0(void);
void fn_1_11264(s32 arg0, s32 arg1, s32 arg2);
void fn_1_11338(u32 arg0, s32 arg1);
s32 fn_1_11390(s32 arg0);
void fn_1_114EC(u32 arg0, s32 arg1);
void fn_1_11708(u32 arg0);
void fn_1_1190C(void);

#endif
