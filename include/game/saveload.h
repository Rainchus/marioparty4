#ifndef _GAME_SAVELOAD_H
#define _GAME_SAVELOAD_H

#include "common.h"

s32 SLFileOpen(char *arg0);
s32 SLFileCreate(char *arg0, u32 arg1, void *arg2);
s32 SLFileWrite(s32 arg0, void *arg1);
s32 SLFileRead(s32 arg0, void *arg1);
s32 SLFileClose(void);
void SLCurSlotNoSet(s16 arg0);
void SLCurBoxNoSet(s8 arg0);
void SLSaveFlagSet(s32 arg0);
s32 SLSaveFlagGet(void);
void SLSaveDataMake(s32 arg0, OSTime *arg1);
void SLSaveDataInfoSet(OSTime *arg0);
void SLCommonSet(void);
void SLSaveBoard(void);
void SLSaveBoardBackup(void);
s32 SLSave(void);
s32 SLLoad(void);
void SLLoadGameStat(void);
void SLLoadBoard(void);
void SLLoadBoardBackup(void);
void SLSerialNoGet(void);
BOOL SLSerialNoCheck(void);
BOOL SLCheckSumCheck(void);
u16 SLCheckSumGet(void);
void SLCheckSumSet(void);
s32 SLStatSet(s32 arg0);
s32 SLCardMount(s16 arg0);
s32 SLFormat(s16 arg0);
s16 SLMessOut(s16 arg0);

#endif
