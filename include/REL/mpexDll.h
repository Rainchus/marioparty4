#ifndef MPEXDLL_H
#define MPEXDLL_H

#include "game/object.h"

typedef void (*MpexDllUnkFunc)(void);

typedef struct MpexDllUnkStruct {
    /* 0x00 */ MpexDllUnkFunc unk_00;
    /* 0x04 */ void *unk_04; // func, unknown args
    /* 0x08 */ Vec unk_08;
    /* 0x14 */ Vec unk_14;
    /* 0x20 */ Vec unk_20;
    /* 0x2C */ Vec unk_2C;
    /* 0x38 */ float unk_38;
    /* 0x3C */ float unk_3C;
    /* 0x40 */ s32 unk_40;
} MpexDllUnkStruct; /* size = 0x44 */

typedef struct MpexDllUnkStruct2 {
    /* 0x00 */ char unk00[0x40];
    /* 0x40 */ s16 *unk_40;
    /* 0x44 */ char unk44;
    /* 0x48 */ s16 *unk_48;
    /* 0x4C */ char unk_4C[0xC];
    /* 0x58 */ u32 unk_58;
} MpexDllUnkStruct2; /* size = unknown */

void fn_1_374(void);
void fn_1_298(void);
void fn_1_910(MpexDllUnkFunc arg0);
void fn_1_25C4(MpexDllUnkStruct2 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_28E0(MpexDllUnkStruct2 *arg0, s32 arg1, Vec *arg2, float arg8, float arg9, float argA, s32 arg3, s32 arg4);
s32 fn_1_3044(Process *arg0);

void fn_1_1B7D0(s32 arg0);

s32 fn_1_1D02C(s32 arg0);

extern u8 lbl_1_bss_6AC;

#endif
