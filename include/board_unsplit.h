#ifndef _UNSPLIT_BOARD_H
#define _UNSPLIT_BOARD_H

#include "dolphin.h"

#ifndef _BOARD_MAIN_H
typedef void (*BoardLightHook)(void);
#endif

void BoardShopTutorialExec(s32);
void BoardMGSetupTutorialExec(void);
void BoardBooHouseTutorialExec(void);
void BoardLightHookSet(BoardLightHook set, BoardLightHook reset);
s32 fn_8006DDE8(s16, f32);
void BoardShopHostSet(s16);
void BoardBooHouseHostSet(s16);
s32 BoardCameraRotGet(Vec*);
s32 BoardIsKill(void);

void BoardBowserExec(s32 player, s32 space);
void BoardFortuneExec(s32 player, s32 space);

#endif
