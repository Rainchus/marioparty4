#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "dolphin.h"
#include "common_structs.h"

void Hu3DLayerHookSet(short layer, void (*func)(short layer));
void Hu3D2Dto3D(Vec*, s32, Vec*);
void Hu3DModelLightInfoSet(s32, s32);
void Hu3DBGColorSet(u8, u8, u8);
void Hu3DCameraCreate(s32);
void Hu3DCameraPerspectiveSet(s32, f32, f32, f32, f32);
void Hu3DCameraViewportSet(s32, f32, f32, f32, f32, f32, f32);
void HuAudFadeOut(int arg0);

void WipeCreate(char dir, char type, short duration);
u8 WipeStatGet(void);

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

void HuWinAllKill(void);
void HuWinMesSet(s16, s32);
void HuWinKill(s16);
void HuWinPriSet(s16, s32);
void HuWinHomeClear(s16);
void HuWinMesPalSet(s16, s32, s32, s32, s32);
void HuWinMesSet(s16, s32);
void HuWinMesSpeedSet(s16, s32);
void HuWinMesMaxSizeGet(s32, f32*, ...);
s16 HuWinCreate(float x, float y, s16 w, s16 h, s16 frame);

void HuPadRumbleAllStop(void);

void HuAudFXListnerKill(void);
void HuAudDllSndGrpSet(u16 ovl);
void HuAudVoiceInit(s16 ovl);

void MGSeqKillAll(void);

void MGSeqPracticeStart(void);
void fn_8004D6F4(s16 arg);

s32 _CheckFlag(u32 flag);

void BoardWinCreate(s16, s32, s32);
void BoardWinKill(void);
void BoardWinWait(void);

s32 HuTHPFrameGet(void);

s32 rand8(void);

void fn_8005D8E8(void); 
void fn_8005DB6C(s16, Vec*, s32, f32, f32, s32); 
void fn_8005E0C0(void);
void fn_80074210(s32, s32, Vec*);
void fn_8007A360(s32);
void fn_8007F894(void);
void fn_80083F84(void);
void fn_800884F4(s32);
void fn_800A4C88(void);
void fn_800A6B10(void);
void fn_8008853C(s32);
void fn_800B42B4(s32);
void fn_80082AAC(s32);
void fn_800B4264(s32, s32, s32);
void fn_8007500C(s32);
void fn_8006F0D4(s32, f32);
f32 fn_8006F128(s32);
void fn_8006F61C(s16, s32);
void fn_800B42BC(s16);
s32 fn_8006DBD4(s16);
void fn_8005B150(void*, void*);
void fn_8006F2E8(s32, Vec*);
void fn_8005D10C(void*, void*);
s16 fn_8006D9A4(s32, void*, s32);
void fn_8006DB90(s16);
void fn_8006DDE8(s16, f32);
void fn_8006E2B8(s16, s32, s32);
void fn_8006E878(s16, f32);
void fn_8006F158(s16, void*);
void fn_8006F1A8(s16, f32, f32, f32);
s32 fn_8006F220(s16 arg0, Vec* arg1);
void fn_8006F50C(s16, s32);
void fn_80073FF4(void*);
void fn_80073FFC(void*);
void fn_80074004(void*);
s32 fn_800745F0(s32, s32);
void fn_800772EC(s32);
void fn_80077A3C(void);
void fn_80077AAC(s16);
void fn_8007A83C(s16);
void fn_80083EDC(s16);
void fn_800A4F6C(s16);
void fn_800B3FD8(void*);
void fn_800B4274(s32, s32);
void fn_8005D5C0(Vec*);
void fn_8006F338(s16, f32, f32, f32);
s32 fn_8005B6A8(void);
void fn_8006EFBC(s16, Mtx);
void fn_8006F270(s16, f32, f32, f32);

#endif
