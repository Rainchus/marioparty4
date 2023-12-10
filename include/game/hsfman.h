#ifndef _GAME_HSFMAN_H
#define _GAME_HSFMAN_H

#include "common.h"
#include "game/memory.h"
#include "game/hsfanim.h"
#include "game/hsfformat.h"
#include "game/sprite.h"

typedef struct model_data {
    u8 unk_00;
    u8 unk_01;
    s8 unk_02;
    s8 unk_03;
    s8 unk_04;
    s8 unk_05;
    s16 layer;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10[4];
    s16 cluster_attr[4];
    s16 unk_20;
    u16 camera;
    s16 unk_24;
    s16 unk_26;
    char unk_28[0x10];
    s16 unk_38[8];
    HsfData *unk_48;
    HsfData *unk_4C;
    u32 attr;
    u32 motion_attr;
    Point3d unk_58;
    f32 unk_64;
    Point3d unk_68;
    f32 unk_74;
    char unk_78[0x1C];
    f32 unk_94;
    char unk_98[0x2C];
    HsfData *hsfData;
    HsfData *unk_C8;
    Vec pos;
    Vec rot;
    Vec scale;
    Mtx unk_F0;
    ParticleData *unk_120;
} ModelData;

typedef struct ThreeDCameraStruct {
    f32 unk_00;
    f32 start;
    f32 end;
    char unk_04[0x4C];
} ThreeDCameraStruct;
typedef struct ThreeDProjectionStruct {
    s8 unk_00;
    char unk_01[0x3];
    AnimData *unk_04;
    char unk_08[0xC];
    Point3d unk_14;
    Point3d unk_20;
    Vec unk_2C;
    Mtx unk_38;
    char unk_68[0x30];
} ThreeDProjectionStruct;
typedef struct shadow_data {
    char unk_00[0x2];
    u16 unk_02;
    void*unk_04;
    char unk_08[0x90];
} ShadowData;
typedef struct motion_data {
    s16 unk_00;
    s16 unk_02;
    HsfData *unk_04;
} MotionData;
typedef struct light_data {
    char unk_00[0x44];
} LightData;

void ClusterMotionExec(ModelData*);             /* extern */
void ClusterProc(ModelData*);                   /* extern */
void EnvelopeProc(HsfData*);                           /* extern */
void GXWaitDrawDone();                                 /* extern */
void Hu3DAnimExec();                                   /* extern */
void Hu3DCameraMotionExec(s16);                        /* extern */
void Hu3DCameraSet(s16, void*);                        /* extern */
void Hu3DDraw(ModelData*, f32*, f32*);          /* extern */
void Hu3DDrawPost();                                   /* extern */
void Hu3DDrawPreInit();                                /* extern */
void Hu3DMotionNext(s16);                              /* extern */
void Hu3DShadowExec();                                 /* extern */
void Hu3DSubMotionExec(s16);                           /* extern */
void HuPerfBegin(s32);                                   /* extern */
void HuPerfEnd(s32);                                     /* extern */
void HuSprBegin(void);                                     /* extern */
void HuSprDispInit(void);                                  /* extern */
void HuSprExec(s16);                                     /* extern */
void HuSprFinish(void);                                    /* extern */
void InitVtxParm(HsfData*);                            /* extern */
void ShapeProc(HsfData*);                              /* extern */
void mtxRot(Mtx, f32, f32, f32);                /* extern */
void mtxScaleCat(Mtx, f32, f32, f32);           /* extern */
void mtxTransCat(Mtx, f32, f32, f32);
void Hu3DAnimInit(void);
void Hu3DFogClear(void);
void Hu3DLighInit(void);
void Hu3DMotionInit(void);
void Hu3DParManInit(void);
void Hu3DFogSet(f32, f32, u8, u8, u8);                 /* extern */
void Hu3DMotionClusterSet(s16, s16);                   /* extern */
void Hu3DMotionExec(s16, s16, f32, s32);
f32 Hu3DMotionMaxTimeGet(s16);                      /* extern */
s16 Hu3DMotionModelCreate(s16);                     /* extern */
void Hu3DMotionShapeSet(s16, s16);                     /* extern */
HsfData* LoadHSF(s32);                              /* extern */
void MakeDisplayList(s16, HsfData*);                   /* extern */
void ClusterAdjustObject(HsfData*, HsfData*);          /* extern */
HsfObject* Hu3DObjDuplicate(HsfData*, u32);         /* extern */
void Hu3DAnimModelKill(s16);                           /* extern */
void Hu3DGLightKill(s16);                              /* extern */
void Hu3DLLightKill(s16, s16);                         /* extern */
s32 Hu3DMotionKill(s16);
void Hu3DModelKill(s16);
void Hu3DParManAllKill(void);
s32 MakeObjectName(s32);

void Hu3DInit(void);
void Hu3DPreProc(void);
void Hu3DExec(void);
void Hu3DAllKill(void);
void Hu3DBGColorSet(u8, u8, u8);
void Hu3DLayerHookSet(s16, void (*)(s16));
void Hu3DPauseSet(s32);
void Hu3DNoSyncSet(s32);
s16 Hu3DModelCreate(s32);
s16 Hu3DModelLink(s16);
s16 Hu3DHookFuncCreate(HsfData*);
void Hu3DModelAllKill(void);
void Hu3DModelPosSet(s16, f32, f32, f32);
void Hu3DModelPosSetV(s16, Vec);
void Hu3DModelRotSet(s16, f32, f32, f32);
void Hu3DModelRotSetV(s16, Vec);
void Hu3DModelScaleSet(s16, f32, f32, f32);
void Hu3DModelScaleSetV(s16, Vec);
void Hu3DModelAttrSet(s16, u32);
void Hu3DModelAttrReset(s16, u32);
u32 Hu3DModelAttrGet(s16);
u32 Hu3DModelMotionAttrGet(s16);
void Hu3DModelClusterAttrSet(s16, s16, s32);
void Hu3DModelClusterAttrReset(s16, s16, s32);
void Hu3DModelCameraSet(s16, u16);
void Hu3DModelLayerSet(s16, s16);
HsfObject* Hu3DModelObjPtrGet(s16, s32);
//...
void Hu3DShadowSizeSet(u16);
void Hu3DProjectionKill(s16);
void Hu3DProjectionPosSet(s16, Vec, Vec, Vec);
void Hu3DProjectionTPLvlSet(s16, f32);
void Hu3DMipMapSet(char*, s16, s32, f32);

extern MotionData Hu3DMotion[0x100];
extern f32 lbl_801D4AB0;
extern f32 lbl_801D4AB4;
extern f32 lbl_801D4AB8;
extern f32 lbl_801D4AFC;
extern GXColor lbl_801D6BE0;
extern u32 totalMatCnt;
extern u32 totalMatCnted;
extern u32 totalPolyCnt;
extern u32 totalTexCacheCnt;
extern u32 totalTexCacheCnted;
extern u32 totalTexCnt;
extern u32 totalTexCnted;
#endif
