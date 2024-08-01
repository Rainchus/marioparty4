#ifndef PRESENT_H
#define PRESENT_H

#include "game/object.h"

typedef struct UnkWindowDataStruct {
    /* 0x00 */ Process *process;
    /* 0x04 */ s16 window;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u32 unk18;
    /* 0x1C */ s32 choice;
    /* 0x20 */ s32 unk_20;
} UnkWindowDataStruct; /* size 0x24 */ // this already exists in option.h

extern omObjData *lbl_1_bss_10;
extern omObjData *lbl_1_bss_8;
extern Process *lbl_1_bss_4;

void fn_1_144(s16 arg0, s32 arg1, s32 arg2);
void fn_1_334(s16 arg0, s32 arg1, float arg8, s32 arg2);
omObjData *fn_1_6B4();
void fn_1_920(omObjData *object, float arg8, float arg9, float argA, s32 arg1);
void fn_1_9A4(omObjData *object, float arg8, float arg9, float argA, s32 arg1);
void fn_1_BF8(omObjData *object);
omObjData *fn_1_1458(void);
void fn_1_180C(omObjData *object, s32 arg1);
s32 fn_1_1850(omObjData *object);
omObjData *fn_1_39A8(void);
UnkWindowDataStruct *fn_1_3EA4(s32 arg0);
void fn_1_4080(UnkWindowDataStruct *windowData);
void fn_1_4098(UnkWindowDataStruct *windowData);
void fn_1_40B0(UnkWindowDataStruct *windowData, u32 mess);
omObjData *fn_1_42F4(void);
void fn_1_45C0(omObjData *arg0, s32 arg1);
s32 fn_1_4604(omObjData *object);

#endif
