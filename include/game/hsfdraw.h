#ifndef _GAME_HSFDRAW_H
#define _GAME_HSFDRAW_H

#include "game/hsfman.h"
#include "dolphin.h"

void Hu3DDrawPreInit(void);
void Hu3DDraw(ModelData *arg0, Mtx arg1, Vec *arg2);
s32 ObjCullCheck(HsfData *arg0, HsfObject *arg1, Mtx arg2);
void Hu3DDrawPost(void);
void MakeDisplayList(s16 arg0, HsfData *arg1);
HsfConstData *ObjConstantMake(HsfObject *arg0, u32 arg1);
void mtxTransCat(Mtx arg0, float arg1, float arg2, float arg3);
void mtxRotCat(Mtx arg0, float arg1, float arg2, float arg3);
void mtxRot(Mtx arg0, float arg1, float arg2, float arg3);
void mtxScaleCat(Mtx arg0, float arg1, float arg2, float arg3);
s16 HmfInverseMtxF3X3(Mtx arg0, Mtx arg1);
void SetDefLight(Vec arg0, Vec arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA);
void Hu3DModelObjPosGet(s16 arg0, char *arg1, Vec *arg2);
void Hu3DModelObjMtxGet(s16 arg0, char *arg1, Mtx arg2);
void PGObjCall(ModelData *arg0, HsfObject *arg1);
void PGObjCalc(ModelData *arg0, HsfObject *arg1);
void PGObjReplica(ModelData *arg0, HsfObject *arg1);
HsfObject *Hu3DObjDuplicate(HsfData *arg0, u32 arg1);
void Hu3DModelObjDrawInit(void);
void Hu3DModelObjDraw(s16 arg0, char *arg1, Mtx arg2);

#endif
