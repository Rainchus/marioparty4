#include "game/hsfman.h"

ModelData Hu3DData[0x200];
CameraData Hu3DCamera[0x10];
s16 layerNum[8];
void (*layerHook[8])(s16);
AnimData *reflectAnim[5];
AnimData *hiliteAnim[4];
ThreeDProjectionStruct Hu3DProjection[4];
ShadowData Hu3DShadowData;
HsfScene FogData;
Mtx Hu3DCameraMtx;
Mtx Hu3DCameraMtxXPose;
LightData Hu3DGlobalLight[0x8];
LightData Hu3DLocalLight[0x20];
Mtx lbl_8018D39C;
GXColor BGColor;
s16 reflectMapNo;
AnimData *toonAnim;
s16 Hu3DShadowCamBit;
s32 Hu3DShadowF;
s32 shadowModelDrawF;
s16 Hu3DProjectionNum;
s16 Hu3DCameraNo;
s16 Hu3DCameraBit;
HsfData* Hu3DMallocNo;
s16 Hu3DPauseF;
u16 Hu3DCameraExistF;
u16 NoSyncF;
s32 modelKillAllF;

#include "refMapData0.inc"
#include "refMapData1.inc"
#include "refMapData2.inc"
#include "refMapData3.inc"
#include "refMapData4.inc"
#include "toonMapData.inc"
#include "toonMapData2.inc"
#include "hiliteData.inc"
#include "hiliteData2.inc"
#include "hiliteData3.inc"
#include "hiliteData4.inc"

void Hu3DInit(void) {
    ModelData* data;
    CameraData* camera;
    s16 i;

    data = Hu3DData;
    for (i = 0; i < 0x200; i++, data++) {
        data->hsfData = NULL;
    }
    camera = Hu3DCamera;
    for (i = 0; i < 0x10; i++, camera++) {
        camera->fov = -1.0f;
    }
    Hu3DMotionInit();
    Hu3DLighInit();
    BGColor.r = BGColor.g = BGColor.b = 0;
    BGColor.a = 0xFF;
    for (i = 0; i < 8; i++) {
        layerNum[i] = 0;
        layerHook[i] = 0;
    }
    reflectAnim[0] = HuSprAnimRead(refMapData0);
    reflectAnim[1] = HuSprAnimRead(refMapData1);
    reflectAnim[2] = HuSprAnimRead(refMapData2);
    reflectAnim[3] = HuSprAnimRead(refMapData3);
    reflectAnim[4] = HuSprAnimRead(refMapData4);
    reflectMapNo = 0;
    toonAnim = HuSprAnimRead(toonMapData);
    hiliteAnim[0] = HuSprAnimRead(hiliteData);
    hiliteAnim[1] = HuSprAnimRead(hiliteData2);
    hiliteAnim[2] = HuSprAnimRead(hiliteData3);
    hiliteAnim[3] = HuSprAnimRead(hiliteData4);
    Hu3DFogClear();
    Hu3DAnimInit();
    Hu3DParManInit();
    for (i = 0; i < 4; i++) {
        Hu3DProjection[i].unk_04 = NULL;
    }
    Hu3DShadowCamBit = 0;
    Hu3DShadowData.unk_04 = 0;
    Hu3DShadowF = 0;
    Hu3DProjectionNum = 0;
    Hu3DCameraExistF = 0;
    modelKillAllF = 0;
    Hu3DPauseF = 0;
    NoSyncF = 0;
}

void Hu3DPreProc(void) {
    ModelData *data;
    s16 i;
    
    GXSetCopyClear(BGColor, 0xFFFFFF);
    data = &Hu3DData[0];
    for (i = 0; i < 0x200; i++, data++) {
        if (data->hsfData != 0) {
            data->attr &= ~0x800;
        }
    }
    totalPolyCnted = totalPolyCnt;
    totalMatCnted = totalMatCnt;
    totalTexCnted = totalTexCnt;
    totalTexCacheCnted = totalTexCacheCnt;
    totalPolyCnt = totalMatCnt = totalTexCnt = totalTexCacheCnt = 0;
}

void Hu3DExec(void) {
    GXColor unusedColor;
    CameraData* camera;
    ModelData* data;
    s16 temp_r22;
    s16 var_r23;
    s16 var_r25;
    s16 var_r24;
    s16 j;
    s16 i;
    void (* temp)(s16);
    Mtx sp40;
    Mtx sp10;
    ThreeDProjectionStruct* var_r26;

    unusedColor = lbl_801D6BE0;
    HuPerfBegin(3);
    GXSetCurrentMtx(0U);
    camera = Hu3DCamera;
    shadowModelDrawF = 0;
    HuSprBegin();
    var_r24 = 0;
    for (Hu3DCameraNo = 0; Hu3DCameraNo < 0x10; Hu3DCameraNo++, camera++) {
        if (-1.0f != camera->fov) {
            GXInvalidateVtxCache();
            temp_r22 = (s16) (1 << Hu3DCameraNo);
            Hu3DCameraBit = temp_r22;
            if (NoSyncF == 0) {
                if (Hu3DCameraNo == 0 && Hu3DShadowF != 0 && Hu3DShadowCamBit != 0) {
                    Hu3DShadowExec();
                    var_r24 = 1;
                    GXSetDrawDone();
                } else if (Hu3DCameraNo != 0) {
                    var_r24 = 1;
                    GXSetDrawDone();
                }
            } else if (Hu3DCameraNo == 0 && Hu3DShadowF != 0 && Hu3DShadowCamBit != 0) {
                Hu3DShadowExec();
            }
            var_r26 = &Hu3DProjection[0];
            for (i = 0; i < 4; i++, var_r26++) {
                if (var_r26->unk_04 != 0) {
                    C_MTXLookAt(var_r26->unk_38, &var_r26->unk_14, &var_r26->unk_2C, &var_r26->unk_20);
                }
            }
            if (Hu3DCameraNo == 0) {
                HuSprDispInit();
                HuSprExec(0x7F);
            }
            if (FogData.fogType != GX_FOG_NONE) {
                GXSetFog(FogData.fogType, FogData.start, FogData.end, camera->near, camera->far, FogData.color);
            }
            for (j = 0; j < 8; j++) {
                if (layerHook[j] != 0) {
                    Hu3DCameraSet(Hu3DCameraNo, Hu3DCameraMtx);
                    PSMTXInvXpose(Hu3DCameraMtx, Hu3DCameraMtxXPose);
                    temp = layerHook[j];
                    temp(j);
                }
                if (layerNum[j] != 0) {
                    Hu3DDrawPreInit();
                    Hu3DCameraSet(Hu3DCameraNo, Hu3DCameraMtx);
                    PSMTXInvXpose(Hu3DCameraMtx, Hu3DCameraMtxXPose);
                    data = Hu3DData;
                    for (i = 0, var_r23 = i; i < 0x200; i++, data++) {
                        if (data->hsfData != 0) {
                            if ((data->attr & 0x10000) != 0) {
                                Hu3DCameraMotionExec(i);
                            } else {
                                if ((data->attr & 0x2001) == 0x2001 && data->unk_08 != -1) {
                                    Hu3DMotionExec(i, data->unk_08, data->unk_64, 0);
                                }
                                if ((data->attr & 9) == 0 && (data->camera & temp_r22) != 0 && data->layer == j) {
                                    if (((data->attr & 0x800) == 0 && (data->attr & 0x100) == 0) || ((data->attr & 0x100) != 0 && (data->unk_00 & 1) != 0)) {
                                        var_r25 = 0;
                                        data->motion_attr &= 0xBFFFFFFF;
                                        if (data->unk_08 != -1) {
                                            Hu3DMotionExec(i, data->unk_08, data->unk_64, 0);
                                        }
                                        if (data->unk_0C != -1) {
                                            Hu3DSubMotionExec(i);
                                        }
                                        if (data->unk_0A != -1) {
                                            Hu3DMotionExec(i, data->unk_0A, data->unk_74, 1);
                                        }
                                        if ((data->attr & 0x400) != 0) {
                                            ClusterMotionExec(data);
                                            var_r25 = 1;
                                        }
                                        if (data->unk_0E != -1) {
                                            if (data->unk_08 == -1) {
                                                Hu3DMotionExec(i, data->unk_0E, data->unk_94, 0);
                                            } else {
                                                Hu3DMotionExec(i, data->unk_0E, data->unk_94, 1);
                                            }
                                            var_r25 = 1;
                                        }
                                        if ((data->attr & 0x90) == 0 && (data->motion_attr & 0x40000002) == 0) {
                                            var_r25 = 1;
                                            InitVtxParm(data->hsfData);
                                            if (data->unk_0E != -1) {
                                                ShapeProc(data->hsfData);
                                            }
                                            if ((data->attr & 0x400) != 0) {
                                                ClusterProc(data);
                                            }
                                            if (data->hsfData->cenvCnt != 0) {
                                                EnvelopeProc(data->hsfData);
                                            }
                                            PPCSync();
                                        }
                                        if (var_r25 != 0) {
                                            GXInvalidateVtxCache();
                                        }
                                        data->attr |= 0x800;
                                    }
                                    if (var_r24 != 0 && (data->attr & 0x10) != 0) {
                                        GXWaitDrawDone();
                                        var_r24 = 0;
                                    }
                                    if ((data->attr & 0x8000) == 0 && (0.0f != data->scale.x || 0.0f != data->scale.y || 0.0f != data->scale.z)) {
                                        mtxRot(sp40, data->rot.x, data->rot.y, data->rot.z);
                                        mtxScaleCat(sp40, data->scale.x, data->scale.y, data->scale.z);
                                        mtxTransCat(sp40, data->pos.x, data->pos.y, data->pos.z);
                                        PSMTXConcat(Hu3DCameraMtx, sp40, sp10);
                                        PSMTXConcat(sp10, data->unk_F0, sp10);
                                        Hu3DDraw(data, sp10[0], &data->scale.x);
                                    }
                                    data->unk_00++;
                                    var_r23++;
                                    if (var_r23 >= layerNum[j]) {
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    Hu3DDrawPost();
                }
            }
        }
    }
    HuSprDispInit();
    HuSprExec(0);
    data = Hu3DData;
    for (i = 0; i < 0x200; i++, data++) {
        if (data->hsfData != 0 && (data->unk_08 != -1 || (data->attr & 0x400) != 0 || data->unk_0E != -1) && (Hu3DPauseF == 0 || (data->attr & 0x200000) != 0)) {
            Hu3DMotionNext(i);
        }
    }
    HuSprFinish();
    Hu3DAnimExec();
    HuPerfEnd(3);
}

void Hu3DAllKill(void) {
    s16 i;
    Hu3DModelAllKill();
    Hu3DMotionAllKill();
    Hu3DCameraAllKill();
    Hu3DLightAllKill();
    Hu3DAnimAllKill();
    if(reflectAnim[0] != (AnimData *)refMapData0) {
        HuMemDirectFree(reflectAnim[0]);
    }
    reflectAnim[0] = HuSprAnimRead(refMapData0);
    if(Hu3DShadowData.unk_04) {
        HuMemDirectFree(Hu3DShadowData.unk_04);
        Hu3DShadowCamBit = 0;
        Hu3DShadowData.unk_04 = NULL;
        Hu3DShadowF = 0;
    }
    Hu3DFogClear();
    for(i=0; i<8; i++) {
        layerNum[i] = 0;
        layerHook[i] = NULL;
    }
    for(i=0; i<4; i++) {
        if(Hu3DProjection[i].unk_04) {
            Hu3DProjectionKill(i);
        }
        Hu3DProjection[i].unk_04 = NULL;
    }
    NoSyncF = 0;
}

void Hu3DBGColorSet(u8 arg0, u8 arg1, u8 arg2) {
    BGColor.r = arg0;
    BGColor.g = arg1;
    BGColor.b = arg2;
}

void Hu3DLayerHookSet(s16 layer, void (*func)(s16)) {
    layerHook[layer] = func;
}

void Hu3DPauseSet(s32 arg0) {
    Hu3DPauseF = arg0;
}

void Hu3DNoSyncSet(s32 arg0) {
    NoSyncF = arg0;
}

// ,,,

s16 Hu3DModelCreate(s32 arg0) {
    HsfData* temp_r0;
    ModelData* var_r31;
    s16 i;
    s16 var_r30;

    var_r31 = Hu3DData;
    
    for (var_r30 = 0; var_r30 < 0x200; var_r30++, var_r31++) {
        if (var_r31->hsfData == 0x0) {
            break;
        }
    }
    if (var_r30 == 0x200) {
        OSReport("Error: Not Found %s for MipMapSet\n");
        return -1;
    }
    var_r31->hsfData = LoadHSF(arg0);
    var_r31->unk_48 = Hu3DMallocNo = var_r31->hsfData;
    var_r31->attr = 0;
    var_r31->motion_attr = 0;
    var_r31->unk_02 = 0;
    MakeDisplayList(var_r30, (HsfData* ) var_r31->unk_48);
    var_r31->unk_68.x = 1.0f;
    for (i = 0; i < 4; i++) {
        var_r31->unk_10[i] = -1;
    }
    var_r31->unk_0A = -1;
    var_r31->unk_0C = -1;
    var_r31->unk_0E = -1;
    var_r31->unk_64 = 0.0f;
    if (var_r31->hsfData->motionCnt != 0) {
        var_r31->unk_08 = var_r31->unk_20 = Hu3DMotionModelCreate(var_r30);
        if (var_r31->hsfData->cenvCnt != 0) {
            Hu3DMotionExec(var_r30, var_r31->unk_08, 0.0f, 0);
            EnvelopeProc(var_r31->hsfData);
            PPCSync();
        }
        if (var_r31->hsfData->clusterCnt != 0) {
            Hu3DMotionClusterSet(var_r30, var_r31->unk_08);
        }
        if (var_r31->hsfData->shapeCnt != 0) {
            Hu3DMotionShapeSet(var_r30, var_r31->unk_08);
        }
        var_r31->unk_68.y = 0.0f;
        var_r31->unk_68.z = Hu3DMotionMaxTimeGet(var_r30);
    } else {
        var_r31->unk_20 = var_r31->unk_08 = -1;
    }
    var_r31->pos.x = var_r31->pos.y = var_r31->pos.z = 0.0f;
    var_r31->rot.x = var_r31->rot.y = var_r31->rot.z = 0.0f;
    var_r31->scale.x = var_r31->scale.y = var_r31->scale.z = 1.0f;
    var_r31->camera = -1;
    var_r31->layer = 0;
    var_r31->unk_120 = 0;
    var_r31->unk_26 = 0;
    var_r31->unk_03 = 0;
    var_r31->unk_58.x = var_r31->unk_58.z = var_r31->unk_58.y = 1.0f;
    var_r31->unk_04 = -1;
    var_r31->unk_24 = -1;
    
    for (i = 0; i < 8; i++) {
        var_r31->unk_38[i] = -1;
    }
    var_r31->unk_01 = 0;
    var_r31->unk_00 = (u8) var_r30;
    PSMTXIdentity(var_r31->unk_F0);
    layerNum[0] += 1;
    HuMemDCFlush(HEAP_DATA);
    if ((var_r31->hsfData->sceneCnt != 0) && ((var_r31->hsfData->scene->start != 0.0f) || (var_r31->hsfData->scene->end != 0.0f))) {
        Hu3DFogSet(var_r31->hsfData->scene->start, var_r31->hsfData->scene->end, var_r31->hsfData->scene->color.r, var_r31->hsfData->scene->color.g, var_r31->hsfData->scene->color.b);
    }
    return var_r30;
}

s16 Hu3DModelLink(s16 arg0) {
    HsfObject* temp_r3_2;
    ModelData* temp_r30;
    ModelData* var_r31;
    s16 var_r28;
    s16 i;
    s32 temp_r0;
    s32 temp_r3;
    s32 temp_r5;
    s32 var_ctr;
    HsfData* var_r4;
    HsfData* var_r5;

    temp_r30 = &Hu3DData[arg0];
    var_r31 = Hu3DData;
    for (var_r28 = 0; var_r28 < 0x200; var_r28++, var_r31++) {
        if (var_r31->hsfData == 0x0) {
            break;
        }
    }
    if (var_r28 == 0x200) {
        return -1;
    }
    var_r31->unk_C8 = temp_r30->hsfData;
    var_r31->hsfData = HuMemDirectMallocNum(HEAP_DATA, 0x80, (u32)var_r31->unk_4C);
    var_r31->unk_4C = var_r31->hsfData;
    *var_r31->hsfData = *temp_r30->hsfData;
    temp_r3_2 = Hu3DObjDuplicate(var_r31->hsfData, (u32)var_r31->unk_4C);
    var_r31->hsfData->root = (HsfObject*)((u32)temp_r3_2 + ((u32)var_r31->hsfData->root - (u32)var_r31->hsfData->object));
    var_r31->hsfData->object = temp_r3_2;
    var_r31->unk_48 = temp_r30->unk_48;
    var_r31->attr = temp_r30->attr;
    temp_r30->attr |= 0x100000;
    var_r31->motion_attr = temp_r30->motion_attr;
    var_r31->pos.x = var_r31->pos.y = var_r31->pos.z = 0.0f;
    var_r31->rot.x = var_r31->rot.y = var_r31->rot.z = 0.0f;
    var_r31->scale.x = var_r31->scale.y = var_r31->scale.z = 1.0f;
    var_r31->unk_08 = temp_r30->unk_08;
    if (var_r31->unk_08 != -1) {
        var_r31->unk_68.y = 0.0f;
        var_r31->unk_68.z = Hu3DMotionMaxTimeGet(var_r28);
    }
    var_r31->unk_0C = var_r31->unk_0A = var_r31->unk_0E = -1;
    for (i = 0; i < 4; i++) {
        var_r31->unk_10[i] = temp_r30->unk_10[i];
        if (var_r31->unk_10[i] != -1) {
            ClusterAdjustObject(var_r31->hsfData, Hu3DMotion[var_r31->unk_10[i]].unk_04);
            var_r31->attr |= 0x400;
        }
    }
    var_r31->unk_64 = temp_r30->unk_64;
    var_r31->unk_68.x = temp_r30->unk_68.x;
    var_r31->unk_20 = temp_r30->unk_20;
    var_r31->camera = -1;
    var_r31->layer = 0;
    var_r31->unk_120 = 0;
    var_r31->unk_26 = 0;
    var_r31->unk_03 = 0;
    var_r31->unk_02 = 0;
    var_r31->unk_58.x = var_r31->unk_58.z = var_r31->unk_58.y = 1.0f;
    var_r31->unk_04 = -1;
    var_r31->unk_24 = arg0;
    for (i = 0; i < 8; i++) {
        var_r31->unk_38[i] = -1;
    }
    var_r31->unk_01 = 0;
    PSMTXIdentity(var_r31->unk_F0);
    layerNum[0] += 1;
    return var_r28;
}

s16 Hu3DHookFuncCreate(HsfData* arg0) {
    HsfData* sp8;
    ModelData* var_r31;
    s16 var_r29;
    s16 i;

    var_r31 = Hu3DData;
    for (var_r29 = 0; var_r29 < 0x200; var_r29++, var_r31++) {
        if (var_r31->hsfData == 0) {
            break;
        }
    }
    if (var_r29 == 0x200) {
        return -1;
    }
    var_r31->hsfData = arg0;
    var_r31->unk_48 = (HsfData *)(var_r29 + 0x2710);
    var_r31->attr = 0x10;
    var_r31->motion_attr = 0;
    var_r31->pos.x = var_r31->pos.y = var_r31->pos.z = 0.0f;
    var_r31->rot.x = var_r31->rot.y = var_r31->rot.z = 0.0f;
    var_r31->scale.x = var_r31->scale.y = var_r31->scale.z = 1.0f;
    var_r31->unk_08 = var_r31->unk_0C = var_r31->unk_0A = var_r31->unk_0E = -1;
    
    for (i = 0; i < 4; i++) {
        var_r31->unk_10[i] = -1;
    }
    var_r31->unk_64 = 0.0f;
    var_r31->unk_68.x = 1.0f;
    var_r31->unk_20 = -1;
    var_r31->camera = -1;
    var_r31->layer = 0;
    var_r31->unk_120 = 0;
    var_r31->unk_26 = 0;
    var_r31->unk_03 = 0;
    var_r31->unk_24 = -1;
    var_r31->unk_02 = 0;
    var_r31->unk_04 = -1;
    
    for (i = 0; i < 8; i++) {
        var_r31->unk_38[i] = -1;
    }
    var_r31->unk_01 = 0;
    PSMTXIdentity(var_r31->unk_F0);
    layerNum[0] += 1;
    return var_r29;
}

void Hu3DModelKill(s16 arg0) {
    HsfData* var_r28;
    ModelData* temp_r31;
    ModelData* var_r30;
    ParticleData *copy;
    s16 var_r27;
    s16 i;

    temp_r31 = &Hu3DData[arg0];
    var_r28 = temp_r31->hsfData;
    if (var_r28 != 0) {
        if ((temp_r31->attr & 4) != 0) {
            Hu3DShadowCamBit -= 1;
        }
        layerNum[temp_r31->layer] -= 1;

        if ((temp_r31->attr & 0x10) != 0) {
            HuMemDirectFreeNum(HEAP_DATA, (u32) temp_r31->unk_48);
            if ((temp_r31->attr & 0x20) != 0) {
                copy = temp_r31->unk_120;
                HuSprAnimKill(copy->unk_44);
            }
            temp_r31->hsfData = NULL;
            if (modelKillAllF == 0) {
                HuMemDCFlush(HEAP_DATA);
            }
            return;
        }
        if ((temp_r31->attr & 0x10000) != 0) {
            if (temp_r31->unk_08 != -1) {
                Hu3DMotionKill(temp_r31->unk_08);
            }
            HuMemDirectFreeNum(HEAP_DATA, (u32) temp_r31->unk_48);
            temp_r31->hsfData = NULL;
            return;
        }
        Hu3DAnimModelKill(arg0);
        if (temp_r31->unk_24 != -1) {
            HuMemDirectFree(temp_r31->hsfData);
            HuMemDirectFreeNum(HEAP_DATA, (u32) temp_r31->unk_4C);
            var_r28 = temp_r31->unk_C8;
            temp_r31->hsfData = var_r28;
        }
        var_r30 = Hu3DData;
        for (var_r27 = i = 0; i < 0x200; i++, var_r30++) {
            if ((var_r30->hsfData != 0) && (var_r30->hsfData == var_r28 || (var_r30->unk_24 != -1 && var_r30->unk_C8 == var_r28))) {
                var_r27++;
            }
        }
        if (var_r27 > 1) {
            temp_r31->hsfData = NULL;
            var_r30 = Hu3DData;
            if (temp_r31->unk_20 != -1) {
                for (i = 0; i < 0x200; i++, var_r30++) {
                    if (var_r30->hsfData != 0 && var_r30->unk_24 != -1 && var_r30->unk_C8 == var_r28) {
                        Hu3DMotion[temp_r31->unk_20].unk_02 = i;
                        break;
                    }
                }
            }
            if (modelKillAllF == 0) {
                HuMemDCFlush(HEAP_DATA);
            }
            return;
        }
        if (temp_r31->unk_20 != -1 && Hu3DMotionKill(temp_r31->unk_20) == 0) {
            Hu3DMotion[temp_r31->unk_20].unk_02 = -1;
            HuMemDirectFreeNum(HEAP_DATA, (u32) temp_r31->unk_48);
            temp_r31->hsfData = NULL;
            if (modelKillAllF == 0) {
                HuMemDCFlush(HEAP_DATA);
            }
            return;
        }
        HuMemDirectFree(temp_r31->hsfData);
        HuMemDirectFreeNum(HEAP_DATA, (u32) temp_r31->unk_48);
        for (i = 0; i < temp_r31->unk_26; i++) {
            Hu3DGLightKill(temp_r31->unk_28[i]);
        }
        for (i = 0; i < 8; i++) {
            if (temp_r31->unk_38[i] != -1) {
                Hu3DLLightKill(arg0, i);
            }
        }
        temp_r31->hsfData = NULL;
        if (modelKillAllF == 0) {
            HuMemDCFlush(HEAP_DATA);
        }
    }
}

void Hu3DModelAllKill(void) {
    ModelData* var_r30;
    s16 i;

    modelKillAllF = 1;
    var_r30 = Hu3DData;
    
    for (i = 0; i < 0x200; i++, var_r30++) {
        if (var_r30->hsfData != 0) {
            Hu3DModelKill(i);
        }
    }
    modelKillAllF = 0;
    
    for (i = 0; i < 8; i++) {
        layerNum[i] = 0;
        layerHook[i] = NULL;
    }
    Hu3DParManAllKill();
    HuMemDCFlush(HEAP_DATA);
}

void Hu3DModelPosSet(s16 index, f32 x, f32 y, f32 z) {
    ModelData* temp_r31;

    temp_r31 = &Hu3DData[index];
    temp_r31->pos.x = x;
    temp_r31->pos.y = y;
    temp_r31->pos.z = z;
}

void Hu3DModelPosSetV(s16 arg0, Vec arg1) {
    ModelData* temp_r31;

    temp_r31 = &Hu3DData[arg0];
    temp_r31->pos = arg1;
}

void Hu3DModelRotSet(s16 index, f32 x, f32 y, f32 z) {
    ModelData* temp_r31;

    temp_r31 = &Hu3DData[index];
    temp_r31->rot.x = x;
    temp_r31->rot.y = y;
    temp_r31->rot.z = z;
}

void Hu3DModelRotSetV(s16 arg0, Vec arg1) {
    ModelData* temp_r31;

    temp_r31 = &Hu3DData[arg0];
    temp_r31->rot = arg1;
}

void Hu3DModelScaleSet(s16 index, f32 x, f32 y, f32 z) {
    ModelData* temp_r31;

    temp_r31 = &Hu3DData[index];
    temp_r31->scale.x = x;
    temp_r31->scale.y = y;
    temp_r31->scale.z = z;
}

void Hu3DModelScaleSetV(s16 arg0, Vec arg1) {
    ModelData* temp_r31;

    temp_r31 = &Hu3DData[arg0];
    temp_r31->scale = arg1;
}

void Hu3DModelAttrSet(s16 arg0, u32 arg1) {
    ModelData* temp_r31;

    temp_r31 = &Hu3DData[arg0];
    if ((arg1 & (1 << 30)) != 0) {
        temp_r31->motion_attr |= arg1 & 0xBFFFFFFF;
    } else {
        temp_r31->attr |= arg1;
    }
}

void Hu3DModelAttrReset(s16 arg0, u32 arg1) {
    ModelData* temp_r31;

    temp_r31 = &Hu3DData[arg0];
    if ((arg1 & (1 << 30)) != 0) {
        temp_r31->motion_attr &= ~arg1;
    } else {
        temp_r31->attr &= ~arg1;
    }
}

u32 Hu3DModelAttrGet(s16 arg0) {
    ModelData *copy = &Hu3DData[arg0];
    return copy->attr;
}

u32 Hu3DModelMotionAttrGet(s16 arg0) {
    ModelData *copy = &Hu3DData[arg0];
    return copy->motion_attr;
}

void Hu3DModelClusterAttrSet(s16 arg0, s16 arg1, s32 arg2) {
    ModelData* temp_r31;
    s32 temp_r6;

    temp_r31 = &Hu3DData[arg0];
    temp_r31->cluster_attr[arg1] |= arg2;
}

void Hu3DModelClusterAttrReset(s16 arg0, s16 arg1, s32 arg2) {
    ModelData* temp_r31;

    temp_r31 = &Hu3DData[arg0];
    temp_r31->cluster_attr[arg1] &= ~arg2;
}

void Hu3DModelCameraSet(s16 arg0, u16 arg1) {
    ModelData* copy = &Hu3DData[arg0];
    copy->camera = arg1;
}

void Hu3DModelLayerSet(s16 arg0, s16 arg1) {
    ModelData* temp_r31;

    temp_r31 = &Hu3DData[arg0];
    layerNum[temp_r31->layer] -= 1;
    temp_r31->layer = arg1;
    layerNum[arg1] += 1;
}

HsfObject* Hu3DModelObjPtrGet(s16 arg0, s32 arg1) {
    char name[0x100];
    s32 spC;
    s16 sp8;
    HsfData* temp_r31;
    s16 var_r30;
    HsfObject* var_r29;
    HsfObject* var_r28;
    u32 var_r4;

    temp_r31 = Hu3DData[arg0].hsfData;
    var_r29 = temp_r31->object;
    strcpy(&name, MakeObjectName(arg1));
    
    for (var_r30 = 0; var_r30 < temp_r31->objectCnt; var_r29++, var_r30++) {
        var_r28 = var_r29;
        if (strcmp(&name, var_r28->name) == 0) {
            return var_r29;
        }
    }
    if (var_r30 == temp_r31->objectCnt) {
        OSReport("Error: OBJPtr Error!\n");
    }
    return NULL;
}

static inline void inlineFunc(HsfObject* var_r26, u32 a) {
    HsfConstData* temp_r25;
    HsfObject* copy = var_r26;
    if (copy->type == HSF_OBJ_MESH) {
        temp_r25 = copy->constData;
        temp_r25->flags |= a;
    } 
}

void Hu3DModelTPLvlSet(s16 arg0, f32 arg8) {
    HsfMaterial* var_r31;
    HsfData* temp_r30;
    s16 i;
    ModelData* temp_r28;
    HsfObject* var_r27;
    HsfObject* var_r26;
    HsfConstData* temp_r25;

    temp_r28 = &Hu3DData[arg0];
    temp_r30 = temp_r28->hsfData;
    var_r31 = temp_r30->material;
    for (i = 0; i < temp_r30->materialCnt; i++, var_r31++) {
        var_r31->invAlpha = 1.0f - arg8;
        if (1.0f != arg8) {
            var_r31->pass = (var_r31->pass & 0xF0) | 1;
        } else {
            var_r31->pass &= 0xF0;
        }
    }
    var_r26 = temp_r30->object;
    for (i = 0; i < temp_r30->objectCnt; var_r26++, i++) {
        var_r27 = var_r26;
        if (var_r27->type == 2) {
            temp_r25 = var_r27->constData;
            temp_r25->flags |= 1;
        } 
    }
    temp_r28->attr |= 0x40000;
}

void Hu3DModelHiliteMapSet(s16 arg0, AnimData *arg1) {
    HsfObject* copy;
    ModelData* temp_r30;
    HsfData* temp_r29;
    s16 i;
    HsfObject* var_r27;
    HsfConstData* temp_r25;

    temp_r30 = &Hu3DData[arg0];
    temp_r29 = temp_r30->hsfData;
    var_r27 = temp_r29->object;
    for (i = 0; i < temp_r29->objectCnt; var_r27++, i++) {
        copy = var_r27;
        if (copy->type == HSF_OBJ_MESH) {
            copy->flags |= 0x100;
            temp_r25 = copy->constData;
            temp_r25->flags |= 0x8000;
            temp_r25->hilite_map = arg1;
        } 
    }
}

static inline void constDataFlagSet(HsfObject* var_r26, u32 a) {
    HsfConstData* temp_r25;
    HsfObject* copy = var_r26;
    if (copy->constData != 0) {
        temp_r25 = copy->constData;
        temp_r25->flags |= a;
    } 
}

static inline void constDataFlagReset(HsfObject* var_r26, u32 a) {
    HsfConstData* temp_r25;
    HsfObject* copy = var_r26;
    if (copy->constData != 0) {
        temp_r25 = copy->constData;
        temp_r25->flags &= ~a;
    } 
}

void Hu3DModelShadowSet(s16 arg0) {
    HsfConstData* temp_r26;
    HsfData* temp_r30;
    HsfConstData* temp_r25;
    HsfObject* copy;
    s16 var_r28;
    HsfObject* var_r27;
    ModelData* temp_r31;

    temp_r31 = &Hu3DData[arg0];
    temp_r30 = temp_r31->hsfData;
    if ((temp_r31->attr & 4) == 0) {
        Hu3DShadowCamBit++;
    }
    temp_r31->attr |= 4;
    var_r27 = temp_r30->object;
    
    for (var_r28 = 0; var_r28 < temp_r30->objectCnt; var_r28++, var_r27++) {
        constDataFlagSet(var_r27, 0x400);
    }
}

void Hu3DModelShadowReset(s16 arg0) {
    s16 var_r28;
    HsfObject* var_r27;
    HsfConstData* temp_r26;
    ModelData* temp_r31;
    HsfData* temp_r30;
    HsfObject* copy;

    temp_r31 = &Hu3DData[(s16) arg0];
    temp_r30 = temp_r31->hsfData;
    temp_r31->attr &= ~4;
    Hu3DShadowCamBit -= 1;
    var_r27 = temp_r30->object;
    for (var_r28 = 0; var_r28 < temp_r30->objectCnt; var_r28++, var_r27++) {
        constDataFlagReset(var_r27, 0x400);
    }
}

void Hu3DModelShadowDispOn(s16 arg0) {
    ModelData* temp_r31;

    temp_r31 = &Hu3DData[arg0];
    temp_r31->attr |= 4;
}

void Hu3DModelShadowDispOff(s16 arg0) {
    ModelData* temp_r31;

    temp_r31 = &Hu3DData[arg0];
    temp_r31->attr &= ~4;
}

void Hu3DModelShadowMapSet(s16 arg0) {
    HsfConstData* temp_r27;
    HsfData* temp_r31;
    s16 i;
    HsfObject* var_r28;
    HsfObject* copy;

    temp_r31 = Hu3DData[arg0].hsfData;
    var_r28 = temp_r31->object;
    for (i = 0; i < temp_r31->objectCnt; i++, var_r28++) {
        constDataFlagSet(var_r28, 8);
    }
}

void Hu3DModelShadowMapObjSet(s16 arg0, s32 arg1) {
    char name[0x100];
    HsfData* temp_r30;
    s16 i;
    HsfObject* var_r28;
    HsfObject* copy;
    HsfConstData* temp_r27;

    temp_r30 = Hu3DData[arg0].hsfData;
    var_r28 = temp_r30->object;
    strcpy(&name, MakeObjectName(arg1));
    
    for (i = 0; i < temp_r30->objectCnt; i++, var_r28++) {
        copy = var_r28;
        if (copy->constData != 0x0 && strcmp(&name, copy->name) == 0) {
            temp_r27 = copy->constData;
            temp_r27->flags |= 8;
            break;
        }
    }
}

void Hu3DModelAmbSet(s16 arg0, f32 arg8, f32 arg9, f32 argA) {
    ModelData* temp_r31;

    temp_r31 = &Hu3DData[arg0];
    temp_r31->unk_58.x = arg8;
    temp_r31->unk_58.z = arg9;
    temp_r31->unk_58.y = argA;
}

void Hu3DModelHookSet(s16 arg0, s32 arg1, s16 arg2) {
    char name[0x100];
    ModelData* data;
    HsfData* temp_r30;
    s16 i;
    HsfConstData *constData;
    HsfObject* copy;
    HsfObject* var_r27;

    temp_r30 = Hu3DData[arg0].hsfData;
    var_r27 = temp_r30->object;
    strcpy(&name, MakeObjectName(arg1));
    
    for (i = 0; i < temp_r30->objectCnt; i++, var_r27++) {
        copy = var_r27;
        if (copy->constData != 0) {
            if (strcmp(&name, copy->name) == 0) {
                constData = copy->constData;
                constData->hook = arg2;
                data = &Hu3DData[arg2];
                data->attr |= 0x8000;
                return;
            } else {
                (void)data;
            }
        }
    }
    OSReport("Error: Not Found %s for HookSet\n", arg1);
}

void Hu3DModelHookReset(s16 arg0) {
    HsfConstData* temp_r31;
    HsfData* temp_r30;
    HsfObject* copy;
    ModelData* temp_r28;
    s16 var_r27;
    HsfObject* var_r26;
    s16 temp_r0;

    temp_r30 = Hu3DData[arg0].hsfData;
    var_r26 = temp_r30->object;
    for (var_r27 = 0; var_r27 < temp_r30->objectCnt; var_r27++, var_r26++) {
        copy = var_r26;
        if (copy->constData != 0) {
            temp_r31 = copy->constData;
            if (temp_r31->hook != -1) {
                temp_r0 = temp_r31->hook;
                temp_r28 = &Hu3DData[temp_r0];
                temp_r28->attr &= ~0x8000;
                temp_r31->hook = -1;
                (void)temp_r28;
            }
        }
    }
}

void Hu3DModelHookObjReset(s16 arg0, s32 arg1) {
    char name[0x100];
    ModelData* temp_r28;
    HsfData* temp_r30;
    HsfObject* copy;
    HsfConstData* temp_r29;
    s16 i;
    HsfObject* var_r26;
    s16 temp_r0;

    temp_r30 = Hu3DData[arg0].hsfData;
    var_r26 = temp_r30->object;
    strcpy(&name, MakeObjectName(arg1));
    
    for (i = 0; i < temp_r30->objectCnt; i++, var_r26++) {
        copy = var_r26;
        if (copy->constData != 0) {
            if (strcmp(&name, copy->name) == 0) {
                temp_r29 = copy->constData;
                temp_r0 = temp_r29->hook;
                temp_r28 = &Hu3DData[temp_r0];
                temp_r28->attr &= ~0x8000;
                temp_r29->hook = -1;
                (void)temp_r28;
                return;
            }
        }
    }
    
    OSReport("Error: Not Found %s for HookReset\n", arg1);
}

void Hu3DModelProjectionSet(s16 arg0, s16 arg1) {
    ModelData* temp_r31;

    temp_r31 = &Hu3DData[arg0];
    temp_r31->unk_02 = temp_r31->unk_02 | (1 << arg1);
}

void Hu3DModelProjectionReset(s16 arg0, s16 arg1) {
    ModelData* temp_r31;

    temp_r31 = &Hu3DData[arg0];
    temp_r31->unk_02 &= ~(1 << arg1);
}

void Hu3DModelHiliteTypeSet(s16 arg0, s16 arg1) {
    HsfData* temp_r30;
    HsfMaterial* var_r31;
    ModelData* temp_r29;
    ModelData* temp_r5;
    s16 i;
    s32 temp;

    temp_r5 = &Hu3DData[arg0];
    temp_r30 = temp_r5->hsfData;
    var_r31 = temp_r30->material;

    arg1 = ((s16) arg1) * 0x10;
    arg1 &= 0xF0;
    for (i = 0; i < temp_r30->materialCnt; i++, var_r31++) {
        var_r31->pass = var_r31->pass & 0xF | arg1;
        var_r31->flags |= 0x100;
    }
    temp_r29 = &Hu3DData[arg0];
    temp_r29->attr |= 0x20000;
    (void)temp_r29;
}

void Hu3DModelReflectTypeSet(s16 arg0, s16 arg1) {
    ModelData *copy = &Hu3DData[arg0];
    copy->unk_04 = arg1;
}

CameraData defCamera = {
    45.0f,
    20.0f,
    5000.0f,
    0.0f,
    1.2f,
    {0.0f, 0.0f, 100.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    0, 0, 640, 480,
    0.0f, 0.0f, 640.0f, 480.0f,
    0.0f, 1.0f
};

void Hu3DCameraCreate(s32 cam) {
    s16 mask;
    s16 i;
    CameraData* cam_ptr;

    defCamera.viewport_w = RenderMode->fbWidth;
    defCamera.viewport_h = RenderMode->efbHeight;
    defCamera.scissor_w = RenderMode->fbWidth;
    defCamera.scissor_h = RenderMode->efbHeight;
    Hu3DCameraExistF |= cam;
    
    for (i = 0, mask = 1; i < 0x10; i++, mask <<= 1) {
        if ((cam & mask) != 0) {
            cam_ptr = &Hu3DCamera[i];
            *cam_ptr = defCamera;
        }
    }
}

void Hu3DCameraPerspectiveSet(s32 cam, f32 fov, f32 near, f32 far, f32 aspect) {
    s16 mask;
    s16 i;
    CameraData* cam_ptr;

    for (i = 0, mask = 1; i < 0x10; i++, mask <<= 1) {
        if ((cam & mask) != 0) {
            cam_ptr = &Hu3DCamera[i];
            cam_ptr->fov = fov;
            cam_ptr->near = near;
            cam_ptr->far = far;
            cam_ptr->aspect = aspect;
        }
    }
}

void Hu3DCameraViewportSet(s32 cam, f32 vx, f32 vy, f32 vw, f32 vh, f32 nz, f32 fz) {
    s16 mask;
    s16 i;
    CameraData* cam_ptr;

    for (i = 0, mask = 1; i < 0x10; i++, mask <<= 1) {
        if ((cam & mask) != 0) {
            cam_ptr = &Hu3DCamera[i];
            cam_ptr->viewport_x = vx;
            cam_ptr->viewport_y = vy;
            cam_ptr->viewport_w = vw;
            cam_ptr->viewport_h = vh;
            cam_ptr->near_z = nz;
            cam_ptr->far_z = fz;
        }
    }
}

void Hu3DCameraScissorSet(s32 cam, s32 x, s32 y, s32 w, s32 h) {
    s16 mask;
    s16 i;
    CameraData* cam_ptr;

    for (i = 0, mask = 1; i < 0x10; i++, mask <<= 1) {
        if ((cam & mask) != 0) {
            cam_ptr = &Hu3DCamera[i];
            cam_ptr->scissor_x = x;
            cam_ptr->scissor_y = y;
            cam_ptr->scissor_w = w;
            cam_ptr->scissor_h = h;
        }
    }
}

void Hu3DCameraPosSet(s32 cam, f32 x, f32 y, f32 z, f32 ux, f32 uy, f32 uz, f32 tx, f32 ty, f32 tz) {
    s16 mask;
    s16 i;
    CameraData* cam_ptr;

    for (i = 0, mask = 1; i < 0x10; i++, mask <<= 1) {
        if ((cam & mask) != 0) {
            cam_ptr = &Hu3DCamera[i];
            cam_ptr->pos.x = x;
            cam_ptr->pos.y = y;
            cam_ptr->pos.z = z;
            cam_ptr->up.x = ux;
            cam_ptr->up.y = uy;
            cam_ptr->up.z = uz;
            cam_ptr->target.x = tx;
            cam_ptr->target.y = ty;
            cam_ptr->target.z = tz;
        }
    }
}

void Hu3DCameraPosSetV(s32 cam, Vec pos, Vec up, Vec target) {
    s16 mask;
    s16 i;
    CameraData* cam_ptr;

    for (i = 0, mask = 1; i < 0x10; i++, mask <<= 1) {
        if ((cam & mask) != 0) {
            cam_ptr = &Hu3DCamera[i];
            cam_ptr->pos = pos;
            cam_ptr->up = up;
            cam_ptr->target = target;
        }
    }
}

void Hu3DCameraKill(s32 cam) {
    s16 mask;
    s16 i;
    CameraData* cam_ptr;

    for (i = 0, mask = 1; i < 0x10; i++, mask <<= 1) {
        if ((cam & mask) != 0) {
            cam_ptr = &Hu3DCamera[i];
            cam_ptr->fov = -1.0f;
        }
    }
}

void Hu3DCameraAllKill(void) {
    CameraData* cam_ptr;
    CameraData* cam_ptr2;
    s16 i;
    s16 mask;
    s16 j;
    s16 mask2;

    cam_ptr = &Hu3DCamera[0];
    for (i = 0, mask = 1; i < 0x10; i++, mask <<= 1, cam_ptr++) {
        if (-1.0f != cam_ptr->fov) {
           for (j = 0, mask2 = 1; j < 0x10; j++, mask2 <<= 1) {
                if ((mask & mask2) != 0) {
                    cam_ptr2 = &Hu3DCamera[j];
                    cam_ptr2->fov = -1.0f;
                }
            }
        }
    }
    Hu3DCameraExistF = 0;
}

void Hu3DCameraSet(s32 arg0, Mtx arg1) {
    Mtx44 sp10;
    Mtx44 spC;
    CameraData* temp_r31;

    temp_r31 = &Hu3DCamera[arg0];
    C_MTXPerspective(sp10, temp_r31->fov, temp_r31->aspect, temp_r31->near, temp_r31->far);
    GXSetProjection(sp10, GX_PERSPECTIVE);
    if (RenderMode->field_rendering != 0) {
        GXSetViewportJitter(temp_r31->viewport_x, temp_r31->viewport_y, temp_r31->viewport_w, temp_r31->viewport_h, temp_r31->near_z, temp_r31->far_z, VIGetNextField());
    } else {
        GXSetViewport(temp_r31->viewport_x, temp_r31->viewport_y, temp_r31->viewport_w, temp_r31->viewport_h, temp_r31->near_z, temp_r31->far_z);
    }
    GXSetScissor(temp_r31->scissor_x, temp_r31->scissor_y, temp_r31->scissor_w, temp_r31->scissor_h);
    C_MTXLookAt(arg1, &temp_r31->pos, &temp_r31->up, &temp_r31->target);
}

BOOL Hu3DModelCameraInfoSet(s16 arg0, u16 arg1) {
    CameraData* cam;
    CameraData* temp_r30;
    CameraData* temp_r29;
    HsfObject* obj_copy;
    ModelData* temp_r24;
    ModelData* temp_r28;
    HsfObject* var_r23;
    HsfData* temp_r27;
    Point3d sp14;
    Point3d sp8;
    f32 temp_f31;
    s16 i;
    s16 var_r25;
    s16 var_r26;
    s16 var_r21;
    s16 var_r20;

    temp_r28 = &Hu3DData[arg0];
    temp_r27 = temp_r28->hsfData;
    cam = &Hu3DCamera[arg1];
    var_r23 = temp_r27->object;
    
    for (i = 0; i < temp_r27->objectCnt; i++, var_r23++) {
        obj_copy = var_r23;
        if (obj_copy->type == 7) {
            temp_f31 = obj_copy->data.base.rot.x;
            cam->aspect_dupe = temp_f31;
            
            PSVECSubtract((Point3d* ) &obj_copy->camera.target, (Point3d* ) &obj_copy->camera.pos, &sp8);
            
            sp14.x = ((sp8.x * sp8.y * (1.0 - cos((M_PI * temp_f31) / 180.0))) - (sp8.z * sin((M_PI * temp_f31) / 180.0)));
            sp14.y = ((sp8.y * sp8.y) + (1.0f - (sp8.y * sp8.y)) * cos((M_PI * temp_f31) / 180.0));
            sp14.z = (((sp8.y * sp8.z) * (1.0 - cos((M_PI * (f64) temp_f31) / 180.0))) + (sp8.x * sin((M_PI * temp_f31) / 180.0)));
            PSVECNormalize(&sp14, &sp8);

            Hu3DCameraPosSet(arg1, obj_copy->camera.target.x, obj_copy->camera.target.y, obj_copy->camera.target.z,
                             sp8.x, sp8.y, sp8.z, 
                             obj_copy->camera.pos.x, obj_copy->camera.pos.y, obj_copy->camera.pos.z);
            
            Hu3DCameraPerspectiveSet(arg1, obj_copy->camera.fov, obj_copy->camera.near, obj_copy->camera.far, 1.2f);
            
            temp_r28->unk_01 = arg1;
            temp_r24 = &Hu3DData[arg0];
            temp_r24->attr |= 0x2000;
            (void)temp_r24;
            return 1;
        }
    }
    return 0;
}

s16 Hu3DModelCameraCreate(s16 arg0, u16 arg1) {
    ModelData* temp_r31;
    s16 temp_r3;

    temp_r3 = Hu3DHookFuncCreate((HsfData* )-1);
    temp_r31 = &Hu3DData[(s16) temp_r3];
    temp_r31->attr &= ~0x10;
    temp_r31->attr |= 0x10000 | 0x2000;
    temp_r31->unk_08 = arg0;
    temp_r31->unk_01 = arg1;
    return temp_r3;
}

void Hu3DCameraMotionOn(s16 arg0, s8 arg1) {
    ModelData* copy;
    ModelData* copy2;

    copy2 = &Hu3DData[arg0];
    copy2->unk_01 = arg1;
    copy = &Hu3DData[arg0];
    copy->attr |= 0x2000;
}

void Hu3DCameraMotionStart(s16 arg0, u16 arg1) {
    ModelData* temp_r30;
    ModelData* temp_r29;
    ModelData* temp_r28;
    ModelData* temp_r27;

    temp_r28 = &Hu3DData[arg0];
    temp_r27 = &Hu3DData[arg0];
    temp_r27->unk_01 = arg1;
    temp_r29 = &Hu3DData[arg0];
    temp_r29->attr |= 0x2000;
    temp_r30 = &Hu3DData[arg0];
    temp_r30->motion_attr &= ~0x40000002;
    Hu3DMotionStartEndSet(arg0, 0.0f, Hu3DMotionMotionMaxTimeGet(temp_r28->unk_08));
    Hu3DMotionTimeSet(arg0, 0.0f);
}

void Hu3DCameraMotionOff(s16 arg0) {
    ModelData* temp_r31;

    temp_r31 = &Hu3DData[arg0];
    temp_r31->attr &= ~0x2000;
}

void Hu3DLighInit(void) {
    LightData* var_r31;
    s16 var_r30;

    var_r31 = Hu3DGlobalLight;
    for (var_r30 = 0; var_r30 < 8; var_r30++, var_r31++) {
        var_r31->unk_00 = -1;
    }
    var_r31 = Hu3DLocalLight;
    for (var_r30 = 0; var_r30 < 0x20; var_r30++, var_r31++) {
        var_r31->unk_00 = -1;
    }
}

void Hu3DGLightCreate(f32 arg8, f32 arg9, f32 argA, f32 argB, f32 argC, f32 argD, u8 arg0, u8 arg1, u8 arg2) {
    Vec vec1;
    Vec vec2;
    GXColor color;

    vec1.x = arg8;
    vec1.y = arg9;
    vec1.z = argA;
    vec2.x = argB;
    vec2.y = argC;
    vec2.z = argD;
    color.r = arg0;
    color.g = arg1;
    color.b = arg2;
    color.a = 0xFF;
    Hu3DGLightCreateV(&vec1, &vec2, &color);
}

s16 Hu3DGLightCreateV(Vec* arg0, Vec* arg1, GXColor* arg2) {
    s16 var_r30;
    LightData* var_r31;

    var_r31 = Hu3DGlobalLight;
    
    for (var_r30 = 0; var_r30 < 8; var_r30++, var_r31++) {
        if (var_r31->unk_00 == -1) {
            break;
        }
    }
    if (var_r30 == 8) {
        return -1;
    }
    var_r31->unk_00 = 0;
    var_r31->unk_1C = *arg0;
    var_r31->unk_28 = *arg1;
    var_r31->unk_34.x = var_r31->unk_34.y = var_r31->unk_34.z = 0.0f;
    var_r31->unk_04 = 0.0f;
    var_r31->unk_02 = 2;
    
    PSVECNormalize(&var_r31->unk_28, &var_r31->unk_28);
    var_r31->color = *arg2;
    return var_r30;
}

void Hu3DLLightCreate(s16 arg0, f32 arg8, f32 arg9, f32 argA, f32 argB, f32 argC, f32 argD, u8 arg1, u8 arg2, u8 arg3) {
    Vec vec1;
    Vec vec2;
    GXColor color;

    vec1.x = arg8;
    vec1.y = arg9;
    vec1.z = argA;
    vec2.x = argB;
    vec2.y = argC;
    vec2.z = argD;
    color.r = arg1;
    color.g = arg2;
    color.b = arg3;
    color.a = 0xFF;
    Hu3DLLightCreateV(arg0, &vec1, &vec2, &color);
}

s16 Hu3DLLightCreateV(s16 arg0, Vec* arg1, Vec* arg2, GXColor* arg3) {
    ModelData* temp_r29;
    s16 var_r28;
    s16 var_r30;
    LightData* var_r31;

    temp_r29 = &Hu3DData[arg0];
    var_r31 = Hu3DLocalLight;
    for (var_r28 = 0; var_r28 < 0x20; var_r28++, var_r31++) {
        if (var_r31->unk_00 == -1) {
            break;
        }
    }
    if (var_r28 == 0x20) {
        return -1;
    }
    var_r31->unk_00 = 0;
    var_r31->unk_1C = *arg1;
    var_r31->unk_28 = *arg2;
    var_r31->unk_34.x = var_r31->unk_34.y = var_r31->unk_34.z = 0.0f;
    var_r31->unk_04 = 30.0f;
    var_r31->unk_02 = 2;
    PSVECNormalize(&var_r31->unk_28, &var_r31->unk_28);
    var_r31->color = *arg3;
    
    for (var_r30 = 0; var_r30 < 8; var_r30++) {
        if (temp_r29->unk_38[var_r30] == -1) {
            break;
        }
    }
    if (var_r30 == 8) {
        return -1;
    }
    temp_r29->unk_38[var_r30] = var_r28;
    temp_r29->attr |= 0x1000;
    return var_r30;
}

void Hu3DGLightSpotSet(s16 arg0, u16 arg1, f32 arg8) {
    LightData* temp_r31;

    temp_r31 = &Hu3DGlobalLight[arg0];
    temp_r31->unk_00 &= 0xFF00;
    temp_r31->unk_04 = arg8;
    temp_r31->unk_02 = arg1;
}

void Hu3DLLightSpotSet(s16 arg0, s16 arg1, u16 arg2, f32 arg8) {
    ModelData* data;
    LightData* temp_r31;

    data = &Hu3DData[arg0];
    temp_r31 = &Hu3DLocalLight[data->unk_38[arg1]];
    temp_r31->unk_00 &= 0xFF00;
    temp_r31->unk_04 = arg8;
    temp_r31->unk_02 = arg2;
}

// ...

void Hu3DShadowSizeSet(u16 arg0) {
    Hu3DShadowData.unk_02 = arg0;
    if (Hu3DShadowData.unk_04 != 0) {
        HuMemDirectFree(Hu3DShadowData.unk_04);
    }
    Hu3DShadowData.unk_04 = HuMemDirectMalloc(HEAP_DATA, arg0 * arg0);
}

s16 Hu3DProjectionCreate(void *arg0, f32 arg8, f32 arg9, f32 argA) {
    s16 var_r30;
    ThreeDProjectionStruct* var_r31;

    var_r31 = Hu3DProjection;
    
    for (var_r30 = 0; var_r30 < 4; var_r30++, var_r31++) {
        if (var_r31->unk_04 == 0U) {
            break;
        }
    }
    if ((s16) var_r30 == 4) {
        return -1;
    }
    var_r31->unk_04 = arg0;
    var_r31->unk_08.x = arg8;
    var_r31->unk_08.y = arg9;
    var_r31->unk_08.z = argA;
    var_r31->unk_14.x = 1000.0f;
    var_r31->unk_14.y = 1000.0f;
    var_r31->unk_14.z = 0.0f;
    var_r31->unk_20.x = var_r31->unk_20.y = var_r31->unk_20.z = 0.0f;
    var_r31->unk_2C.x = -1.0f;
    var_r31->unk_2C.y = 1.0f;
    var_r31->unk_2C.z = 0.0f;
    C_MTXLightPerspective(var_r31->unk_68, arg8, 1.2f, 0.5f, 20.0f, 0.5f, 0.5f);
    PSVECNormalize(&var_r31->unk_2C, &var_r31->unk_2C);
    var_r31->unk_00 = 0x80;
    Hu3DProjectionNum++;
    return var_r30;
}

void Hu3DProjectionKill(s16 arg0) {
    HuSprAnimKill(Hu3DProjection[arg0].unk_04);
    Hu3DProjection[arg0].unk_04 = NULL;
}

void Hu3DProjectionPosSet(s16 arg0, Vec arg1, Vec arg2, Vec arg3) {
    Hu3DProjection[arg0].unk_14 = arg1;
    Hu3DProjection[arg0].unk_20 = arg3;
    Hu3DProjection[arg0].unk_2C = arg2;
}

void Hu3DProjectionTPLvlSet(s16 arg0, f32 arg8) {
    Hu3DProjection[arg0].unk_00 = 255.0f * arg8;
}

void Hu3DMipMapSet(char* arg0, s16 arg1, s32 arg2, f32 arg8) {
    HsfBitmap* temp_r31;
    AnimBmpData* var_r30;
    s16 i;
    HsfData* temp_r27;
    HsfAttribute* var_r26;
    ModelData* temp_r25;
    s32 var_r24;
    void *var_r23;
    void* temp_r22;
    AnimData* temp_r3;

    temp_r25 = &Hu3DData[arg1];
    temp_r27 = temp_r25->hsfData;
    var_r26 = temp_r27->attribute;
    for (i = 0; i < temp_r27->attributeCnt; i++, var_r26++) {
        if (strcmp(arg2, var_r26->bitmap->name) == 0) {
            break;
        }
    }
    if (i == temp_r27->attributeCnt) {
        OSReport("Error: Not Found %s for MipMapSet\n", arg2);
        return;
    }
    temp_r31 = var_r26->bitmap;
    temp_r3 = HuSprAnimRead(arg0);
    var_r30 = temp_r3->bmp;
    for ( i = 0, var_r24 = i; i < temp_r3->bmpNum; i++, var_r30++) {
        var_r24 += var_r30->dataSize;
    }
    var_r23 = HuMemDirectMallocNum(HEAP_DATA, var_r24, (u32)temp_r25->unk_48);
    temp_r22 = var_r23;
    var_r30 = temp_r3->bmp;
    temp_r31->data = temp_r22;
    temp_r31->sizeX = var_r30->sizeX;
    temp_r31->sizeY = var_r30->sizeY;
    temp_r31->palSize = var_r30->palNum;
    temp_r31->palData = var_r30->palData;
    temp_r31->maxLod = temp_r3->bmpNum;
    switch (var_r30->dataFmt) {                        /* irregular */
        case 0:
            temp_r31->dataFmt = 6;
            break;
        case 2:
            temp_r31->dataFmt = 5;
            break;
        case 3:
            temp_r31->dataFmt = 0xA;
            temp_r31->pixSize = 8;
            break;
        case 4:
            temp_r31->dataFmt = 0xA;
            temp_r31->pixSize = 4;
            break;
    }

    for (i = 0; i < temp_r3->bmpNum; i++, var_r30++) {
        memcpy(var_r23, var_r30->data, var_r30->dataSize);
        var_r23 = (void*) ((int) var_r23 + var_r30->dataSize);
    }
    DCFlushRange(temp_r22, var_r24);
}
