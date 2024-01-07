#ifndef _GAME_HSFMAN_H
#define _GAME_HSFMAN_H

#include "common.h"
#include "math.h"
#include "game/memory.h"
#include "game/hsfanim.h"
#include "game/hsfformat.h"
#include "game/sprite.h"
#include "game/init.h"
#include "game/data.h"
#include "game/memory.h"
#include "dolphin/gx/GXVert.h"

#define Hu3DModelCreateFile(data_id) (Hu3DModelCreate(HuDataSelHeapReadNum((data_id), MEMORY_DEFAULT_NUM, HEAP_DATA)))

typedef struct particle_data ParticleData;

typedef struct model_data {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
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
    u16 unk_26;
    u16 unk_28[8];
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
} ModelData; // sizeof 0x124
typedef struct camera_data {
    f32 fov;
    f32 near;
    f32 far;
    f32 aspect;
    f32 aspect_dupe;
    Vec pos;
    Vec up;
    Vec target;
    s16 scissor_x;
    s16 scissor_y;
    s16 scissor_w;
    s16 scissor_h;
    f32 viewport_x;
    f32 viewport_y;
    f32 viewport_w;
    f32 viewport_h;
    f32 near_z;
    f32 far_z;
} CameraData; // sizeof 0x58
typedef struct ThreeDProjectionStruct {
    u8 unk_00;
    char unk_01[0x3];
    void *unk_04;
    Vec unk_08;
    Point3d unk_14;
    Point3d unk_20;
    Vec unk_2C;
    Mtx unk_38;
    Mtx unk_68;
} ThreeDProjectionStruct; // sizeof 0x98
typedef struct shadow_data {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
    void* unk_04;
    Vec unk_08;
    Vec unk_14;
    Vec unk_20;
    Vec unk_2C;
    Mtx unk_38;
    Mtx unk_68;
} ShadowData; // sizeof 0x98
typedef struct motion_data {
    s16 unk_00;
    s16 unk_02;
    HsfData *unk_04;
} MotionData;
typedef struct light_data {
    s16 unk_00;
    s16 unk_02;
    f32 unk_04;
    f32 unk_08;
    char unk_0C[0x10];
    Vec unk_1C;
    Vec unk_28;
    Vec unk_34;
    GXColor color;
} LightData;

extern void ClusterMotionExec(ModelData*);             /* extern */
extern void ClusterProc(ModelData*);                   /* extern */
extern void EnvelopeProc(HsfData*);                           /* extern */
extern void GXWaitDrawDone();                                 /* extern */
extern void Hu3DAnimExec();                                   /* extern */
extern void Hu3DCameraMotionExec(s16);                        /* extern */
extern void Hu3DDraw(ModelData*, Mtx, Vec*);          /* extern */
extern void Hu3DDrawPost();                                   /* extern */
extern void Hu3DDrawPreInit();                                /* extern */
extern void Hu3DMotionNext(s16);                              /* extern */
extern void Hu3DShadowExec();                                 /* extern */
extern void Hu3DSubMotionExec(s16);                           /* extern */
extern void HuPerfBegin(s32);                                   /* extern */
extern void HuPerfEnd(s32);                                     /* extern */
extern void HuSprBegin(void);                                     /* extern */
extern void HuSprDispInit(void);                                  /* extern */
extern void HuSprExec(s16);                                     /* extern */
extern void HuSprFinish(void);                                    /* extern */
extern void InitVtxParm(HsfData*);                            /* extern */
extern void ShapeProc(HsfData*);                              /* extern */
extern void mtxRot(Mtx, f32, f32, f32);                /* extern */
extern void mtxScaleCat(Mtx, f32, f32, f32);           /* extern */
extern void mtxTransCat(Mtx, f32, f32, f32);
extern void Hu3DAnimInit(void);
extern void Hu3DMotionInit(void);
extern void Hu3DParManInit(void);
extern void Hu3DMotionClusterSet(s16, s16);                   /* extern */
extern void Hu3DMotionExec(s16, s16, f32, s32);
extern f32 Hu3DMotionMaxTimeGet(s16);                      /* extern */
extern s16 Hu3DMotionModelCreate(s16);                     /* extern */
extern void Hu3DMotionShapeSet(s16, s16);                     /* extern */
extern void MakeDisplayList(s16, HsfData*);                   /* extern */
extern void ClusterAdjustObject(HsfData*, HsfData*);          /* extern */
extern HsfObject* Hu3DObjDuplicate(HsfData*, u32);         /* extern */
extern void Hu3DAnimModelKill(s16);                           /* extern */
extern void Hu3DGLightKill(s16);                              /* extern */
extern void Hu3DLLightKill(s16, s16);                         /* extern */
extern s32 Hu3DMotionKill(s16);
extern void Hu3DModelKill(s16);
extern void Hu3DParManAllKill(void);
extern f32 Hu3DMotionMotionMaxTimeGet(s16);
extern void Hu3DMotionStartEndSet(s16, f32, f32);
extern void Hu3DMotionTimeSet(s16, f32);
extern void GXInitSpecularDir(GXLightObj*, f32, f32, f32);

void Hu3DInit(void);
void Hu3DPreProc(void);
void Hu3DExec(void);
void Hu3DAllKill(void);
void Hu3DBGColorSet(u8, u8, u8);
void Hu3DLayerHookSet(s16, void (*)(s16));
void Hu3DPauseSet(s32);
void Hu3DNoSyncSet(s32);
s16 Hu3DModelCreate(void *);
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
HsfObject* Hu3DModelObjPtrGet(s16, char *);
void Hu3DModelTPLvlSet(s16, f32);
void Hu3DModelHiliteMapSet(s16, AnimData*);
void Hu3DModelShadowSet(s16);
void Hu3DModelShadowReset(s16);
void Hu3DModelShadowDispOn(s16);
void Hu3DModelShadowDispOff(s16);
void Hu3DModelShadowMapSet(s16);
void Hu3DModelShadowMapObjSet(s16, char *);
void Hu3DModelAmbSet(s16, f32, f32, f32);
void Hu3DModelHookSet(s16, char *, s16);
void Hu3DModelHookReset(s16);
void Hu3DModelHookObjReset(s16, char *);
void Hu3DModelProjectionSet(s16, s16);
void Hu3DModelProjectionReset(s16, s16);
void Hu3DModelHiliteTypeSet(s16, s16);
void Hu3DModelReflectTypeSet(s16, s16);
void Hu3DCameraCreate(s32);
void Hu3DCameraPerspectiveSet(s32, f32, f32, f32, f32);
void Hu3DCameraViewportSet(s32, f32, f32, f32, f32, f32, f32);
void Hu3DCameraScissorSet(s32, u32, u32, u32, u32);
void Hu3DCameraPosSet(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void Hu3DCameraPosSetV(s32 cam, Vec *pos, Vec *up, Vec *target);
void Hu3DCameraKill(s32);
void Hu3DCameraAllKill(void);
void Hu3DCameraSet(s32, Mtx);
BOOL Hu3DModelCameraInfoSet(s16, u16);
s16 Hu3DModelCameraCreate(s16, u16);
void Hu3DCameraMotionOn(s16, s8);
void Hu3DCameraMotionStart(s16, u16);
void Hu3DCameraMotionOff(s16);
void Hu3DLighInit(void);
s16 Hu3DGLightCreate(f32, f32, f32, f32, f32, f32, u8, u8, u8);
s16 Hu3DGLightCreateV(Vec*, Vec*, GXColor*);
s16 Hu3DLLightCreate(s16, f32, f32, f32, f32, f32, f32, u8, u8, u8);
s16 Hu3DLLightCreateV(s16, Vec*, Vec*, GXColor*);
void Hu3DGLightSpotSet(s16, u16, f32);
void Hu3DLLightSpotSet(s16, s16, u16, f32);
void Hu3DGLightInfinitytSet(s16);
void Hu3DLLightInfinitytSet(s16, s16);
void Hu3DGLightPointSet(s16, u16, f32, f32);
void Hu3DLLightPointSet(s16, s16, u16, f32, f32);
void Hu3DGLightKill(s16);
void Hu3DLLightKill(s16, s16);
void Hu3DLightAllKill(void);
void Hu3DGLightColorSet(s16, u8, u8, u8, u8);
void Hu3DLLightColorSet(s16, s16, u8, u8, u8, u8);
void Hu3DGLightPosSetV(s16, Vec*, Point3d*);
void Hu3DLLightPosSetV(s16, s16, Vec*, Point3d*);
void Hu3DGLightPosSet(s16, f32, f32, f32, f32, f32, f32);
void Hu3DLLightPosSet(s16, s16, f32, f32, f32, f32, f32, f32);
void Hu3DGLightPosAimSetV(s16, Point3d*, Point3d*);
void Hu3DLLightPosAimSetV(s16, s16, Point3d*, Point3d*);
void Hu3DGLightPosAimSet(s16, f32, f32, f32, f32, f32, f32);
void Hu3DLLightPosAimSet(s16, s16, f32, f32, f32, f32, f32, f32);
void Hu3DGLightStaticSet(s16, s32);
void Hu3DLLightStaticSet(s16, s16, s32);
s32 Hu3DModelLightInfoSet(s16, s16);
s16 Hu3DLightSet(ModelData*, Mtx*, Mtx*, f32);
void lightSet(LightData* arg0, s16 arg1, Mtx *arg2, Mtx *arg3, f32 arg8);
void Hu3DReflectMapSet(AnimData* arg0);
void Hu3DReflectNoSet(s16 arg0);
void Hu3DFogSet(f32, f32, u8, u8, u8);
void Hu3DFogClear(void);
void Hu3DShadowCreate(f32, f32, f32);
void Hu3DShadowPosSet(Vec*, Vec*, Vec*);
void Hu3DShadowTPLvlSet(f32);
void Hu3DShadowSizeSet(u16);
void Hu3DShadowExec(void);
s16 Hu3DProjectionCreate(void*, f32, f32, f32);
void Hu3DProjectionKill(s16);
void Hu3DProjectionPosSet(s16, Vec, Vec, Vec);
void Hu3DProjectionTPLvlSet(s16, f32);
void Hu3DMipMapSet(char*, s16, s32, f32);

extern ModelData Hu3DData[0x200];
extern CameraData Hu3DCamera[0x10];
extern AnimData *reflectAnim[5];
extern AnimData *hiliteAnim[4];
extern ThreeDProjectionStruct Hu3DProjection[4];
extern ShadowData Hu3DShadowData;
extern Mtx Hu3DCameraMtx;
extern Mtx Hu3DCameraMtxXPose;
extern LightData Hu3DGlobalLight[0x8];
extern s16 reflectMapNo;
extern AnimData *toonAnim;
extern s16 Hu3DShadowCamBit;
extern s32 Hu3DShadowF;
extern s32 shadowModelDrawF;
extern s16 Hu3DCameraNo;
extern s16 Hu3DCameraBit;
extern s16 Hu3DPauseF;

extern MotionData Hu3DMotion[0x100];
extern u32 totalMatCnt;
extern u32 totalMatCnted;
extern u32 totalPolyCnt;
extern u32 totalTexCacheCnt;
extern u32 totalTexCacheCnted;
extern u32 totalTexCnt;
extern u32 totalTexCnted;
#endif
