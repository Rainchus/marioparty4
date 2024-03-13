#ifndef _GAME_MINIGAME_SEQ_H
#define _GAME_MINIGAME_SEQ_H

#include "game/object.h"

void MGSeqInit(void);
void MGSeqMain(void);
s16 MGSeqCreate(s16 type, ...);
u8 MGSeqStatGet(s16 id);
void MGSeqPosSet(s16 id, float x, float y);
void MGSeqParamSet(s16 id, s16 param1, s16 param2);
void MGSeqKill(s16 id);
void MGSeqKillAll(void);
s32 MGSeqDoneCheck(void);
void MGSeqStub(void);
void MGSeqPauseInit(void);
void MGSeqPauseEnableCtrl(s32 flag);
void MGSeqPracticeInit(void);
void MGSeqPracticeExitCheck(omObjData *object);

extern OverlayID mgSeqOvlPrev;

#endif
