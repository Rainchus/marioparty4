#ifndef _GAME_WINDOW_H
#define _GAME_WINDOW_H

#include "game/sprite.h"

typedef struct {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
} UnknownWindowStruct1; // Size 8

typedef struct {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ char unk01[1];
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
} UnknownWindowStruct2; // Size 6

typedef struct {
    /* 0x000 */ u8 unk00;
    /* 0x001 */ u8 unk01;
    /* 0x002 */ u8 unk02;
    /* 0x003 */ u8 unk03;
    /* 0x004 */ s16 unk04;
    /* 0x006 */ s16 unk06[30];
    /* 0x042 */ s16 unk42;
    /* 0x044 */ s16 unk44;
    /* 0x046 */ s16 unk46;
    /* 0x048 */ s16 unk48;
    /* 0x04A */ char unk4A[2];
    /* 0x04C */ u32 unk4C;
    /* 0x050 */ AnimData* unk50;
    /* 0x054 */ s16 unk54;
    /* 0x056 */ s16 unk56;
    /* 0x058 */ s16 unk58;
    /* 0x05A */ s16 unk5A;
    /* 0x05C */ s16 unk5C;
    /* 0x05E */ s16 unk5E;
    /* 0x060 */ s16 unk60;
    /* 0x062 */ s16 unk62;
    /* 0x064 */ s16 unk64;
    /* 0x066 */ s16 unk66;
    /* 0x068 */ s16 unk68;
    /* 0x06A */ s16 unk6A;
    /* 0x06C */ f32 unk6C;
    /* 0x070 */ f32 unk70;
    /* 0x074 */ f32 unk74;
    /* 0x078 */ f32 unk78;
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ s16 unk80;
    /* 0x082 */ s16 unk82;
    /* 0x084 */ UnknownWindowStruct1* unk84;
    /* 0x088 */ s16 unk88;
    /* 0x08A */ char unk8A[2];
    /* 0x08C */ s32 unk8C;
    /* 0x090 */ u8* unk90;
    /* 0x094 */ u8* unk94[1]; // unknown size
    /* 0x098 */ char unk98[0x1C];
    /* 0x0B4 */ void* unkB4[8];
    /* 0x0D4 */ s16 unkD4;
    /* 0x0D6 */ s16 unkD6;
    /* 0x0D8 */ s16 unkD8;
    /* 0x0DA */ u8 unkDA[16];
    /* 0x0EA */ UnknownWindowStruct2 unkEA[16];
    /* 0x14A */ s16 unk14A;
    /* 0x14C */ s16 unk14C;
    /* 0x14E */ s16 unk14E;
    /* 0x150 */ s16 unk150;
    /* 0x152 */ s16 unk152;
    /* 0x154 */ s16 unk154;
    /* 0x156 */ s16 unk156;
    /* 0x158 */ s16 unk158;
    /* 0x15A */ char unk15A[6];
    /* 0x160 */ u8 unk160[10][3];
    /* 0x17E */ char unk17E[2];
} SomeWindowStruct; // Size 0x180

typedef struct {
    /* 0x00 */ u8 r;
    /* 0x01 */ u8 g;
    /* 0x02 */ u8 b;
} ColorRGB; // Size 3

void HuWindowInit(void);
void HuWinInit(s32 arg0);
s16 HuWinCreate(f32 x, f32 y, s16 w, s16 h, s16 frame);
void HuWinKill(s16 arg0);
void HuWinAllKill(void);
void HuWinHomeClear(s16 arg0);
void HuWinKeyWaitEntry(s16 arg0);
u32 HuWinActivePadGet(SomeWindowStruct* arg0);
u32 HuWinActiveKeyGetX(SomeWindowStruct* arg0);
void HuWinPosSet(s16 arg0, f32 arg1, f32 arg2);
void HuWinScaleSet(s16 arg0, f32 arg1, f32 arg2);
void HuWinZRotSet(s16 arg0, f32 arg1);
void HuWinCenterPosSet(s16 arg0, f32 arg1, f32 arg2);
void HuWinDrawNoSet(s16 arg0, s16 arg1);
void HuWinScissorSet(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void HuWinPriSet(s16 arg0, s16 arg1);
void HuWinAttrSet(s16 arg0, s32 arg1);
void HuWinAttrReset(s16 arg0, u32 arg1);
u8 HuWinStatGet(s16 arg0);
void HuWinMesColSet(s16 arg0, u8 arg1);
void HuWinMesPalSet(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4);
void HuWinBGTPLvlSet(s16 arg0, f32 arg1);
void HuWinBGColSet(s16 arg0, ColorRGB* arg1);
void HuWinMesSpeedSet(s16 arg0, s16 arg1);
void HuWinMesRead(s32 arg0);
void HuWinMesSet(s16 arg0, u32 arg1);
void HuWinInsertMesSet(s16 arg0, u32 arg1, s16 arg2);
s16 HuWinChoiceGet(s16 arg0, s16 arg1);
s16 HuWinChoiceNumGet(s16 arg0);
void HuWinChoiceDisable(s16 arg0, s16 arg1);
s16 HuWinChoiceNowGet(s16 arg0);
void HuWinMesWait(s16 arg0);
void HuWinAnimSet(s16 arg0, AnimData* arg1, s16 arg2, f32 arg3, f32 arg4);
s16 HuWinSprSet(s16 arg0, s16 arg1, f32 arg2, f32 arg3);
void HuWinSprPosSet(s16 arg0, s16 arg1, f32 arg2, f32 arg3);
void HuWinSprPriSet(s16 arg0, s16 arg1, s16 arg2);
s16 HuWinSprIDGet(s16 arg0, s16 arg1);
void HuWinSprKill(s16 arg0, s16 arg1);
void HuWinDispOff(s16 arg0);
void HuWinDispOn(s16 arg0);
void HuWinComKeyWait(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s16 arg4);
void HuWinComKeySet(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void _HuWinComKeySet(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s16 arg4);
void HuWinComKeyGet(s16 arg0, u32* arg1);
void HuWinComKeyReset(void);
void HuWinInsertMesSizeGet(s32 arg0, s16 arg1);
void HuWinMesSizeCancelCRSet(s32 arg0);
void HuWinMesMaxSizeBetGet(f32* arg0, u32 arg1, u32 arg2);
s32 HuWinKeyWaitNumGet(u32 arg0);
void HuWinPushKeySet(s16 arg0, s16 arg1);
void HuWinDisablePlayerSet(s16 arg0, u8 arg1);
void HuWinDisablePlayerReset(s16 arg0, s32 arg1);
void HuWinExCreate(f32 arg0, f32 arg1, s16 arg2, s16 arg3, s16 arg4);
s16 HuWinExCreateStyled(f32 arg0, f32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
void HuWinExAnimIn(s16 arg0);
void HuWinExAnimOut(s16 arg0);
void HuWinExCleanup(s16 arg0);
void HuWinExAnimPopIn(s16 arg0, s16 arg1);

#endif
