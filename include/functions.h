#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "dolphin.h"
#include "common_structs.h"

void Hu3DLayerHookSet(short layer, void (*func)(short layer));
void Hu3D2Dto3D(Vec*, s32, Vec*);
void Hu3DBGColorSet(u8, u8, u8);
void Hu3DCameraCreate(s32);
void Hu3DCameraPerspectiveSet(s32, f32, f32, f32, f32);
void Hu3DCameraViewportSet(s32, f32, f32, f32, f32, f32, f32);
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

void HuWinAllKill(void);
void HuWinKill(s16);
void HuWinPriSet(s16, s16);
void HuWinHomeClear(s16);
void HuWinMesPalSet(s16, u8, u8, u8, u8);
void HuWinMesSet(s16, u32);
void HuWinMesSpeedSet(s16, s16);
void HuWinMesMaxSizeGet(s16, f32*, ...);
s16 HuWinCreate(float x, float y, s16 w, s16 h, s16 frame);

void HuAudFXListnerKill(void);
void HuAudDllSndGrpSet(u16 ovl);
void HuAudVoiceInit(s16 ovl);

void MGSeqKillAll(void);

void MGSeqPracticeStart(void);
void fn_8004D6F4(s16 arg);

void BoardWinCreate(s16, s32, s32);
void BoardWinKill(void);
void BoardWinWait(void);

s32 rand8(void);

void BoardCameraTargetSetModel(s16 model); 
void BoardCameraStartMotion2(s16, Vec*, s32, f32, f32, s32); 
void BoardCameraMotionWait(void);
void BoardSpacePosGet(s32, s32, Vec*);
void fn_8007A360(s32);
void fn_8007F894(void);
s16 fn_80083F84(void);
void fn_800884F4(s32);
void fn_800A4C88(void);
void fn_800A6B10(void);
void fn_8008853C(s32);
void BoardTutorialItemSet(s32);
void fn_80082AAC(s32);
void BoardTutorialDirInputSet(s32, s32, s32);
void BoardSpaceStarSetIndex(s32);
void BoardModelRotYSet(s32, f32);
f32 BoardModelRotYGet(s32);
void BoardModelLayerSet(s16, s32);
void BoardTutorialHostSet(s16);
s32 BoardModelIDGet(s16);
void BoardInit(void*, void*);
void BoardModelScaleSetV(s32, Vec*);
void BoardLightHookSet(void*, void*);
s16 BoardModelCreate(s32, void*, s32);
void BoardModelKill(s16);
void fn_8006DDE8(s16, f32);
void BoardModelMotionStart(s16, s32, s32);
void BoardModelMotionSpeedSet(s16, f32);
void BoardModelPosSetV(s16, void*);
void BoardModelPosSet(s16, f32, f32, f32);
s32 BoardModelRotSetV(s16 arg0, Vec* arg1);
void BoardModelVisibilitySet(s16, s32);
void BoardSpaceWalkEventFuncSet(void*);
void BoardSpaceWalkMiniEventFuncSet(void*);
void BoardSpaceLandEventFuncSet(void*);
s32 BoardSpaceFlagSearch(s32, s32);
void BoardSpaceInit(s32);
void BoardSpaceDestroy(void);
void fn_80077AAC(s16);
void fn_8007A83C(s16);
void fn_80083EDC(s16);
void fn_800A4F6C(s16);
void BoardTutorialHookSet(void*);
void BoardTutorialBlockSetPos(s32, s32);
void BoardCameraRotGet(Vec*);
void BoardModelScaleSet(s16, f32, f32, f32);
s32 BoardIsKill(void);
void BoardModelMtxSet(s16, Mtx);
void BoardModelRotSet(s16, f32, f32, f32);

#endif
