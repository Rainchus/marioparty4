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

void BoardCameraTargetModelSet(s16 model); 
void BoardCameraMotionStartEx(s16, Vec *, Vec *, f32, f32, s16); 
void BoardCameraMotionWait(void);
s32 BoardSpacePosGet(s32, s32, Vec*);
void BoardShopTutorialExec(s32);
void BoardLotteryTutorialExec(void);
s16 BoardStarHostMdlGet(void);
void BoardStatusShowSetAll(s32);
void BoardMGSetupTutorialExec(void);
void BoardBooHouseTutorialExec(void);
void BoardStatusItemSet(s32);
void BoardTutorialItemSet(s32);
void BoardCharWheelSetTarget(s32);
void BoardTutorialDirInputSet(s32, s32, s32);
void BoardSpaceStarSetIndex(s32);
void BoardModelRotYSet(s16, f32);
f32 BoardModelRotYGet(s16);
void BoardModelLayerSet(s16, u8);
void BoardTutorialHostSet(s16);
s16 BoardModelIDGet(s16);
void BoardModelScaleSetV(s16, Vec*);
void BoardLightHookSet(BoardLightHook set, BoardLightHook reset);
s16 BoardModelCreate(s32, void*, s32);
void BoardModelKill(s16);
void fn_8006DDE8(s16, f32);
s32 BoardModelMotionStart(s16, s32, s32);
void BoardModelMotionSpeedSet(s16, f32);
void BoardModelPosSetV(s16, Vec*);
void BoardModelPosSet(s16, f32, f32, f32);
void BoardModelRotSetV(s16 arg0, Vec* arg1);
void BoardModelVisibilitySet(s16, s32);
void BoardSpaceWalkEventFuncSet(BoardSpaceEventFunc func);
void BoardSpaceWalkMiniEventFuncSet(BoardSpaceEventFunc func);
void BoardSpaceLandEventFuncSet(BoardSpaceEventFunc func);
s32 BoardSpaceFlagSearch(s32, u32);
void BoardSpaceInit(s32);
void BoardSpaceDestroy(void);
void BoardShopHostSet(s16);
void BoardLotteryHostSet(s16);
void BoardStarHostSet(s16);
void BoardBooHouseHostSet(s16);
void BoardTutorialHookSet(void*);
void BoardTutorialBlockSetPos(s32, s32);
s32 BoardCameraRotGet(Vec*);
void BoardModelScaleSet(s16, f32, f32, f32);
s32 BoardIsKill(void);
void BoardModelMtxSet(s16, Mtx);
void BoardModelRotSet(s16, f32, f32, f32);

void BoardBowserExec(s32 player, s32 space);
void BoardBattleExec(s32 player, s32 space);
void BoardFortuneExec(s32 player, s32 space);

#endif
