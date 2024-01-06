#ifndef _GAME_MSM_H
#define _GAME_MSM_H

#include "dolphin.h"

typedef struct {
    s32 unk00;
    s32 unk04;
    char unk08[4];
    char *unk0C;
    char *unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    void *unk20;
    s32 unk24;
} UnkMsmStruct_00; // Size 0x28

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ s8 unk05;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ char unk08[1];
    /* 0x09 */ s8 unk09;
    /* 0x0A */ s8 unk0A;
    /* 0x0B */ char unk0B[5];
    /* 0x10 */ Vec unk10;
} UnkMsmStruct_01; // Size 0x1C

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ float startDis;
    /* 0x08 */ float frontSurDis;
    /* 0x0C */ float backSurDis;
} UnkMsmStruct_02; // Size (min: 0x10, max: 0x1C)

void msmSysRegularProc(void);
void msmSysSetOutputMode(s32 arg0);
void msmSysSetAux(s32 arg0, s32 arg1);
s32 msmSysGetSampSize(s32 arg0);
s32 msmSysDelGroupAll(void);
s32 msmSysDelGroupBase(s32 arg0);
void msmSysLoadGroupBase(s32 arg0, void *arg1);
s32 msmSysLoadGroupSet(s32 arg0, void *arg1);
s32 msmSysInit(char **arg0, UnkMsmStruct_00 *arg1);
s32 msmMusGetMidiCtrl(s32 arg0, s32 arg1, s32 arg2);
s32 msmMusGetNumPlay(s32 arg0);
s32 msmMusGetStatus(s32 arg0);
void msmMusPauseAll(s32 arg0, s32 arg1);
void msmMusPause(s32 arg0, s32 arg1, s32 arg2);
void msmMusStopAll(s32 arg0, s32 arg1);
void msmMusStop(s32 arg0, s32 arg1);
s32 msmMusPlay(s32 arg0, s32 arg1);
void msmSeDelListener(void);
void msmSeUpdataListener(s32 arg0, s32 arg1);
void msmSeSetListener(s32 arg0, s32 arg1, float arg2, float arg3, UnkMsmStruct_02 *arg4);
s32 msmSeGetEntryID(s32 arg0, void *arg1);
s32 msmSeGetNumPlay(s32 arg0);
s32 msmSeGetStatus(s32 arg0);
s32 msmSeSetParam(s32 arg0, UnkMsmStruct_01 *arg1);
void msmSePauseAll(s32 arg0, s32 arg1);
void msmSeStopAll(s32 arg0, s32 arg1);
void msmSeStop(s32 arg0, s32 arg1);
s32 msmSePlay(s32 arg0, UnkMsmStruct_01 *arg1);
s32 msmStreamGetStatus(s32 arg0);
void msmStreamPauseAll(s32 arg0);
void msmStreamStop(s32 arg0, s32 arg1);
s32 msmStreamPlay(s16 arg0, s32 *arg1);

#endif
