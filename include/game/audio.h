#ifndef _GAME_AUDIO_H
#define _GAME_AUDIO_H

#include "dolphin.h"

typedef struct sndGrpTbl_s {
    s16 ovl;
    s16 grpSet;
    s32 auxANo;
    s32 auxBNo;
    s8 auxAVol;
    s8 auxBVol;
} SNDGRPTBL;


void HuAudInit(void);
s32 HuAudStreamPlay(char *name, BOOL flag);
void HuAudStreamVolSet(s16 vol);
void HuAudStreamPauseOn(void);
void HuAudStreamPauseOff(void);
void HuAudStreamFadeOut(s32 streamNo);
void HuAudAllStop(void);
void HuAudFadeOut(s32 speed);
int HuAudFXPlay(int seId);
int HuAudFXPlayVol(int seId, s16 vol);
int HuAudFXPlayVolPan(int seId, s16 vol, s16 pan);
void HuAudFXStop(int seNo);
void HuAudFXAllStop(void);
void HuAudFXFadeOut(int seNo, s32 speed);
void HuAudFXPanning(int seNo, s16 pan);
void HuAudFXListnerSet(Vec *pos, Vec *heading, float sndDist, float sndSpeed);
void HuAudFXListnerSetEX(Vec *pos, Vec *heading, float sndDist, float sndSpeed, float startDis, float frontSurDis, float backSurDis);
void HuAudFXListnerUpdate(Vec *arg0, Vec *arg1);
int HuAudFXEmiterPlay(int seId, Vec *pos);
void HuAudFXEmiterUpDate(int seNo, Vec *pos);
void HuAudFXListnerKill(void);
void HuAudFXPauseAll(s32 arg0);
s32 HuAudFXStatusGet(int seNo);
s32 HuAudFXPitchSet(int seNo, s16 pitch);
s32 HuAudFXVolSet(int seNo, s16 vol);
s32 HuAudSeqPlay(s16 arg0);
void HuAudSeqStop(s32 arg0);
void HuAudSeqFadeOut(s32 arg0, s32 arg1);
void HuAudSeqAllFadeOut(s32 arg0);
void HuAudSeqAllStop(void);
void HuAudSeqPauseAll(s32 arg0);
void HuAudSeqPause(s32 arg0, s32 arg1, s32 arg2);
s32 HuAudSeqMidiCtrlGet(s32 arg0, s8 arg1, s8 arg2);
s32 HuAudSStreamPlay(s16 arg0);
void HuAudSStreamStop(s32 arg0);
void HuAudSStreamFadeOut(s32 arg0, s32 arg1);
void HuAudSStreamAllFadeOut(s32 arg0);
void HuAudSStreamAllStop(void);
s32 HuAudSStreamStatGet(s32 arg0);
void HuAudDllSndGrpSet(u16 ovl);
void HuAudSndGrpSetSet(s16 arg0);
void HuAudSndGrpSet(s16 arg0);
void HuAudSndCommonGrpSet(s16 arg0, s32 arg1);
void HuAudAUXSet(s32 arg0, s32 arg1);
void HuAudAUXVolSet(s8 arg0, s8 arg1);
void HuAudVoiceInit(s16 ovl);
s32 HuAudPlayerVoicePlay(s16 arg0, s16 arg1);
s32 HuAudPlayerVoicePlayPos(s16 arg0, s16 arg1, Vec *arg2);
void HuAudPlayerVoicePlayEntry(s16 arg0, s16 arg1);
s32 HuAudCharVoicePlay(s16 arg0, s16 arg1);
s32 HuAudCharVoicePlayPos(s16 arg0, s16 arg1, Vec *arg2);
void HuAudCharVoicePlayEntry(s16 arg0, s16 arg1);

extern float Snd3DBackSurDisOffset;
extern float Snd3DFrontSurDisOffset;
extern float Snd3DStartDisOffset;
extern float Snd3DSpeedOffset;
extern float Snd3DDistOffset;
extern s32 musicOffF;
extern u8 fadeStat;

extern SNDGRPTBL sndGrpTable[];

#endif
