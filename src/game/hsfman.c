#include "game/hsfman.h"

ModelData Hu3DData[0x200];
ThreeDCameraStruct Hu3DCamera[0x10];
s16 layerNum[8];
void (*layerHook[8])(s16);
AnimData *reflectAnim[5];
AnimData *hiliteAnim[4];
ThreeDProjectionStruct Hu3DProjection[4];
ShadowData Hu3DShadowData;
HsfScene FogData;
Mtx Hu3DCameraMtx;
LightData Hu3DGlobalLight[0x8];
Mtx Hu3DCameraMtxXPose;
LightData Hu3DLocalLight[0x20];
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
s16 Hu3DCameraExistF;
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
    ThreeDCameraStruct* camera;
    s16 i;

    data = Hu3DData;
    for (i = 0; i < 0x200; i++, data++) {
        data->hsfData = NULL;
    }
    camera = Hu3DCamera;
    for (i = 0; i < 0x10; i++, camera++) {
        camera->unk_00 = lbl_801D4AB0;
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
    u8 spB;
    u8 spA;
    u8 sp9;
    GXColor sp8;
    ModelData *var_r31;
    s16 var_r30;
    
    GXSetCopyClear(BGColor, 0xFFFFFF);
    var_r31 = &Hu3DData[0];
    for (var_r30 = 0; var_r30 < 0x200; var_r31++) {
        if (var_r31->hsfData != 0) {
            var_r31->unk_50 &= 0xFFFFF7FF;
        }
        var_r30++;
    }
    totalPolyCnted = totalPolyCnt;
    totalMatCnted = totalMatCnt;
    totalTexCnted = totalTexCnt;
    totalTexCacheCnted = totalTexCacheCnt;
    totalPolyCnt = totalMatCnt = totalTexCnt = totalTexCacheCnt = 0;
}

void Hu3DExec(void) {
    GXColor spC;
    GXColor sp8;
    ThreeDCameraStruct* var_r27;
    ModelData* var_r30;
    ModelData* var_r30_2;
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

    spC = lbl_801D6BE0;
    HuPerfBegin(3);
    GXSetCurrentMtx(0U);
    var_r27 = Hu3DCamera;
    shadowModelDrawF = 0;
    HuSprBegin();
    var_r24 = 0;
    for (Hu3DCameraNo = 0; Hu3DCameraNo < 0x10; Hu3DCameraNo++, var_r27++) {
        if (lbl_801D4AB0 != var_r27->unk_00) {
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
                GXSetFog(FogData.fogType, FogData.start, FogData.end, var_r27->start, var_r27->end, FogData.color);
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
                    var_r30 = Hu3DData;
                    for (i = 0, var_r23 = i; i < 0x200; i++, var_r30++) {
                        if (var_r30->hsfData != 0) {
                            if ((var_r30->unk_50 & 0x10000) != 0) {
                                Hu3DCameraMotionExec(i);
                            } else {
                                if ((var_r30->unk_50 & 0x2001) == 0x2001 && var_r30->unk_08 != -1) {
                                    Hu3DMotionExec(i, var_r30->unk_08, var_r30->unk_64, 0);
                                }
                                if ((var_r30->unk_50 & 9) == 0 && (var_r30->unk_22 & temp_r22) != 0 && var_r30->unk_06 == j) {
                                    if (((var_r30->unk_50 & 0x800) == 0 && (var_r30->unk_50 & 0x100) == 0) || ((var_r30->unk_50 & 0x100) != 0 && (var_r30->unk_00 & 1) != 0)) {
                                        var_r25 = 0;
                                        var_r30->unk_54 &= 0xBFFFFFFF;
                                        if (var_r30->unk_08 != -1) {
                                            Hu3DMotionExec(i, var_r30->unk_08, var_r30->unk_64, 0);
                                        }
                                        if (var_r30->unk_0C != -1) {
                                            Hu3DSubMotionExec(i);
                                        }
                                        if (var_r30->unk_0A != -1) {
                                            Hu3DMotionExec(i, var_r30->unk_0A, var_r30->unk_74, 1);
                                        }
                                        if ((var_r30->unk_50 & 0x400) != 0) {
                                            ClusterMotionExec(var_r30);
                                            var_r25 = 1;
                                        }
                                        if (var_r30->unk_0E != -1) {
                                            if (var_r30->unk_08 == -1) {
                                                Hu3DMotionExec(i, var_r30->unk_0E, var_r30->unk_94, 0);
                                            } else {
                                                Hu3DMotionExec(i, var_r30->unk_0E, var_r30->unk_94, 1);
                                            }
                                            var_r25 = 1;
                                        }
                                        if ((var_r30->unk_50 & 0x90) == 0 && (var_r30->unk_54 & 0x40000002) == 0) {
                                            var_r25 = 1;
                                            InitVtxParm(var_r30->hsfData);
                                            if (var_r30->unk_0E != -1) {
                                                ShapeProc(var_r30->hsfData);
                                            }
                                            if ((var_r30->unk_50 & 0x400) != 0) {
                                                ClusterProc(var_r30);
                                            }
                                            if (var_r30->hsfData->cenvCnt != 0) {
                                                EnvelopeProc(var_r30->hsfData);
                                            }
                                            PPCSync();
                                        }
                                        if (var_r25 != 0) {
                                            GXInvalidateVtxCache();
                                        }
                                        var_r30->unk_50 |= 0x800;
                                    }
                                    if (var_r24 != 0 && (var_r30->unk_50 & 0x10) != 0) {
                                        GXWaitDrawDone();
                                        var_r24 = 0;
                                    }
                                    if ((var_r30->unk_50 & 0x8000) == 0 && (lbl_801D4AB4 != var_r30->unk_E4 || lbl_801D4AB4 != var_r30->unk_E8 || lbl_801D4AB4 != var_r30->unk_EC)) {
                                        mtxRot(sp40, var_r30->unk_D8, var_r30->unk_DC, var_r30->unk_E0);
                                        mtxScaleCat(sp40, var_r30->unk_E4, var_r30->unk_E8, var_r30->unk_EC);
                                        mtxTransCat(sp40, var_r30->unk_CC, var_r30->unk_D0, var_r30->unk_D4);
                                        PSMTXConcat(Hu3DCameraMtx, sp40, sp10);
                                        PSMTXConcat(sp10, var_r30->unk_F0, sp10);
                                        Hu3DDraw(var_r30, sp10[0], &var_r30->unk_E4);
                                    }
                                    var_r30->unk_00++;
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
    var_r30 = Hu3DData;
    for (i = 0; i < 0x200; i++, var_r30++) {
        if (var_r30->hsfData != 0 && (var_r30->unk_08 != -1 || (var_r30->unk_50 & 0x400) != 0 || var_r30->unk_0E != -1) && (Hu3DPauseF == 0 || (var_r30->unk_50 & 0x200000) != 0)) {
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
    var_r31->unk_50 = 0;
    var_r31->unk_54 = 0;
    var_r31->unk_02 = 0;
    MakeDisplayList(var_r30, (HsfData* ) var_r31->unk_48);
    var_r31->unk_68.x = lbl_801D4AB8;
    for (i = 0; i < 4; i++) {
        var_r31->unk_10[i] = -1;
    }
    var_r31->unk_0A = -1;
    var_r31->unk_0C = -1;
    var_r31->unk_0E = -1;
    var_r31->unk_64 = lbl_801D4AB4;
    if (var_r31->hsfData->motionCnt != 0) {
        var_r31->unk_08 = var_r31->unk_20 = Hu3DMotionModelCreate(var_r30);
        if (var_r31->hsfData->cenvCnt != 0) {
            Hu3DMotionExec(var_r30, var_r31->unk_08, lbl_801D4AB4, 0);
            EnvelopeProc(var_r31->hsfData);
            PPCSync();
        }
        if (var_r31->hsfData->clusterCnt != 0) {
            Hu3DMotionClusterSet(var_r30, var_r31->unk_08);
        }
        if (var_r31->hsfData->shapeCnt != 0) {
            Hu3DMotionShapeSet(var_r30, var_r31->unk_08);
        }
        var_r31->unk_68.y = lbl_801D4AB4;
        var_r31->unk_68.z = Hu3DMotionMaxTimeGet(var_r30);
    } else {
        var_r31->unk_20 = var_r31->unk_08 = -1;
    }
    var_r31->unk_CC = var_r31->unk_D0 = var_r31->unk_D4 = lbl_801D4AB4;
    var_r31->unk_D8 = var_r31->unk_DC = var_r31->unk_E0 = lbl_801D4AB4;
    var_r31->unk_E4 = var_r31->unk_E8 = var_r31->unk_EC = lbl_801D4AB8;
    var_r31->unk_22 = -1;
    var_r31->unk_06 = 0;
    var_r31->unk_120 = 0;
    var_r31->unk_26 = 0;
    var_r31->unk_03 = 0;
    var_r31->unk_58.x = var_r31->unk_58.z = var_r31->unk_58.y = lbl_801D4AB8;
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
    if ((var_r31->hsfData->sceneCnt != 0) && ((var_r31->hsfData->scene->start != lbl_801D4AB4) || (var_r31->hsfData->scene->end != lbl_801D4AB4))) {
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
    var_r31->unk_50 = temp_r30->unk_50;
    temp_r30->unk_50 |= 0x100000;
    var_r31->unk_54 = temp_r30->unk_54;
    var_r31->unk_CC = var_r31->unk_D0 = var_r31->unk_D4 = lbl_801D4AB4;
    var_r31->unk_D8 = var_r31->unk_DC = var_r31->unk_E0 = lbl_801D4AB4;
    var_r31->unk_E4 = var_r31->unk_E8 = var_r31->unk_EC = lbl_801D4AB8;
    var_r31->unk_08 = temp_r30->unk_08;
    if (var_r31->unk_08 != -1) {
        var_r31->unk_68.y = lbl_801D4AB4;
        var_r31->unk_68.z = Hu3DMotionMaxTimeGet(var_r28);
    }
    var_r31->unk_0C = var_r31->unk_0A = var_r31->unk_0E = -1;
    for (i = 0; i < 4; i++) {
        var_r31->unk_10[i] = temp_r30->unk_10[i];
        if (var_r31->unk_10[i] != -1) {
            ClusterAdjustObject(var_r31->hsfData, Hu3DMotion[var_r31->unk_10[i]].unk_04);
            var_r31->unk_50 |= 0x400;
        }
    }
    var_r31->unk_64 = temp_r30->unk_64;
    var_r31->unk_68.x = temp_r30->unk_68.x;
    var_r31->unk_20 = temp_r30->unk_20;
    var_r31->unk_22 = -1;
    var_r31->unk_06 = 0;
    var_r31->unk_120 = 0;
    var_r31->unk_26 = 0;
    var_r31->unk_03 = 0;
    var_r31->unk_02 = 0;
    var_r31->unk_58.x = var_r31->unk_58.z = var_r31->unk_58.y = lbl_801D4AB8;
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
    var_r31->unk_50 = 0x10;
    var_r31->unk_54 = 0;
    var_r31->unk_CC = var_r31->unk_D0 = var_r31->unk_D4 = lbl_801D4AB4;
    var_r31->unk_D8 = var_r31->unk_DC = var_r31->unk_E0 = lbl_801D4AB4;
    var_r31->unk_E4 = var_r31->unk_E8 = var_r31->unk_EC = lbl_801D4AB8;
    var_r31->unk_08 = var_r31->unk_0C = var_r31->unk_0A = var_r31->unk_0E = -1;
    
    for (i = 0; i < 4; i++) {
        var_r31->unk_10[i] = -1;
    }
    var_r31->unk_64 = lbl_801D4AB4;
    var_r31->unk_68.x = lbl_801D4AB8;
    var_r31->unk_20 = -1;
    var_r31->unk_22 = -1;
    var_r31->unk_06 = 0;
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
        if ((temp_r31->unk_50 & 4) != 0) {
            Hu3DShadowCamBit -= 1;
        }
        layerNum[temp_r31->unk_06] -= 1;

        if ((temp_r31->unk_50 & 0x10) != 0) {
            HuMemDirectFreeNum(HEAP_DATA, (u32) temp_r31->unk_48);
            if ((temp_r31->unk_50 & 0x20) != 0) {
                copy = temp_r31->unk_120;
                HuSprAnimKill(copy->unk_44);
            }
            temp_r31->hsfData = NULL;
            if (modelKillAllF == 0) {
                HuMemDCFlush(HEAP_DATA);
            }
            return;
        }
        if ((temp_r31->unk_50 & 0x10000) != 0) {
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

void Hu3DShadowSizeSet(u16 arg0) {
    Hu3DShadowData.unk_02 = arg0;
    if (Hu3DShadowData.unk_04 != 0) {
        HuMemDirectFree(Hu3DShadowData.unk_04);
    }
    Hu3DShadowData.unk_04 = HuMemDirectMalloc(HEAP_DATA, arg0 * arg0);
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
    Hu3DProjection[arg0].unk_00 = (s8) (lbl_801D4AFC * arg8);
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
