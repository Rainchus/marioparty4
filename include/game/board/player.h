#ifndef _BOARD_PLAYER_H
#define _BOARD_PLAYER_H

#include "math.h"
#include "board_unsplit.h"
#include "dolphin/os/OSFastCast.h"
#include "game/gamework_data.h"
#include "game/gamework.h"
#include "game/window.h"
#include "game/object.h"
#include "game/process.h"
#include "game/hsfman.h"
#include "game/gamework_data.h"
#include "game/board/main.h"
#include "game/board/space.h"

extern s16 boardPlayerMdl[4];

static inline s16 BoardPlayerHandicapGet(s32 player)
{
	return GWPlayer[player].handicap;
}

static inline s32 BoardPlayerGetCurrIdx()
{
	return GWSystem.player_curr;
}

static inline PlayerState *BoardPlayerGet(s32 player)
{
	return &GWPlayer[player];
}

static inline PlayerState *BoardPlayerGetCurr()
{
	return &GWPlayer[BoardPlayerGetCurrIdx()];
}

static inline s16 BoardPlayerModelGet(s32 player)
{
	PlayerState *player_ptr = BoardPlayerGet(player);
	return boardPlayerMdl[player_ptr->player_idx];
}

static inline s16 BoardPlayerModelGetCurr()
{
	PlayerState *player = BoardPlayerGetCurr();
	return boardPlayerMdl[player->player_idx];
}

s32 BoardRollTypeGet(void);
void BoardRollTypeSet(s32 type);
s32 BoardPlayerGetCharMess(s32 player);
char* BoardPlayerGetCharName(s32 player);
s32 BoardPlayerIsAllCom(void);
void BoardPlayerInit(void);
void BoardPlayerModelInit(void);
void BoardPlayerModelKill(void);
void BoardPlayerLayerSet(s32, s32);
void BoardPlayerCameraSet(s32, u16);
void fn_80062A40(s32, f32);
void BoardPlayerExistCheck(s32, s32);
s32 BoardPlayerItemAdd(s32, s32);
s32 BoardPlayerItemRemove(s32, s32);
s32 BoardPlayerItemFind(s32, s32);
s32 BoardPlayerItemCount(s32);
void BoardPlayerCornerPosSet(s32 arg0);
void BoardPlayerCornerPosGet(s32, Vec*);
void BoardPlayerAmbSet(s32, f32, f32, f32);
void BoardPlayerMtxSet(s32, Mtx*);
void BoardPlayerPosSetV(s32, Vec*);
void BoardPlayerPosSet(s32, f32, f32, f32);
void BoardPlayerPosGet(s32, Vec*);
void BoardPlayerRotSetV(s32, Vec*);
void BoardPlayerRotSet(s32, f32, f32, f32);
void BoardPlayerRotGet(s32, Vec*);
void BoardPlayerRotYSet(s32, f32);
f32 BoardPlayerRotYGet(s32);
void BoardPlayerScaleSetV(s32, Vec*);
void BoardPlayerScaleSet(s32, f32, f32, f32);
s16 BoardPlayerCurrMotionGet(s32);
void BoardPlayerMotionCreate(s32, s32);
void BoardPlayerMotionKill(s32, s32);
void BoardPlayerMotionEndCheck(s32);
void BoardPlayerMotionEndWait(s32);
void BoardPlayerMotionStart(s32, s32, s32);
void BoardPlayerMotionShiftSet(s32, s32, f32, f32, u32);
void BoardPlayerMotionSpeedSet(s32, f32);
void BoardPlayerMotionTimeSet(s32, f32);
f32 BoardPlayerMotionTimeGet(s32);
f32 BoardPlayerMotionMaxTimeGet(s32);
void BoardPlayerMotionTimeRangeSet(s32, f32, f32);
void BoardPlayerModelAttrSet(s32, s32);
void BoardPlayerModelAttrReset(s32, s32);
void BoardPlayerCoinsSet(s32, s32);
s32 BoardPlayerCoinsGet(s32);
void BoardPlayerCoinsAdd(s32, s32);
void BoardPlayerStarsAdd(s32, s32);
void BoardPlayerSizeSet(s32, s32);
s32 BoardPlayerSizeGet(s32);
s32 BoardPlayerSameTeamFind(s32);
s32 BoardPlayerTeamFind(s32);
s32 BoardPlayerRankCalc(s32);
void BoardPlayerPreTurnHookSet(s32, s32 (*)());
void BoardPlayerPostTurnHookSet(s32, s32 (*)());
void BoardPlayerTurnExec(s32);
void BoardPlayerTurnRollExec(s32);
void BoardPlayerTurnMoveExec(s32);
void BoardPlayerPostTurnHookExec(s32);
void BoardPlayerSizeRestore(s32);
void BoardPlayerZoomRestore(s32);
void BoardJunctionMaskSet(s32);
void BoardJunctionMaskReset(s32);
void BoardJunctionMaskZero(void);
void InitJunction(s32, s32, f32);
//...
s32 GetDefaultDirection(f32, f32*, s32);
s32 BoardPlayerAutoSizeGet(s32);
void BoardPlayerAutoSizeSet(s32, s32);
void BoardPlayerCopyMat(s32);
void BoardBowserSuitKill(s32);
void SetRollPlayerSize(s32);
void BoardDiceDigit2DUpdateEnable(s32);
void BoardPlayerMoveTo(s32, s16);
void BoardPlayerZoomRestore(s32);
void BoardRotateDiceNumbers(s32);
s32 DoSparkSpace(s32, s16*);
s32 MegaPlayerPassFunc(s32, s16);
s32 BoardPlayerAnimBlendCheck(s32);
void BoardPlayerCoinsSet(s32 player, s32 value);
s32 BoardPlayerSizeGet(s32 player);
void BoardPlayerAutoSizeSet(s32 player, s32 value);
void BoardPlayerMotionStart(s32, s32, s32);
void BoardPlayerRotYSet(s32 player, float rot_y);
void BoardPlayerZoomRestore(s32 player);

#endif