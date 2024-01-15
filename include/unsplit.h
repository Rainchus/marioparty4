#ifndef _UNSPLIT_H
#define _UNSPLIT_H

#include "dolphin.h"

void Hu3D2Dto3D(Vec*, s16, Vec*);
void HuAudFadeOut(s32 arg0);

void Hu3DModelPosSet(s16 index, float x, float y, float z);
void Hu3DModelRotSet(s16 index, float x, float y, float z);
void Hu3DModelScaleSet(s16 index, float x, float y, float z);

void espInit(void);
void espScaleSet(s16, f32, f32);
s16 espEntry(s32, s32, s32);
void espDispOff(s16);
void espKill(s16);
void espDispOn(s16);
void espPosSet(s16, f32, f32);

void HuAudFXListnerKill(void);
void HuAudDllSndGrpSet(u16 ovl);
void HuAudVoiceInit(s16 ovl);

void MGSeqKillAll(void);

void MGSeqPracticeStart(void);
void fn_8004D6F4(s16 arg);

#endif
