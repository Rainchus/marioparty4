#ifndef _UNSPLIT_H
#define _UNSPLIT_H

#include "dolphin.h"

void MGSeqKillAll(void);

void MGSeqPracticeInit(void);
void CharMotionClose(s16 character);
void CharModelClose(s16 character);
void CharModelMotionDataClose(s16 character);
void CharModelKill(s16 character);
s16 CharModelCreate(s16 character, s16 lod);
s16 CharModelMotionCreate(s16 character, s32 data_num);
void CharModelMotionSet(s16 character, s16 motion);
float CharModelMotionMaxTimeGet(s16 character);
float CharModelMotionTimeGet(s16 character);
void CharModelMotionShiftSet(s16 model, s16 motion, float time, float shift_time, u32 attr);
void CharModelMotionTimeSet(s16 character, float time);
void CharModelMotionSpeedSet(s16 character, float speed);
void CharModelMotionKill(s16 character, s32 motion);
void CharModelVoiceEnableSet(s16 character, s16 motion, s32 flag);
void CharModelCoinEffectCreate(s16, Vec *);

s32 CharModelMotionEndCheck(s16 character);

#endif
