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

typedef struct MpexDllUnkStruct3 {
    /* 0x00 */ char unk00[0x30];
    /* 0x30 */ s16 unk_30;
    /* 0x32 */ s16 unk_32;
    /* 0x34 */ char unk34[6];
    /* 0x3A */ s16 unk_3A[0x10];
    /* 0x5A */ s16 unk_5A[0x10];
} MpexDllUnkStruct3; /* size = unknown */

s32 fn_1_3044(Process *arg0);

// s32 fn_1_1B52C(float, float, float, float); seems implicit in main.c
s32 fn_1_1B554(float, float, float);
s32 fn_1_1B574(float, float, float, float);
s32 fn_1_1B64C(float, float, float, float);
s32 fn_1_1B7D0(s32 arg0);

extern u8 lbl_1_bss_6AC;

#endif
