#ifndef MENTDLL_H
#define MENTDLL_H

#include "game/object.h"

typedef struct MentDllUnkBss64Struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ float unk_08;
    /* 0x0C */ float unk_0C;
    /* 0x10 */ float unk_10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ float unk_20;
    /* 0x24 */ float unk_24;
    /* 0x28 */ float unk_28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ float unk_38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk_40;
} MentDllUnkBss64Struct; /* size = 0x44 */

float fn_1_20C(float arg8, float arg9, float argA, float argB);
float fn_1_234(float arg8, float arg9, float argA);
float fn_1_254(float arg8, float arg9, float argA, float argB);
float fn_1_32C(float arg8, float arg9, float argA, float argB);
float fn_1_3F4(float arg8, float arg9, float argA, float argB);
void fn_1_4B0(s32 arg0);
void fn_1_4D8(void);
void fn_1_50C(void);
void fn_1_5E8(s32 arg0);
void fn_1_6D0(void);
s32 fn_1_1434(s32 arg0, s32 arg1, s32 arg2);
void fn_1_16AC(s32 arg0);
void fn_1_1968(s32 arg0, u32 arg1, s32 arg2, s32 arg3);
s32 fn_1_1A5C(u32 arg0, s32 arg1, s32 arg2);
s32 fn_1_1DD8(u32 arg0, s32 arg1, s32 arg2);
s32 fn_1_2154(u32 arg0);
void fn_1_2318(s32 arg0);
void fn_1_2808(void *arg0);
void fn_1_2844(Process *arg0, void *arg1);
void fn_1_4138(MentDllUnkBss64Struct *arg0, float *arg1, float arg8, float arg9, float argA);
void fn_1_5150(void *arg0, void *arg1, float arg8, float arg9, float argA);
void fn_1_5818(omObjData *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_59A0(omObjData *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_5C08(omObjData *arg0);
void fn_1_5CDC(omObjData *arg0, s32 arg1, s32 arg2);
void fn_1_5D38(omObjData *arg0, s32 arg1, Vec arg2, float arg8, float arg9, float argA, s32 arg3, s32 arg4);
void fn_1_6534(s32, s32, float, float);

void fn_1_658C(Process *arg0);

#endif
