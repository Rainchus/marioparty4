#ifndef _GAME_THPMAIN_H
#define _GAME_THPMAIN_H

#include "dolphin/types.h"

s16 HuTHPSprCreateVol(char *path, s16 loop, s16 prio, float volume);
s16 HuTHPSprCreate(char *path, s16 loop, s16 prio);
s16 HuTHP3DCreateVol(char *path, s16 loop, float volume);
s16 HuTHP3DCreate(char *path, s16 loop);
void HuTHPStop(void);
void HuTHPClose(void);
void HuTHPRestart(void);
int HuTHPEndCheck(void);
int HuTHPFrameGet(void);
int HuTHPTotalFrameGet(void);
void HuTHPSetVolume(int left, int right);

#endif