#ifndef _UNSPLIT_BOARD_H
#define _UNSPLIT_BOARD_H

#include "dolphin.h"

#ifndef _BOARD_SPACE_EVENT_FUNC
#define _BOARD_SPACE_EVENT_FUNC
typedef s32 (*BoardSpaceEventFunc)(void);
#endif

#ifndef _BOARD_MAIN_H
typedef void (*BoardLightHook)(void);
#endif

s32 BoardSpacePosGet(s32, s32, Vec*);
void BoardShopTutorialExec(s32);
void BoardMGSetupTutorialExec(void);
void BoardBooHouseTutorialExec(void);
void BoardCharWheelTargetSet(s32);
void BoardSpaceStarSetIndex(s32);
void BoardLightHookSet(BoardLightHook set, BoardLightHook reset);
s32 fn_8006DDE8(s16, f32);
void BoardSpaceWalkEventFuncSet(BoardSpaceEventFunc func);
void BoardSpaceWalkMiniEventFuncSet(BoardSpaceEventFunc func);
void BoardSpaceLandEventFuncSet(BoardSpaceEventFunc func);
s32 BoardSpaceFlagSearch(s32, u32);
void BoardSpaceInit(s32);
void BoardSpaceDestroy(void);
void BoardShopHostSet(s16);
void BoardBooHouseHostSet(s16);
s32 BoardCameraRotGet(Vec*);
s32 BoardIsKill(void);

void BoardBowserExec(s32 player, s32 space);
void BoardFortuneExec(s32 player, s32 space);

#endif
