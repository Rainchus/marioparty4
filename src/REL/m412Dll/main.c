#include "REL/m412Dll.h"

#include "math.h"
#include "ext_math.h"
#include "rel_sqrt_consts.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/frand.h"
#include "game/hsfmotion.h"
#include "game/mapspace.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"

// bss
s16 lbl_1_bss_7A0;
s16 lbl_1_bss_79E;
s16 lbl_1_bss_79C;
s16 lbl_1_bss_798[2];
s32 lbl_1_bss_794;
s32 lbl_1_bss_790;
f32 lbl_1_bss_77C;
f32 lbl_1_bss_778;
f32 lbl_1_bss_774;
unkStruct3 lbl_1_bss_4D4[4];
unkStruct2 lbl_1_bss_33C[6];
unkStruct2 lbl_1_bss_2F8;
unkStruct* lbl_1_bss_278[0x20];
Process* lbl_1_bss_274;
Vec lbl_1_bss_268;
Vec lbl_1_bss_25C;
Vec lbl_1_bss_250;
Vec lbl_1_bss_13C[0x17];
Vec lbl_1_bss_28[0x17];
s32 lbl_1_bss_24;
Vec lbl_1_bss_18;
Vec lbl_1_bss_C;
Vec lbl_1_bss_0;

// data
s32 lbl_1_data_0[8] = {
    0, 1, 2, 3, 4, 5, 6, 7
};
s32 lbl_1_data_20[8] = {
    0x5E0001, 0x190001, 0x6C0001, 0x890001,
    0x840001, 0x100001, 0x0C0001, 0x800001
};
s32 lbl_1_data_40[8] = {
    0x5F0000, 0x1A0000, 0x6D0000, 0x8A0000,
    0x850000, 0x110000, 0x0D0000, 0x810000
};
s32 lbl_1_data_60[6] = {
    0x5F0000, 0x5F0002, 0x5F0003,
    0x5F001A, 0x5F001B, 0x5F004B
};
Vec lbl_1_data_78[7] = {
    {  474.0f, 30.0f, -497.0f },
    {  330.0f, 30.0f,  562.0f },
    { -694.0f, 30.0f,   43.0f },
    { -375.0f, 30.0f, -483.0f },
    {  715.0f, 30.0f,   62.0f },
    { -334.0f, 30.0f,  570.0f },
    {  100.0f, 30.0f, -630.0f }
};
char* lbl_1_data_298[0x17] = {
    "sb_hahen-sb_hahen01",
    "sb_hahen-sb_hahen02",
    "sb_hahen-sb_hahen03",
    "sb_hahen-sb_hahen04",
    "sb_hahen-sb_hahen05",
    "sb_hahen-sb_hahen06",
    "sb_hahen-sb_hahen07",
    "sb_hahen-sb_hahen08",
    "sb_hahen-sb_hahen09",
    "sb_hahen-sb_hahen10",
    "sb_hahen-sb_hahen11",
    "sb_hahen-sb_hahen12",
    "sb_hahen-sb_hahen13",
    "sb_hahen-sb_hahen14",
    "sb_hahen-sb_hahen15",
    "sb_hahen-sb_hahen16",
    "sb_hahen-sb_hahen17",
    "sb_hahen-sb_hahen18",
    "sb_hahen-sb_hahen19",
    "sb_hahen-sb_hahen20",
    "sb_hahen-sb_hahen21",
    "sb_hahen-sb_hahen22",
    "sb_hahen-sb_hahen23"
};

void ObjectSetup(void) {
    f32 temp_f30;
    f32 temp_f29;
    f32 temp_f31;

    lbl_1_bss_274 = omInitObjMan(0x32, 0x2000);
    omGameSysInit(lbl_1_bss_274);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 40.0f, 20.0f, 25000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0U, 0U, 0x280U, 0x1E0U);
    lbl_1_bss_268.x = 1100.0f;
    lbl_1_bss_268.y = 1600.0f;
    lbl_1_bss_268.z = 760.0f;
    lbl_1_bss_250.x = 0.0f;
    lbl_1_bss_250.y = 1.0f;
    lbl_1_bss_250.z = 0.0f;
    lbl_1_bss_25C.x = 60.0f;
    lbl_1_bss_25C.y = 0.0f;
    lbl_1_bss_25C.z = 0.0f;
    temp_f30 = lbl_1_bss_268.x;
    temp_f29 = lbl_1_bss_268.y;
    temp_f31 = lbl_1_bss_268.z;
    lbl_1_bss_774 = sqrtf((temp_f31 * temp_f31) + ((temp_f30 * temp_f30) + (temp_f29 * temp_f29)));
    lbl_1_bss_778 = fn_1_1D08((180.0 * (atan2(temp_f30, temp_f31) / M_PI)));
    lbl_1_bss_77C = fn_1_1D08((180.0 * (atan2(temp_f29, temp_f31) / M_PI)));
    lbl_1_bss_77C = 50.0f;
    Hu3DLighInit();
    lbl_1_bss_7A0 = Hu3DGLightCreate(10000.0f, 0.0f, 10000.0f, -1.0f, 0.0f, -1.0f, 0xFFU, 0xFFU, 0xFFU);
    Hu3DGLightPosAimSet(lbl_1_bss_7A0, 0.0f, 4330.13f, 2500.0f, 0.0f, 0.0f, 0.0f);
    Hu3DGLightInfinitytSet(lbl_1_bss_7A0);
    lbl_1_bss_18.x = -500.0f;
    lbl_1_bss_18.y = 4000.0f;
    lbl_1_bss_18.z = 0.0f;
    lbl_1_bss_C.x = lbl_1_bss_C.z = 0.0f;
    lbl_1_bss_C.y = 1.0f;
    lbl_1_bss_0.x = 0.0f;
    lbl_1_bss_0.y = 0.0f;
    lbl_1_bss_0.z = 0.0f;
    Hu3DShadowCreate(30.0f, 20.0f, 10000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&lbl_1_bss_18, &lbl_1_bss_C, &lbl_1_bss_0);
    Hu3DBGColorSet(0U, 0U, 0U);
    fn_1_8BC();
    HuPrcChildCreate(fn_1_B1C0, 0x1000U, 0x2000U, 0, HuPrcCurrentGet());
    WipeCreate(1, 0, 0x3C);
}

void fn_1_6EC(f32 arg8, f32 arg9, f32 argA, s32 arg0) {
    Vec sp8;

    sp8.x = arg8;
    sp8.y = arg9;
    sp8.z = argA;
    HuAudFXEmiterPlay(arg0, &sp8);
}

void fn_1_73C(void) {
    Vec sp8;
    CameraData* camera;

    camera = &Hu3DCamera[0];

    sp8.x = 0.0f;
    sp8.y = 0.0f;
    sp8.z = -1.0f;

    while (1) {
        HuAudFXListnerUpdate(&camera->pos, &sp8);
        if (lbl_1_bss_794 >= 3) break;
        HuPrcVSleep();
    }
    HuPrcKill(HuPrcCurrentGet());
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_7BC(void) {
    Vec sp14;
    Vec sp8;
    s32 temp_r30;
    s32 var_r31;

    temp_r30 = (s32)HuPrcCurrentGet()->user_data;
    sp14.x = 1465.0f;
    sp14.y = 770.0f;
    sp14.z = -2400.0f;
    sp8.x = sp14.x - 474.0f;
    sp8.y = sp14.y - 30.0f;
    sp8.z = sp14.z - -497.0f;
    
    for (var_r31 = 0; var_r31 < 0x168; var_r31++) {
        HuAudFXEmiterUpDate(temp_r30, &sp14);
        PSVECAdd(&sp8, &sp14, &sp14);
        HuPrcVSleep();
    }
    HuPrcKill(HuPrcCurrentGet());
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_894(omObjData* object) {
    return;
}

void fn_1_898(omObjData* object) {
    object->model[0] = lbl_1_bss_79C;
    object->func = &fn_1_894;
}

void fn_1_8BC(void) {
    Vec sp20;
    Vec sp14;
    s32 sp10;
    volatile u32 spC;
    volatile u32 sp8;
    unkStruct2* temp_r31;
    unkStruct3* temp_r30;
    s16 var_r29;
    void* var_r27;
    s32 var_r28;
    s32 var_r26;
    unkStruct2* temp_r25;
    HsfTransform* temp_r24;
    Process* var_r23;
    s32 temp_r22;
    AnimData* var_r21;
    s16 var_r20;
    s16 var_r19;
    s32 var_r18;
    HsfObject* var_r17;
    
    nMap = 0;
    HuAudSndGrpSet(0x25);
    sp20.x = 1100.0f;
    sp20.y = 1600.0f;
    sp20.z = 760.0f;
    sp14.x = 0.0f;
    sp14.y = 0.0f;
    sp14.z = -1.0f;
    HuAudFXListnerSetEX(&sp20, &sp14, 10000.0f, 0.5666667f, 0.0f, 300.0f, 300.0f);
    var_r27 = HuDataSelHeapReadNum(0x2B0000, 0x10000000, HEAP_DATA);
    var_r29 = Hu3DModelCreate(var_r27);
    Hu3DModelLayerSet(var_r29, 1);
    Hu3DModelShadowMapSet(var_r29);
    Hu3DModelAttrSet(var_r29, 0x40000001);
    var_r27 = HuDataSelHeapReadNum(0x2B0001, 0x10000000, HEAP_DATA);
    lbl_1_bss_79C = Hu3DModelCreate(var_r27);
    Hu3DModelAttrSet(lbl_1_bss_79C, 1);
    MapObject[nMap++] = omAddObjEx(lbl_1_bss_274, 0x100, 1, 0, -1, fn_1_898);
    var_r27 = HuDataSelHeapReadNum(0x2B0002, 0x10000000, HEAP_DATA);
    var_r29 = Hu3DModelCreate(var_r27);
    Hu3DModelLayerSet(var_r29, 0);
    Hu3DModelAttrSet(var_r29, 0x40000001);
    
    for (var_r28 = 0; var_r28 < 0x20; var_r28++) {
        lbl_1_bss_278[var_r28] = NULL;
    }
    var_r27 = HuDataSelHeapReadNum(0x2B001F, 0x10000000, HEAP_DATA);
    lbl_1_bss_79E = var_r29 = Hu3DModelCameraCreate(Hu3DMotionCreate(var_r27), 1);
    Hu3DCameraMotionStart(var_r29, 1);
    
    for (var_r28 = 0; var_r28 < 2; var_r28++) {
        var_r27 = HuDataSelHeapReadNum(0x2B001D, 0x10000000, HEAP_DATA);
        lbl_1_bss_798[var_r28] = var_r29 = Hu3DModelCreate(var_r27);
        Hu3DModelLayerSet(var_r29, 2);
        Hu3DModelAttrSet(var_r29, 0x40000002);
        Hu3DModelAttrSet(var_r29, 1);
    }
    
    for (var_r28 = 0; var_r28 < 6; var_r28++) {
        temp_r31 = &lbl_1_bss_33C[var_r28];
        temp_r31->unk24 = var_r28;
        temp_r31->unk28 = var_r28;
        temp_r31->unk20 = 0;
        if (var_r28 == 0) {
            var_r27 = HuDataSelHeapReadNum(0x2B0006, 0x10000000, HEAP_DATA);
            var_r20 = var_r29 = Hu3DModelCreate(var_r27);
        } else {
            var_r29 = Hu3DModelLink(var_r20);
        }
        temp_r31->unk0 = var_r29;
        temp_r31->unk2C.x = lbl_1_data_78[var_r28].x;
        temp_r31->unk2C.y = lbl_1_data_78[var_r28].y;
        temp_r31->unk2C.z = lbl_1_data_78[var_r28].z;
        Hu3DModelPosSet(var_r29, temp_r31->unk2C.x, temp_r31->unk2C.y, temp_r31->unk2C.z);
        temp_r31->unk38.x = temp_r31->unk38.z = 0.0f;
        temp_r31->unk38.y = fn_1_1D08(180.0 + atan2d(temp_r31->unk2C.x, temp_r31->unk2C.z));
        Hu3DModelRotSet(var_r29, temp_r31->unk38.x, temp_r31->unk38.y, temp_r31->unk38.z);
        Hu3DModelLayerSet(var_r29, 1);
        Hu3DModelShadowSet(var_r29);
        
        for (var_r26 = 0; var_r26 < 3; var_r26++) {
            var_r27 = HuDataSelHeapReadNum(var_r26 + 0x2B0007, 0x10000000, HEAP_DATA);
            temp_r31->unkC[var_r26] = Hu3DJointMotion(var_r29, var_r27);
        }
        var_r27 = HuDataSelHeapReadNum(var_r28 + 0x2B000A, 0x10000000, HEAP_DATA);
        temp_r31->unkC[var_r26] = Hu3DJointMotion(var_r29, var_r27);
        Hu3DMotionSet(var_r29, temp_r31->unkC[3]);
        temp_r31->unk2 = var_r29 = Hu3DModelLink(var_r20);
        Hu3DModelPosSet(var_r29, temp_r31->unk2C.x, temp_r31->unk2C.y - 10.0f, temp_r31->unk2C.z);
        Hu3DModelRotSet(var_r29, temp_r31->unk38.x, temp_r31->unk38.y, temp_r31->unk38.z);
        Hu3DModelScaleSet(var_r29, 1.0f, -1.0f, 1.0f);
        Hu3DModelLayerSet(var_r29, 0);
        Hu3DModelShadowReset(var_r29);
        Hu3DMotionSet(var_r29, temp_r31->unkC[3]);
        Hu3DModelAttrSet(var_r29, 0x800000);
        var_r27 = HuDataSelHeapReadNum(var_r28 + 0x2B0010, 0x10000000, HEAP_DATA);
        temp_r31->unk4 = var_r29 = Hu3DModelCreate(var_r27);
        Hu3DModelLayerSet(var_r29, 1);
        if (var_r28 >= 3) {
            Hu3DModelAttrSet(temp_r31->unk0, 0x40000002);
            Hu3DModelAttrSet(temp_r31->unk2, 0x40000002);
            Hu3DModelAttrSet(temp_r31->unk4, 0x40000002);
        }
        if (var_r28 == 0) {
            var_r27 = HuDataSelHeapReadNum(0x2B0003, 0x10000000, HEAP_DATA);
            var_r19 = var_r29 = Hu3DModelCreate(var_r27);
        } else {
            var_r29 = Hu3DModelLink(var_r19);
        }
        temp_r31->unk6 = var_r29;
        Hu3DModelLayerSet(var_r29, 1);
        Hu3DModelAttrSet(var_r29, 1);
        Hu3DModelShadowSet(var_r29);
        Hu3DModelShadowDispOff(var_r29);
        temp_r31->unk8 = Hu3DModelLink(var_r19);
        Hu3DModelLayerSet(var_r29, 0);
        Hu3DModelAttrSet(temp_r31->unk8, 1);
        var_r23 = HuPrcChildCreate(fn_1_2A1C, 0x2000, 0x3000, 0, HuPrcCurrentGet());
        var_r23->user_data = temp_r31;
    }
    
    for (var_r28 = 0, var_r18 = 0; var_r28 < 50; var_r28++) {
        temp_r31 = &lbl_1_bss_33C[frandmod(3) + var_r18];
        temp_r25 = &lbl_1_bss_33C[frandmod(3) + var_r18];
        temp_r22 = temp_r31->unk28;
        temp_r31->unk28 = temp_r25->unk28;
        temp_r25->unk28 = temp_r22;
    }
    temp_r31 = &lbl_1_bss_33C[3];
    temp_r25 = &lbl_1_bss_33C[5];
    temp_r22 = temp_r31->unk28;
    temp_r31->unk28 = temp_r25->unk28;
    temp_r25->unk28 = temp_r22;
    if (frandmod(2) != 0) {
        temp_r31 = &lbl_1_bss_33C[4];
        temp_r25 = &lbl_1_bss_33C[5];
        temp_r22 = temp_r31->unk28;
        temp_r31->unk28 = temp_r25->unk28;
        temp_r25->unk28 = temp_r22;
    }
    temp_r31 = &lbl_1_bss_2F8;
    var_r27 = HuDataSelHeapReadNum(0x2B0016, 0x10000000, HEAP_DATA);
    var_r20 = var_r29 = Hu3DModelCreate(var_r27);
    temp_r31->unk0 = var_r29;
    temp_r31->unk2C.x = lbl_1_data_78[6].x;
    temp_r31->unk2C.y = lbl_1_data_78[6].y;
    temp_r31->unk2C.z = lbl_1_data_78[6].z;
    Hu3DModelPosSet(var_r29, temp_r31->unk2C.x, temp_r31->unk2C.y, temp_r31->unk2C.z);
    temp_r31->unk38.x = temp_r31->unk38.z = 0.0f;
    temp_r31->unk38.y = fn_1_1D08(180.0 + atan2d(temp_r31->unk2C.x, temp_r31->unk2C.z));
    Hu3DModelRotSet(var_r29, temp_r31->unk38.x, temp_r31->unk38.y, temp_r31->unk38.z);
    Hu3DModelLayerSet(var_r29, 1);
    Hu3DModelShadowSet(var_r29);
    
    for (var_r26 = 0; var_r26 < 5; var_r26++) {
        var_r27 = HuDataSelHeapReadNum(var_r26 + 0x2B0017, 0x10000000, HEAP_DATA);
        temp_r31->unkC[var_r26] = Hu3DJointMotion(var_r29, var_r27);
    }
    var_r27 = HuDataSelHeapReadNum(0x2B0016, 0x10000000, HEAP_DATA);
    temp_r31->unk2 = var_r29 = Hu3DModelCreate(var_r27);
    
    for (var_r26 = 0; var_r26 < 5; var_r26++) {
        var_r27 = HuDataSelHeapReadNum(var_r26 + 0x2B0017, 0x10000000, HEAP_DATA);
        temp_r31->unk16[var_r26] = Hu3DJointMotion(var_r29, var_r27);
    }
    Hu3DModelPosSet(var_r29, temp_r31->unk2C.x, temp_r31->unk2C.y - 10.0f, temp_r31->unk2C.z);
    Hu3DModelRotSet(var_r29, temp_r31->unk38.x, temp_r31->unk38.y, temp_r31->unk38.z);
    Hu3DModelScaleSet(var_r29, 1.0f, -1.0f, 1.0f);
    Hu3DModelLayerSet(var_r29, 0);
    Hu3DModelShadowReset(var_r29);
    Hu3DModelAttrSet(var_r29, 0x800000);
    var_r27 = HuDataSelHeapReadNum(0x2B0004, 0x10000000, HEAP_DATA);
    temp_r31->unk6 = var_r29 = Hu3DModelCreate(var_r27);
    Hu3DModelLayerSet(var_r29, 1);
    Hu3DModelAttrSet(var_r29, 1);
    Hu3DModelShadowSet(var_r29);
    Hu3DModelShadowDispOff(var_r29);
    temp_r31->unk8 = Hu3DModelLink(temp_r31->unk6);
    Hu3DModelLayerSet(temp_r31->unk8, 0);
    Hu3DModelAttrSet(temp_r31->unk8, 1);
    var_r27 = HuDataSelHeapReadNum(0x2B0005, 0x10000000, HEAP_DATA);
    temp_r31->unkA = var_r29 = Hu3DModelCreate(var_r27);
    Hu3DModelShadowSet(var_r29);
    Hu3DModelShadowDispOff(var_r29);
    Hu3DModelLayerSet(var_r29, 1);
    Hu3DModelAttrSet(var_r29, 1);
    
    for (var_r28 = 0; var_r28 < 0x17; var_r28++) {
        var_r17 = Hu3DModelObjPtrGet(var_r29, lbl_1_data_298[var_r28]);
        if (!var_r17) {
            OSReport("objname %s\n", lbl_1_data_298[var_r28]);
            OSPanic("m412.c", 0x258, "ObjPtr");
        }
        temp_r24 = &var_r17->data.base;
        lbl_1_bss_13C[var_r28].x = temp_r24->pos.x;
        lbl_1_bss_13C[var_r28].y = temp_r24->pos.y;
        lbl_1_bss_13C[var_r28].z = temp_r24->pos.z;
        lbl_1_bss_28[var_r28].x = temp_r24->scale.x;
        lbl_1_bss_28[var_r28].y = temp_r24->scale.y;
        lbl_1_bss_28[var_r28].z = temp_r24->scale.z;
    }
    var_r23 = HuPrcChildCreate(fn_1_3950, 0x2000, 0x3000, 0, HuPrcCurrentGet());
    var_r23->user_data = temp_r31;
    
    for (var_r28 = 0; var_r28 < 4; var_r28++) {
        lbl_1_bss_4D4[var_r28].unk3C = var_r28;
    }
    
    for (var_r28 = 0; var_r28 < 50; var_r28++) {
        spC = frandmod(4);
        sp8 = frandmod(4);
        sp10 = lbl_1_bss_4D4[sp8].unk3C;
        lbl_1_bss_4D4[sp8].unk3C = lbl_1_bss_4D4[spC].unk3C;
        lbl_1_bss_4D4[spC].unk3C = sp10;
    }
    
    for (var_r28 = 0; var_r28 < 4; var_r28++) {
        temp_r30 = &lbl_1_bss_4D4[var_r28];
        temp_r30->unk24 = var_r28;
        temp_r30->unk28 = var_r28;
        temp_r30->unk2C = GWPlayerCfg[var_r28].pad_idx;
        temp_r30->unk0 = CharModelCreate(lbl_1_data_0[GWPlayerCfg[var_r28].character], 4);
        Hu3DModelLayerSet(temp_r30->unk0, 1);
        var_r27 = HuDataSelHeapReadNum(lbl_1_data_20[GWPlayerCfg[var_r28].character], 0x10000000, HEAP_DATA);
        temp_r30->unk2 = Hu3DModelCreate(var_r27);
        Hu3DModelScaleSet(temp_r30->unk2, 1.0f, -1.0f, 1.0f);
        Hu3DModelAttrSet(temp_r30->unk2, 0x800000);
        Hu3DModelLayerSet(temp_r30->unk2, 0);
        CharModelLayerSetAll(3);
        temp_r30->unk54.x = temp_r30->unk54.z = temp_r30->unk54.y = 0.0f;
        temp_r30->unk54.y = fn_1_1D08(45.0f + (90.0f * temp_r30->unk3C) + lbl_1_bss_778);
        temp_r30->unk40.x = (400.0 * sind(temp_r30->unk54.y));
        temp_r30->unk40.z = (400.0 * cosd(temp_r30->unk54.y));
        temp_r30->unk54.y = fn_1_1D08(180.0f + temp_r30->unk54.y);
        temp_r30->unk6C = temp_r30->unk54.y;
        temp_r30->unk40.y = 0.0f;
        temp_r30->unk60.x = 50.0f;
        temp_r30->unk60.z = temp_r30->unk60.y = 0.0f;
        HuSetVecF(&temp_r30->unk7C, 0.0, 0.0, 0.0);
        Hu3DModelPosSet(temp_r30->unk0, temp_r30->unk40.x, temp_r30->unk40.y, temp_r30->unk40.z);
        Hu3DModelRotSet(temp_r30->unk0, temp_r30->unk54.x, temp_r30->unk54.y, temp_r30->unk54.z);
        Hu3DModelPosSet(temp_r30->unk2, temp_r30->unk40.x, temp_r30->unk40.y, temp_r30->unk40.z);
        Hu3DModelRotSet(temp_r30->unk2, temp_r30->unk54.x, temp_r30->unk54.y, temp_r30->unk54.z);
        Hu3DModelShadowSet(temp_r30->unk0);
        
        for (var_r26 = 0; var_r26 < 6; var_r26++) {
            temp_r30->unkC[var_r26] = CharModelMotionCreate(lbl_1_data_0[GWPlayerCfg[var_r28].character], lbl_1_data_60[var_r26]);
            var_r27 = HuDataSelHeapReadNum((u16)lbl_1_data_60[var_r26] | lbl_1_data_40[GWPlayerCfg[var_r28].character], 0x10000000, HEAP_DATA);
            temp_r30->unk18[var_r26] = Hu3DJointMotion(temp_r30->unk2, var_r27);
        }
        CharModelMotionSet(lbl_1_data_0[GWPlayerCfg[var_r28].character], temp_r30->unkC[0]);
        Hu3DModelAttrSet(temp_r30->unk0, 0x40000001);
        Hu3DMotionSet(temp_r30->unk2, temp_r30->unk18[0]);
        Hu3DModelAttrSet(temp_r30->unk2, 0x40000001);
        CharModelMotionDataClose(lbl_1_data_0[GWPlayerCfg[var_r28].character]);
        var_r27 = HuDataSelHeapReadNum(0x2B001C, 0x10000000, HEAP_DATA);
        temp_r30->unk6 = var_r29 = Hu3DModelCreate(var_r27);
        Hu3DModelLayerSet(var_r29, 1);
        Hu3DModelAttrSet(var_r29, 0x40000001);
        Hu3DModelAttrSet(var_r29, 1);
        Hu3DModelShadowSet(var_r29);
        Hu3DModelShadowDispOff(var_r29);
        temp_r30->unk8 = var_r29 = Hu3DModelLink(var_r29);
        Hu3DModelLayerSet(var_r29, 0);
        Hu3DModelAttrSet(var_r29, 0x40000001);
        Hu3DModelAttrSet(var_r29, 0x800001);
        var_r27 = HuDataSelHeapReadNum(0x2B001D, 0x10000000, HEAP_DATA);
        temp_r30->unkA = var_r29 = Hu3DModelCreate(var_r27);
        Hu3DModelLayerSet(var_r29, 3);
        Hu3DModelAttrSet(var_r29, 0x40000002);
        Hu3DModelAttrSet(var_r29, 1);
        var_r23 = HuPrcChildCreate(fn_1_7C60, 0x2000, 0x4000, 0, HuPrcCurrentGet());
        var_r23->user_data = temp_r30;
    }
    var_r21 = HuSprAnimRead(HuDataReadNum(0x2B001E, 0x10000000));
    var_r29 = Hu3DParticleCreate(var_r21, 0x100);
    Hu3DModelPosSet(var_r29, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(var_r29, 1.0f, 1.0f, 1.0f);
    Hu3DModelLayerSet(var_r29, 4);
    Hu3DParticleColSet(var_r29, 0xFF, 0xFF, 0xFF);
    Hu3DParticleScaleSet(var_r29, 0.0f);
    Hu3DParticleHookSet(var_r29, fn_1_A01C);
    var_r21 = HuSprAnimRead(HuDataReadNum(0x120003, 0x10000000));
    var_r29 = Hu3DParticleCreate(var_r21, 0x40);
    Hu3DModelPosSet(var_r29, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(var_r29, 1.0f, 1.0f, 1.0f);
    Hu3DModelLayerSet(var_r29, 4);
    Hu3DParticleColSet(var_r29, 0xFF, 0xFF, 0xFF);
    Hu3DParticleScaleSet(var_r29, 0.0f);
    Hu3DParticleHookSet(var_r29, fn_1_A618);
    var_r21 = HuSprAnimRead(HuDataReadNum(0x120003, 0x10000000));
    var_r29 = Hu3DParticleCreate(var_r21, 3);
    Hu3DModelPosSet(var_r29, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(var_r29, 1.0f, 1.0f, 1.0f);
    Hu3DModelLayerSet(var_r29, 4);
    Hu3DParticleColSet(var_r29, 0xFF, 0xFF, 0xFF);
    Hu3DParticleScaleSet(var_r29, 0.0f);
    Hu3DParticleHookSet(var_r29, fn_1_AA88);
    HuDataDirClose(0x120000);
    HuPrcChildCreate(fn_1_B160, 0x1000, 0x1000, 0, HuPrcCurrentGet());
}

f32 fn_1_1D08(f32 arg0) {
    while (arg0 >= 360.0f || arg0 < 0.0f) {
        if (arg0 >= 360.0f) {
            arg0 -= 360.0f;
        }
        if (arg0 < 0.0f) {
            arg0 += 360.0f;
        }
    }
    return arg0;
}

void fn_1_1D88(void) {
    void* var_r31;

    var_r31 = HuPrcCurrentGet()->user_data;
    HuMemDirectFree(var_r31);
}

void fn_1_1DBC(void) {
    Vec sp8;
    HsfObject* var_r27;
    HsfTransform* temp_r31;
    unkStruct4* temp_r30;
    Vec* temp_r29;
    s32 var_r28;
    f32 var_f31;
    f32 var_f30;

    temp_r30 = HuPrcCurrentGet()->user_data;
    HuPrcDestructorSet(fn_1_1D88);
    var_r27 = Hu3DModelObjPtrGet(temp_r30->unk0, lbl_1_data_298[temp_r30->unk4]);
    if (!var_r27) {
        OSReport("objname %s\n", lbl_1_data_298[temp_r30->unk4]);
        OSPanic("m412.c", 0x32E, "ObjPtr");
    }
    temp_r31 = &var_r27->data.base;
    temp_r29 = &lbl_1_bss_13C[temp_r30->unk4];
    temp_r31->pos.x = temp_r29->x;
    temp_r31->pos.y = temp_r29->y;
    temp_r31->pos.z = temp_r29->z;
    HuSetVecF(&sp8, 0.15f * temp_r31->pos.x, 0.15f * temp_r31->pos.y, 0.15f * temp_r31->pos.z);
    temp_r29 = &lbl_1_bss_28[temp_r30->unk4];
    temp_r31->scale.x = temp_r29->x;
    temp_r31->scale.y = temp_r29->y;
    temp_r31->scale.z = temp_r29->z;
    for (var_r28 = 0, var_f31 = -2.0f, var_f30 = 1.0f; var_r28 < 0x1E; var_r28++) {
        sp8.y -= var_f31;
        var_f31 += 0.5f;
        temp_r31->pos.x += sp8.x;
        temp_r31->pos.y += sp8.y;
        temp_r31->pos.z += sp8.z;
        temp_r31->scale.x *= 0.95f;
        temp_r31->scale.y *= 0.95f;
        temp_r31->scale.z *= 0.95f;
        if (temp_r30->unk4 == 0) {
            var_f30 -= 0.033333335f;
            Hu3DModelTPLvlSet(temp_r30->unk0, var_f30);
        }
        HuPrcVSleep();
    }
    temp_r30->unk8 = 0;
    HuPrcVSleep();
    HuPrcKill(HuPrcCurrentGet());
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_2014(void) {
    unkStruct2* temp_r31; // could also be unkStruct3 `\_("/)_/`

    temp_r31 = (unkStruct2*)HuPrcCurrentGet()->user_data;
    lbl_1_bss_278[temp_r31->unk6] = NULL;
    HuMemDirectFree(temp_r31);
}

void fn_1_2064(void) {
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    f32 spC;
    f32 sp8;
    Process* temp_r26;
    s32 var_r30;
    unkStruct* temp_r28;
    unkStruct3* temp_r29;
    unkStruct* temp_r31;
    unkStruct4* var_r27;

    temp_r31 = (unkStruct*)HuPrcCurrentGet()->user_data;
    temp_r31->unk8 = 0;
    temp_r31->unkA = 0;
    HuPrcDestructorSet(fn_1_2014);
    
    do {
        if ((temp_r31->unk8 != 0) || (lbl_1_bss_794 >= 4)) break;
        temp_r31->unk10.x += (temp_r31->unk24.y * sind(temp_r31->unk24.x));
        temp_r31->unk10.z += (temp_r31->unk24.y * cosd(temp_r31->unk24.x));
        temp_r31->unk10.y += temp_r31->unk24.z;
        temp_r31->unk24.z -= 0.9f;
        if (temp_r31->unk30 != 100.0f) {
            HuSetVecF(&sp28, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
            for (var_r30 = 0; var_r30 < 0x20; var_r30++) {
                temp_r28 = lbl_1_bss_278[var_r30];
                if ((var_r30 != temp_r31->unk6) && temp_r28 && (temp_r28->unk6 != -1)) {
                    HuSetVecF(&sp1C, temp_r28->unk10.x, temp_r28->unk10.y, temp_r28->unk10.z);
                    HuSubVecF(&sp10, &sp28, &sp1C);
                    if (sqrtf((sp10.z * sp10.z) + ((sp10.x * sp10.x) + (sp10.y * sp10.y))) < (temp_r31->unk30 + temp_r28->unk30)) {
                        if (temp_r28->unk30 != 100.0f) {
                            temp_r28->unk8 = 1;
                        }
                        temp_r31->unk8 = 1;
                    }
                }
            }
        }
        HuSetVecF(&sp28, temp_r31->unk10.x, 0.0, temp_r31->unk10.z);
        
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            temp_r29 = &lbl_1_bss_4D4[var_r30];
            HuSetVecF(&sp1C, temp_r29->unk40.x, 0.0, temp_r29->unk40.z);
            HuSubVecF(&sp10, &sp28, &sp1C);
            if ((sqrtf((sp10.z * sp10.z) + ((sp10.x * sp10.x) + (sp10.y * sp10.y))) < (temp_r31->unk30 + temp_r29->unk60.x))
                && ((150.0f + temp_r29->unk40.y + temp_r31->unk30) > temp_r31->unk10.y)) {
                
                if (temp_r29->unk30 != 3) {
                    if (temp_r31->unkC == 0) {
                        omVibrate(temp_r29->unk24, 0xC, 4, 2);
                    } else {
                        omVibrate(temp_r29->unk24, 0xC, 0xC, 0);
                    }
                }
                HuAudFXPlay(0x585);
                temp_r29->unk30 = 3;
                temp_r31->unk8 = 1;
            }
        }
        if (temp_r31->unk10.y < temp_r31->unk30) {
            temp_r31->unk10.y = temp_r31->unk30;
            temp_r31->unk8 = 1;
        }
        Hu3DModelPosSet(temp_r31->unk0, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
        Hu3DModelPosSet(temp_r31->unk2, temp_r31->unk10.x, -temp_r31->unk10.y, temp_r31->unk10.z);
        if (temp_r31->unk8 != 0) break;
        HuPrcVSleep();
    } while (1);
    if (temp_r31->unkC == 1) {
        HuAudFXPlay(0x58D);
    } else {
        HuAudFXPlay(0x58C);
    }
    Hu3DModelAttrSet(temp_r31->unk0, 1);
    Hu3DModelAttrSet(temp_r31->unk2, 1);
    Hu3DModelShadowDispOff(temp_r31->unk0);
    temp_r31->unkA = 1;
    if (temp_r31->unkC == 1) {
        
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            if (lbl_1_bss_4D4[var_r30].unk30 != 3) {
                omVibrate(lbl_1_bss_4D4[var_r30].unk24, 0xC, 6, 6);
            }
        }
        Hu3DModelPosSet(temp_r31->unk4, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
        Hu3DModelAttrReset(temp_r31->unk4, 1);
        Hu3DModelShadowDispOn(temp_r31->unk4);
        
        for (var_r30 = 0; var_r30 < 0x17; var_r30++) {
            temp_r26 = HuPrcChildCreate(fn_1_1DBC, 0x2000, 0x1000, 0, HuPrcCurrentGet());
            var_r27 = HuMemDirectMalloc(HEAP_DATA, 0x18);
            temp_r26->user_data = var_r27;
            var_r27->unk0 = temp_r31->unk4;
            var_r27->unk4 = var_r30;
            var_r27->unk8 = 1;
            var_r27->unkC.x = temp_r31->unk10.x;
            var_r27->unkC.y = temp_r31->unk10.y;
            var_r27->unkC.z = temp_r31->unk10.z;
        }
        while (var_r27->unk8 != 0) {
            HuPrcVSleep();
        }
    }
    HuPrcVSleep();
    HuPrcKill(HuPrcCurrentGet());
    while (1) {
        HuPrcVSleep();
    }
}

s32 fn_1_2708(void) {
    s32 var_r31;
    
    for (var_r31 = 0; var_r31 < 0x20; var_r31++) {
        if (!lbl_1_bss_278[var_r31]) break;
    }
    if (var_r31 >= 0x20) {
        var_r31 = -1;
    }
    lbl_1_bss_278[var_r31] = HuMemDirectMalloc(HEAP_DATA, 0x34);
    lbl_1_bss_278[var_r31]->unk6 = -1;
    lbl_1_bss_278[var_r31]->unkA = 0;
    return var_r31;
}

f32 fn_1_27C4(s32 arg0, f32 arg8, f32 arg9) {
    f32 temp_f31;
    f32 var_f25;
    f32 var_f26;
    f32 var_f27;
    f32 var_f28;
    f32 var_f29;
    
    temp_f31 = arg8 - fn_1_1D08(arg9);
    if ((temp_f31 < 0.0f) || (ABS_INV(temp_f31) > 180.0f)) {
        if (ABS_INV(temp_f31) > 180.0f) {
            var_f29 = (360.0f - ABS_INV(temp_f31)) / arg0;
            if (temp_f31 > 0.0f) {
                var_f29 = -var_f29;
            }
        } else {
            var_f29 = temp_f31 / arg0;
        }
    } else {
        var_f29 = temp_f31 / arg0;
    }
    return var_f29;
}

s32 lbl_1_data_310[6][2] = {
    { 0x09249222, 0x22210842 },
    { 0x04924888, 0x88842108 },
    { 0x12492222, 0x22108420 },
    { 0x04444444, 0x44444400 },
    { 0x11111111, 0x11100000 },
    { 0x04444444, 0x40000000 }
};

s32 lbl_1_data_340[1][2] = {
    { 0x00040008, 0x02000000 }
};

s32 lbl_1_data_348[6] = {
    0x0, 0x0, 0x0, 0x8, 0x12, 0x1C
};

void fn_1_2A1C(void) {
    Vec sp68;
    Vec sp5C;
    Vec sp50;
    Vec sp44;
    f32 sp40;
    f32 temp_f18;
    f32 var_f24;
    f32 var_f23;
    f32 var_f19;
    f32 var_f22;
    s32 var_r22;
    s32 var_r23;
    s32 var_r25;
    s32 var_r24;
    s32 var_r26;
    s32 var_r29;
    unkStruct* temp_r30;
    unkStruct3* temp_r27;
    unkStruct2* temp_r31;
    s32 var_r21;
    Process* var_r20;

    temp_r31 = HuPrcCurrentGet()->user_data;
    switch (temp_r31->unk24) {
        case 0:
            var_r25 = 0x142;
            var_r24 = 0x154;
            break;
        case 1:
            var_r25 = 0x14A;
            var_r24 = 0x15E;
            break;
        case 2:
            var_r25 = 0x148;
            var_r24 = 0x162;
            break;
        default:
            var_r25 = 0x4E;
            var_r24 = 0x5D;
            break;
    }
    
loop_10:
    var_r29 = lbl_1_bss_790 / 60;
    if (var_r29 >= 0x3C) {
        var_r29 = 0x3C;
    }
    if (var_r29 == lbl_1_data_348[temp_r31->unk28]) {
        Hu3DModelAttrReset(temp_r31->unk0, 0x40000002);
        Hu3DModelAttrReset(temp_r31->unk2, 0x40000002);
        Hu3DModelAttrReset(temp_r31->unk4, 0x40000002);
    }
    if (var_r25 == Hu3DMotionTimeGet(temp_r31->unk0)) {
        temp_r31->unk20 = 1;
    }
    if (var_r24 == Hu3DMotionTimeGet(temp_r31->unk0)) {
        HuAudFXPlay(0x581);
    }
    if (lbl_1_bss_794 >= 4) {
        while (1) {
            HuPrcVSleep();
        }
    }
    var_r22 = 1;
    if (var_r29 >= 0x20) {
        var_r22 = 0;
    }
    if (((1 << (var_r29 % 32)) & lbl_1_data_310[temp_r31->unk28][var_r22]) != 0) {
        var_r21 = fn_1_2708();
    } else {
        HuPrcVSleep();
        goto loop_10;
    }
    var_r26 = frandmod(4);
    if (lbl_1_bss_4D4[var_r26].unk30 == 3) {
         for (var_r23 = 3; var_r23 != 0; var_r23--) {
            var_r26++;
            if (var_r26 >= 4) {
                var_r26 = 0;
            }
            if (lbl_1_bss_4D4[var_r26].unk30 != 3) break;
        }
    }
    temp_r27 = &lbl_1_bss_4D4[var_r26];
    Hu3DMotionSet(temp_r31->unk0, temp_r31->unkC[1]);
    Hu3DMotionSet(temp_r31->unk2, temp_r31->unkC[1]);
    Hu3DModelAttrReset(temp_r31->unk0, 0x40000001);
    Hu3DModelAttrReset(temp_r31->unk2, 0x40000001);
    var_r29 = Hu3DMotionMaxTimeGet(temp_r31->unk0);
    var_f24 = fn_1_1D08(atan2d(temp_r27->unk40.x - temp_r31->unk2C.x, temp_r27->unk40.z - temp_r31->unk2C.z));
    temp_f18 = (temp_r27->unk40.x + (50.0 * sind(var_f24)));
    sp44.y =     (temp_r27->unk40.z + (50.0 * cosd(var_f24)));
    sp44.x = 360.0f * frandf();
    var_f23 = 50.0f * frandf();
    temp_f18 += (var_f23 * sind(sp44.x));
    sp44.y += (var_f23 * cosd(sp44.x));
    sp44.z = fn_1_27C4(var_r29, var_f24, temp_r31->unk38.y);
    HuAudFXPlay(0x583);

    for (;var_r29 != 0; var_r29--) {
        temp_r31->unk38.y += sp44.z;
        Hu3DModelRotSet(temp_r31->unk0, temp_r31->unk38.x, temp_r31->unk38.y, temp_r31->unk38.z);
        Hu3DModelRotSet(temp_r31->unk2, temp_r31->unk38.x, temp_r31->unk38.y, temp_r31->unk38.z);
        HuPrcVSleep();
    }
    HuPrcSleep(0x1E);
    Hu3DModelAttrReset(temp_r31->unk6, 1);
    Hu3DModelAttrReset(temp_r31->unk8, 1);
    Hu3DModelShadowDispOn(temp_r31->unk6);
    Hu3DModelPosSet(temp_r31->unk6, 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(temp_r31->unk8, 0.0f, 0.0f, 0.0f);
    Hu3DModelHookSet(temp_r31->unk0, "itemhook", temp_r31->unk6);
    Hu3DModelHookSet(temp_r31->unk2, "itemhook", temp_r31->unk8);
    Hu3DMotionShiftSet(temp_r31->unk0, temp_r31->unkC[2], 0.0f, 5.0f, 0);
    Hu3DMotionShiftSet(temp_r31->unk2, temp_r31->unkC[2], 0.0f, 5.0f, 0);
    HuPrcSleep(10);
    while (Hu3DMotionTimeGet(temp_r31->unk0) < 18.0f) {
        HuPrcVSleep();
    }
    Hu3DModelHookReset(temp_r31->unk0);
    Hu3DModelHookReset(temp_r31->unk2);
    HuAudFXPlay(0x582);
    temp_r30 = lbl_1_bss_278[var_r21];
    temp_r30->unk6 = var_r21;
    temp_r30->unkA = 0;
    var_r20 = HuPrcChildCreate(fn_1_2064, 0x1000, 0x3000, 0, HuPrcCurrentGet());
    var_r20->user_data = temp_r30;
    temp_r30->unkC = 0;
    temp_r30->unk0 = temp_r31->unk6;
    temp_r30->unk2 = temp_r31->unk8;
    temp_r30->unk30 = 25.0f;
    temp_r30->unk10.x = -89.937f;
    temp_r30->unk10.y = 125.861f;
    temp_r30->unk10.z = 43.181f;
    temp_r30->unk1C.x = temp_f18;
    temp_r30->unk1C.y = sp44.y;
    var_f24 = fn_1_1D08(atan2d(temp_r30->unk10.x, temp_r30->unk10.z));
    var_f24 += temp_r31->unk38.y;
    var_f23 = sqrtf((temp_r30->unk10.x * temp_r30->unk10.x) + (temp_r30->unk10.z * temp_r30->unk10.z));
    temp_r30->unk10.x = (temp_r31->unk2C.x + (var_f23 * sind(var_f24)));
    temp_r30->unk10.y = 125.861f + temp_r31->unk2C.y;
    temp_r30->unk10.z = (temp_r31->unk2C.z + (var_f23 * cosd(var_f24)));
    Hu3DModelPosSet(temp_r31->unk6, temp_r30->unk10.x, temp_r30->unk10.y, temp_r30->unk10.z);
    Hu3DModelPosSet(temp_r31->unk8, temp_r30->unk10.x, -temp_r30->unk10.y, temp_r30->unk10.z);
    HuSetVecF(&sp68, temp_r31->unk2C.x, 0.0, temp_r31->unk2C.z);
    HuSetVecF(&sp5C, temp_f18, 0.0, sp44.y);
    HuSubVecF(&sp50, &sp68, &sp5C);
    var_f23 = sqrtf((sp50.x * sp50.x) + (sp50.z * sp50.z));
    sp40 = 1.0f;
    while (1) {
        for (var_r29 = 0, var_f19 = temp_r30->unk10.y, var_f22 = sp40; var_f22 > 0.0f; var_r29++) {
            var_f19 += var_f22;
            var_f22 -= 0.9f;
        }
        if (var_f19 >= (var_f23 / 2.0f)) break;
        sp40++;
    }

    for (;var_f19 > 0.0f; var_r29++) {
        var_f19 += var_f22;
        var_f22 -= 0.9f;
    }
    temp_r30->unk24.z = sp40;
    temp_r30->unk24.x = fn_1_1D08(atan2d(temp_f18 - temp_r30->unk10.x, sp44.y - temp_r30->unk10.z));
    temp_r30->unk24.y = var_f23 / var_r29;
    
    while (Hu3DMotionEndCheck(temp_r31->unk0) == 0) {
        HuPrcVSleep();
    }
    goto loop_10;
}

void fn_1_3950(void) {
    Vec sp8C;
    Vec sp80;
    Vec sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    volatile f32 sp58;
    f32 sp54;
    f32 temp_f27;
    f32 var_f29;
    f32 temp_f31;
    f32 temp_f30;
    f32 var_f18;
    f32 var_f19;
    f32 var_f20;
    f32 var_f21;
    f32 var_f22;
    f32 var_f23;
    f32 var_f24;
    s32 var_r28;
    s32 var_r24;
    s32 var_r25;
    s32 var_r29;
    s32 var_r26;
    unkStruct* temp_r30;
    unkStruct3* temp_r27;
    unkStruct2* temp_r31;
    s32 var_r23;
    Process* var_r22;

    temp_r31 = HuPrcCurrentGet()->user_data;
loop_1:
    var_r29 = lbl_1_bss_790 / 60;
    if (var_r29 >= 0x3C) {
        var_r29 = 0x3C;
    }
    if (lbl_1_bss_794 >= 4) {
        while (1) {
            HuPrcVSleep();
        }
    }
    var_r24 = 1;
    if (var_r29 >= 0x20) {
        var_r24 = 0;
    }
    if (((1 << (var_r29 % 32)) & lbl_1_data_340[temp_r31->unk28][var_r24]) != 0) {
        var_r23 = fn_1_2708();
    } else {
        HuPrcVSleep();
        goto loop_1;
    }
    Hu3DModelAttrReset(temp_r31->unk0, 0x40000002);
    Hu3DModelClusterAttrReset(temp_r31->unk0, 0, -0x3FFFFFFE);
    Hu3DModelAttrReset(temp_r31->unk2, 0x40000002);
    Hu3DModelClusterAttrReset(temp_r31->unk2, 0, -0x3FFFFFFE);
    Hu3DModelAttrReset(temp_r31->unk6, 1);
    Hu3DModelAttrReset(temp_r31->unk8, 1);
    Hu3DModelShadowDispOn(temp_r31->unk6);
    var_f18 = 850.0f;
    temp_f31 = -217.722f;
    temp_f30 = 0.0f;
    var_f29 = fn_1_1D08(atan2d(temp_f31, temp_f30));
    var_f29 += temp_r31->unk38.y;
    var_f24 = sqrtf((temp_f31 * temp_f31) + (temp_f30 * temp_f30));
    temp_f31 = (temp_r31->unk2C.x + (var_f24 * sind(var_f29)));
    temp_f30 = (temp_r31->unk2C.z + (var_f24 * cosd(var_f29)));
    sp64 = 5.0f;
    while (1) {
        var_f18 -= sp64;
        sp64 += 0.9f;
        if (sp64 > 20.0f) {
            sp64 = 20.0f;
        }
        if (var_f18 < (304.52f + temp_r31->unk2C.y)) {
            var_f18 = 304.52f + temp_r31->unk2C.y;
        }
        Hu3DModelPosSet(temp_r31->unk6, temp_f31, var_f18, temp_f30);
        Hu3DModelPosSet(temp_r31->unk8, temp_f31, -var_f18, temp_f30);
        if (var_f18 == (304.52f + temp_r31->unk2C.y)) break;
        HuPrcVSleep();
    }
    Hu3DModelPosSet(temp_r31->unk6, 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(temp_r31->unk8, 0.0f, 0.0f, 0.0f);
    Hu3DModelHookSet(temp_r31->unk0, "itemhook", temp_r31->unk6);
    Hu3DModelHookSet(temp_r31->unk2, "itemhook", temp_r31->unk8);
    Hu3DMotionShiftSet(temp_r31->unk0, temp_r31->unkC[2], 0.0f, 5.0f, 0);
    Hu3DMotionShiftSet(temp_r31->unk2, temp_r31->unk16[2], 0.0f, 5.0f, 0);
    HuPrcSleep(10);
    
    while (Hu3DMotionEndCheck(temp_r31->unk0) == 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(0xA);
    var_r26 = frandmod(4);
    if (lbl_1_bss_4D4[var_r26].unk30 == 3) {
        for (var_r25 = 3; var_r25 != 0; var_r25--) {
            var_r26 += 1;
            if (var_r26 >= 4) {
                var_r26 = 0;
            }
            if (lbl_1_bss_4D4[var_r26].unk30 != 3) break;
        }
    }
    temp_r27 = &lbl_1_bss_4D4[var_r26];
    Hu3DMotionSet(temp_r31->unk0, temp_r31->unkC[3]);
    Hu3DModelAttrReset(temp_r31->unk0, 0x40000001);
    Hu3DMotionSet(temp_r31->unk2, temp_r31->unk16[3]);
    Hu3DModelAttrReset(temp_r31->unk2, 0x40000001);
    var_r29 = Hu3DMotionMaxTimeGet(temp_r31->unk0);
    var_f29 = fn_1_1D08(atan2d(temp_r27->unk40.x - temp_r31->unk2C.x, temp_r27->unk40.z - temp_r31->unk2C.z));
    sp6C = (temp_r27->unk40.x + (50.0 * sind(var_f29)));
    sp68 = (temp_r27->unk40.z + (50.0 * cosd(var_f29)));
    sp60 = 360.0f * frandf();
    var_f24 = 50.0f * frandf();
    sp6C += (var_f24 * sind(sp60));
    sp68 += (var_f24 * cosd(sp60));
    sp70 = fn_1_27C4(var_r29, var_f29, temp_r31->unk38.y);
    HuAudFXPlay(0x587);

    for (;var_r29 != 0; var_r29--) {
        temp_r31->unk38.y += sp70;
        Hu3DModelRotSet(temp_r31->unk0, temp_r31->unk38.x, temp_r31->unk38.y, temp_r31->unk38.z);
        Hu3DModelRotSet(temp_r31->unk2, temp_r31->unk38.x, temp_r31->unk38.y, temp_r31->unk38.z);
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    Hu3DMotionShiftSet(temp_r31->unk0, temp_r31->unkC[4], 0.0f, 5.0f, 0);
    Hu3DMotionShiftSet(temp_r31->unk2, temp_r31->unk16[4], 0.0f, 5.0f, 0);
    HuPrcSleep(10);
    
    while (Hu3DMotionTimeGet(temp_r31->unk0) < 24.0f) {
        HuPrcVSleep();
    }
    Hu3DModelHookReset(temp_r31->unk0);
    Hu3DModelHookReset(temp_r31->unk2);
    HuAudFXPlay(0x586);
    temp_r30 = lbl_1_bss_278[var_r23];
    temp_r30->unk6 = var_r23;
    temp_r30->unkA = 0;
    var_r22 = HuPrcChildCreate(fn_1_2064, 0x1000, 0x3000, 0, HuPrcCurrentGet());
    var_r22->user_data = temp_r30;
    temp_r30->unkC = 1;
    temp_r30->unk0 = temp_r31->unk6;
    temp_r30->unk2 = temp_r31->unk8;
    temp_r30->unk4 = temp_r31->unkA;
    temp_r30->unk30 = 100.0f;
    temp_r30->unk10.x = -217.722f;
    temp_r30->unk10.y = 404.52f;
    temp_r30->unk10.z = 0.0f;
    var_f29 = fn_1_1D08(atan2d(temp_r30->unk10.x, temp_r30->unk10.z));
    var_f29 += temp_r31->unk38.y;
    var_f24 = sqrtf((temp_r30->unk10.x * temp_r30->unk10.x) + (temp_r30->unk10.z * temp_r30->unk10.z));
    temp_r30->unk10.x = (temp_r31->unk2C.x + (var_f24 * sind(var_f29)));
    temp_r30->unk10.y = (404.52f + temp_r31->unk2C.y) - 100.0f;
    temp_r30->unk10.z = (temp_r31->unk2C.z + (var_f24 * cosd(var_f29)));
    Hu3DModelPosSet(temp_r31->unk6, temp_r30->unk10.x, temp_r30->unk10.y, temp_r30->unk10.z);
    Hu3DModelPosSet(temp_r31->unk8, temp_r30->unk10.x, -temp_r30->unk10.y, temp_r30->unk10.z);
    HuSetVecF(&sp8C, temp_r31->unk2C.x, 0.0, temp_r31->unk2C.z);
    HuSetVecF(&sp80, sp6C, 0.0, sp68);
    HuSubVecF(&sp74, &sp8C, &sp80);
    var_f24 = sqrtf((sp74.x * sp74.x) + (sp74.z * sp74.z));
    sp54 = 1.0f;

    while (1) {
        for (var_r29 = 0, sp5C = temp_r30->unk10.y, sp58 = sp54; sp58 > 0.0f; var_r29++) {
            sp5C += sp58;
            sp58 -= 0.9f;
        }
        if (sp5C >= 600.0f) break;
        sp54++;
    }
    for (;sp5C > 0.0f; var_r29++) {
        sp5C += sp58;
        sp58 -= 0.9f;
    }
    temp_r30->unk24.z = sp54;
    temp_r30->unk24.x = fn_1_1D08(atan2d((sp6C - temp_r30->unk10.x), (sp68 - temp_r30->unk10.z)));
    temp_r30->unk24.y = var_f24 / var_r29;
    while (Hu3DMotionEndCheck(temp_r31->unk0) == 0) {
        HuPrcVSleep();
    }
    goto loop_1;
}

s8 fn_1_4BE4(s32 arg0, s32 arg1) {
    s8 var_r30;
    s8 var_r29;
    s8 var_r28;
    unkStruct3* temp_r31;

    temp_r31 = &lbl_1_bss_4D4[arg0];
    if (GWPlayerCfg[arg0].iscom == 0) {
        if (arg1 != 0) {
            var_r29 = var_r30 = HuPadStkY[temp_r31->unk2C];
        } else {
            var_r29 = var_r30 = HuPadStkX[temp_r31->unk2C];
        }

        (void)var_r30; // used to make the else branch go here instead of returning
    } else {
        if (arg1 != 0) {
            var_r28 = var_r30 = temp_r31->unk89;
        } else {
            var_r28 = var_r30 = temp_r31->unk88;
        }
    }
    return var_r30;
}

void fn_1_4C9C(Vec* arg0, f32 arg8, f32 arg9) {
    f32 temp_f29;
    
    temp_f29 = sqrtf((arg0->x * arg0->x) + (arg0->z * arg0->z));
    temp_f29 *= arg9;
    arg0->x = (temp_f29 * sind(arg8));
    arg0->z = (temp_f29 * cosd(arg8));
}

static inline f32 unkInline(void) {
    return 1.0f; // huh?
}

s8 fn_1_4E58(s32 arg0, s32 arg1) {
    Vec spC;
    f32 sp8;
    f32 temp_f28;
    f32 temp_f27;
    s8 var_r30;
    s8 temp_r29;
    s8 temp_r28;
    s8 var_r27;
    s8 var_r26;
    unkStruct3* temp_r31;

    temp_r31 = &lbl_1_bss_4D4[arg0];
    if (GWPlayerCfg[arg0].iscom == 0) {
        temp_r29 = HuPadStkX[temp_r31->unk2C];
        temp_r28 = HuPadStkY[temp_r31->unk2C];
        temp_f28 = fn_1_1D08(atan2d(temp_r29, temp_r28));
        temp_f28 -= lbl_1_bss_778;
        HuSetVecF(&spC, (f32)temp_r29, 0.0, (f32)temp_r28);
        temp_f27 = sqrtf((spC.x * spC.x) + (spC.z * spC.z));
        temp_f27 *= unkInline();
        spC.x = (temp_f27 * sind(temp_f28));
        spC.z = (temp_f27 * cosd(temp_f28));
        if (arg1 != 0) {
            var_r27 = var_r30 = spC.z;
        } else {
            var_r27 = var_r30 = spC.x;
        }

        (void)var_r30; // used to make the else branch go here instead of returning
    } else if (arg1 != 0) {
        var_r26 = var_r30 = temp_r31->unk89;
    } else {
        var_r26 = var_r30 = temp_r31->unk88;
    }
    return var_r30;
}

u8 fn_1_525C(s32 arg0, s32 arg1) {
    s8 var_r30;
    s8 var_r29;
    s8 var_r28;
    unkStruct3* temp_r31;

    temp_r31 = &lbl_1_bss_4D4[arg0];
    if (GWPlayerCfg[arg0].iscom == 0) {
        if (arg1 != 0) {
            var_r29 = var_r30 = HuPadTrigR[temp_r31->unk2C];
        } else {
            var_r29 = var_r30 = HuPadTrigL[temp_r31->unk2C];
        }

        (void)var_r30; // used to make the else branch go here instead of returning
    } else if (arg1 != 0) {
        var_r28 = var_r30 = temp_r31->unk8A;
    } else {
        var_r28 = var_r30 = temp_r31->unk8B;
    }
    return var_r30;
}

u16 fn_1_531C(s32 arg0) {
    u16 var_r30;
    unkStruct3* temp_r31;

    temp_r31 = &lbl_1_bss_4D4[arg0];
    if (GWPlayerCfg[arg0].iscom == 0) {
        var_r30 = HuPadBtnDown[temp_r31->unk2C];
    } else {
        var_r30 = temp_r31->unk8E;
    }
    return var_r30;
}

u16 fn_1_5388(s32 arg0) {
    u16 var_r30;
    unkStruct3* temp_r31;

    temp_r31 = &lbl_1_bss_4D4[arg0];
    if (GWPlayerCfg[arg0].iscom == 0) {
        var_r30 = HuPadBtn[temp_r31->unk2C];
    } else {
        var_r30 = temp_r31->unk8C;
    }
    return var_r30;
}

s32 fn_1_53F4(unkStruct3* arg0, f32 arg8, f32 arg9, f32 argA) {
    Vec sp30;
    Vec sp24;
    Vec sp18;
    f32 var_f27;
    f32 var_f28;
    s32 var_r28;
    s32 var_r30;
    unkStruct3* temp_r31;

    var_r28 = -1;
    var_r30 = 0;
    var_f28 = 10000.0f;
    
    for (;var_r30 < 4; var_r30++) {
        if (var_r30 != arg0->unk24) {
            temp_r31 = &lbl_1_bss_4D4[var_r30];
            HuSetVecF(&sp30, arg8, arg9, argA);
            HuSetVecF(&sp24, temp_r31->unk40.x, temp_r31->unk40.y, temp_r31->unk40.z);
            HuSubVecF(&sp18, &sp30, &sp24);
            var_f27 = sqrtf((sp18.z * sp18.z) + ((sp18.x * sp18.x) + (sp18.y * sp18.y)));
            if ((var_f27 < (arg0->unk60.x + temp_r31->unk60.x)) && (var_f27 < var_f28)) {
                var_f28 = var_f27;
                var_r28 = var_r30;
                arg0->unkA4 = 0;
            }
        }
    }
    return var_r28;
}

s32 fn_1_561C(unkStruct3* arg0, s32* arg1) {
    Vec sp24;
    Vec sp18;
    Vec spC;
    f32 var_f27;
    f32 var_f28;
    s32 var_r27;
    s32 var_r28;
    s32 var_r29;
    unkStruct3* temp_r30;

    var_r27 = -1;
    var_r29 = 0;
    var_f28 = 10000.0f;
    var_r28 = 0;
    
    for (;var_r29 < 4; var_r29++) {
        if (var_r29 != arg0->unk24) {
            temp_r30 = &lbl_1_bss_4D4[var_r29];
            HuSetVecF(&sp24, arg0->unk40.x, arg0->unk40.y, arg0->unk40.z);
            HuSetVecF(&sp18, temp_r30->unk40.x, temp_r30->unk40.y, temp_r30->unk40.z);
            HuSubVecF(&spC, &sp24, &sp18);
            var_f27 = sqrtf((spC.z * spC.z) + ((spC.x * spC.x) + (spC.y * spC.y)));
            if (var_f27 < (arg0->unk60.x + temp_r30->unk60.x)) {
                var_r28 += 1;
                if (var_f27 < var_f28) {
                    var_f28 = var_f27;
                    var_r27 = var_r29;
                    arg0->unkA4 = 0;
                }
            }
        }
    }
    *arg1 = var_r28;
    return var_r27;
}