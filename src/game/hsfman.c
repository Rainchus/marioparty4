#include "common.h"

typedef struct ThreeDDataStruct {
    f32  unk_00;
    f32  unk_04;
    f32  unk_08;
    s16  unk_0C;
    s16  unk_0E;
    char unk_10[0x12];
    u16  unk_22;
    char unk_24[0x24];
    u32  unk_48;
    char unk_4C[0x4];
    s32  unk_50;
    s32  unk_54;
    char unk_58[0xC];
    f32  unk_64;
    char unk_68[0xC];
    f32  unk_74;
    char unk_78[0x1C];
    f32  unk_94;
    char unk_98[0x2C];
    void*unk_C4;
    char unk_C8[0x4];
    f32  unk_CC;
    f32  unk_D0;
    f32  unk_D4;
    f32  unk_D8;
    f32  unk_DC;
    f32  unk_E0;
    f32  unk_E4;
    f32  unk_E8;
    f32  unk_EC;
    f32  unk_F0[4];
    char unk_100[0x24];
} ThreeDDataStruct;
typedef struct ThreeDCameraStruct {
    f32  unk_00;
    char unk_04[0x54];
} ThreeDCameraStruct;
typedef struct ThreeDProjectionStruct {
    s8   unk_00;
    char unk_01[0x3];
    s32  unk_04;
    char unk_08[0xC];
    Vec3f unk_14;
    Vec3f unk_20;
    Vec3f unk_2C;
    char unk_38[0x60];
} ThreeDProjectionStruct;
typedef struct ThreeDShadowStruct {
    char unk_00[0x2];
    u16  unk_02;
    void*unk_04;
    char unk_08[0x90];
} ThreeDShadowStruct;

void Hu3DAnimInit(void);
void Hu3DFogClear(void);
void Hu3DLighInit(void);
void Hu3DMotionInit(void);
void Hu3DParManInit(void);
char *HuSprAnimRead(char*);
void HuSprAnimKill(s32);
s16 Hu3DCameraExistF;
ThreeDDataStruct Hu3DData[0x200];
ThreeDCameraStruct Hu3DCamera[0x10];
s16 Hu3DPauseF;
s16 Hu3DProjectionNum;
s16 Hu3DShadowCamBit;
s32 Hu3DShadowF;
s16 NoSyncF;
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
s16 reflectMapNo;
char *toonAnim;
s16 layerNum[8];
s32 layerHook[8];
char *reflectAnim[5];
char *hiliteAnim[4];
ThreeDProjectionStruct Hu3DProjection[4];
ThreeDShadowStruct Hu3DShadowData;
GXColor BGColor;
f32 lbl_801D4AFC;

void Hu3DInit(void) {
    ThreeDDataStruct* data;
    ThreeDCameraStruct* camera;
    s16 i;

    data = Hu3DData;
    for (i = 0; i < 0x200; i++, data++) {
        data->unk_C4 = NULL;
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

void Hu3DProjectionPosSet(s16 arg0, Vec3f arg1, Vec3f arg2, Vec3f arg3) {
    Hu3DProjection[arg0].unk_14 = arg1;
    Hu3DProjection[arg0].unk_20 = arg3;
    Hu3DProjection[arg0].unk_2C = arg2;
}

void Hu3DProjectionTPLvlSet(s16 arg0, f32 arg8) {
    Hu3DProjection[arg0].unk_00 = (s8) (lbl_801D4AFC * arg8);
}
