#ifndef _BOARD_WINDOW_H
#define _BOARD_WINDOW_H

#include "common.h"
#include "game/window.h"
#include "game/process.h"
#include "game/gamework.h"

void BoardWinInit(void);
void fn_8006FDA0(f32*);
void BoardWinKillAll(void);
void BoardWinDestroy(void);
void BoardWinProc(void);
int BoardWinChoiceGet(void);
void BoardWinCreateChoice(s32, s32, s32, s32);
void BoardWinCreate(s32, s32, s32);
void BoardWinInsertMesSet(s32, s32);
void BoardWinWait(void);
void BoardWinKill(void);
void BoardWinSetAttr(s32);
void BoardWinResetAttr(s32);
void BoardWinChoiceDisable(s32);
void BoardWinKeyWait(void);
int BoardWinSpeedGet(void);
void BoardWinSpeedSet(s32);
s16 BoardWinChoiceNowGet(void);
void BoardWinPriSet(s16);
s16 BoardWinChoiceNowGet2(void);
s32 BoardWinPortraitGet(void);
s32 BoardWinPortraitGetStar(void);
void BoardWinPlayerSet(s32);
void BoardWinStartComKeySet(void);
void BoardWinComKeyFuncSet(void (*));

#endif