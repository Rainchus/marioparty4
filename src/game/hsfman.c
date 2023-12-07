#include "game/hsfman.h"

void Hu3DAnimInit(void);
void Hu3DFogClear(void);
void Hu3DLighInit(void);
void Hu3DMotionInit(void);
void Hu3DParManInit(void);

s16 Hu3DCameraExistF;
ModelData Hu3DData[0x200] = {};
ThreeDCameraStruct Hu3DCamera[0x10] = {};
s16 layerNum[8] = {};
void (*layerHook[8])(s16) = {};
char *reflectAnim[5] = {};
char *hiliteAnim[4] = {};
ThreeDProjectionStruct Hu3DProjection[4] = {};
ThreeDShadowStruct Hu3DShadowData = {};
FogStruct FogData = {};
Mtx Hu3DCameraMtx = {};
Mtx Hu3DCameraMtxXPose = {};
s16 Hu3DPauseF;
s16 Hu3DProjectionNum;
s16 Hu3DShadowCamBit;
s32 Hu3DShadowF;
u16 NoSyncF;
f32 lbl_801D4AB0;
s32 modelKillAllF;
char refMapData0[0x1240] = {};
char refMapData1[0x1100] = {};
char refMapData2[0x2080] = {};
char refMapData3[0x2080] = {};
char refMapData4[0x2080] = {};
char toonMapData[0x880] = {};
char toonMapData2[0x1080] = {};
char hiliteData[0x480] = {};
char hiliteData2[0x480] = {};
char hiliteData3[0x480] = {};
char hiliteData4[0x480] = {};
const char lbl_8012D630[] = "Error: Not Found %s for MipMapSet\n";
s16 reflectMapNo;
char *toonAnim;
GXColor BGColor;

extern s16 Hu3DCameraBit;
extern s16 Hu3DCameraNo;
extern f32 lbl_801D4AB4;
extern f32 lbl_801D4AFC;
extern GXColor lbl_801D6BE0;
extern s32 shadowModelDrawF;
extern u32 totalMatCnt;
extern u32 totalMatCnted;
extern u32 totalPolyCnt;
extern u32 totalTexCacheCnt;
extern u32 totalTexCacheCnted;
extern u32 totalTexCnt;
extern u32 totalTexCnted;

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
        Hu3DProjection[i].unk_04 = 0;
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


void Hu3DShadowSizeSet(u16 arg0) {
    Hu3DShadowData.unk_02 = arg0;
    if (Hu3DShadowData.unk_04 != 0) {
        HuMemDirectFree(Hu3DShadowData.unk_04);
    }
    Hu3DShadowData.unk_04 = HuMemDirectMalloc(HEAP_DATA, arg0 * arg0);
}

void Hu3DProjectionKill(s16 arg0) {
    HuSprAnimKill(Hu3DProjection[arg0].unk_04);
    Hu3DProjection[arg0].unk_04 = 0;
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
        OSReport(lbl_8012D630, arg2);
        return;
    }
    temp_r31 = var_r26->bitmap;
    temp_r3 = HuSprAnimRead(arg0);
    var_r30 = temp_r3->bmp;
    for ( i = 0, var_r24 = i; i < temp_r3->bmpNum; i++, var_r30++) {
        var_r24 += var_r30->dataSize;
    }
    var_r23 = HuMemDirectMallocNum(HEAP_DATA, var_r24, temp_r25->unk_48);
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
