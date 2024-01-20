#ifndef _UNSPLIT_H
#define _UNSPLIT_H

#include "dolphin.h"

void MGSeqKillAll(void);

void MGSeqPracticeStart(void);
void CharModelClose(s16 character);
void CharModelKill(s16 character);
s16 CharModelCreate(s16 character, s16 lod);
s16 CharMotionCreate(s16 character, s32 data_num);
void CharMotionKill(s16 character, u32 motion);

#endif
