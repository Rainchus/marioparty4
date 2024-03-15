#ifndef _GAME_MINIGAME_SEQ_H
#define _GAME_MINIGAME_SEQ_H

#include "game/object.h"
#include "stdarg.h"

typedef struct seq_work SeqWork;

typedef int (*SeqUpdateFunc)(SeqWork *work);
typedef int (*SeqInitFunc)(SeqWork *work, va_list params);

typedef struct seq_work {
	SeqUpdateFunc update;
	char *data;
	float x;
	float y;
	float scale_x;
	float scale_y;
	float unk_18;
	float angle;
	float win_scale;
	float unk_24;
	s16 time;
	s16 time_max;
	s16 timer_val;
	s16 state;
	s16 alt_word_len;
	s16 word_len;
	s16 param[2];
	s16 type;
	s16 spr_grp[16];
	s16 sprite[16];
	u8 seq_no;
	u8 stat;
	u8 unk_7C;
	u8 unk_7D;
} SeqWork;

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
