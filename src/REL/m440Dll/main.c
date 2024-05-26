#include "REL/m440Dll.h"

#include "rel_sqrt_consts.h"
#include "math.h"
#include "game/frand.h"
#include "game/hsfman.h"
#include "game/wipe.h"
#include "game/audio.h"
#include "game/objsub.h"
#include "game/minigame_seq.h"
#include "game/sprite.h"

// prototypes
void fn_1_3C4(omObjData* object);
void fn_1_434(omObjData* object);
s32 fn_1_4A4(void);
s32 fn_1_6C8(void);
void fn_1_8F0(omObjData* object);
void fn_1_AE0(omObjData* object);
s32 fn_1_E14(omObjData* object);
// ...
u8 fn_1_1138(omObjData* object);
void fn_1_2240(omObjData* object);
u16 fn_1_23E4(s32);
void fn_1_2428(s32, s32);
void fn_1_2470(omObjData* object);
void fn_1_4EEC(s32, s32);
f32 fn_1_93C0(f32, f32, f32);
s16 fn_1_956C(AnimData*, s32, f32, s32, s32);
void fn_1_9AB0(s16);
void fn_1_9B94(s16, omObjFunc);
void fn_1_AE08(Process*);
// object.c
void fn_1_F168(void);

// bss
omObjData* lbl_1_bss_6C;
omObjData* lbl_1_bss_68;
s16 lbl_1_bss_10[10];
s16 lbl_1_bss_E;
u8 lbl_1_bss_B;
u8 lbl_1_bss_A;
s16 lbl_1_bss_8;
s16 lbl_1_bss_6;
s16 lbl_1_bss_4;
s8 lbl_1_bss_2;
s8 lbl_1_bss_0;

// data
Vec lbl_1_data_2C = { 800.0f, 1300.0f, 1000.0f };
Vec lbl_1_data_38 = { 0.0f, 0.0f, 0.0f };
GXColor lbl_1_data_44 = { 0xFF, 0xFF, 0xFF, 0xFF };
Vec lbl_1_data_54 = { 1300.0f, 2500.0f, 1300.0f };
Vec lbl_1_data_60 = { 0.0f, 1.0f, 0.0f };
Vec lbl_1_data_6C = { 0.0f, 0.0f, -500.0f };
unkStruct lbl_1_data_78[3] = {
    { 1450.0f, { 0.0f, 452.0f, 0.0f }, { 11.0f, -23.0f, 0.0f } },
    { 1700.0f, { 0.0f, 315.0f, 0.0f }, { -2.0f, 0.0f, 0.0f } },
    { 1040.0f, { 200.0f, 21.0f, 0.0f }, { -6.0f, 0.0f, 0.0f } },
};

void ModuleProlog(void) {
    Vec sp8;
    LightData* var_r30;
    Process* var_r31;

    Hu3DLightAllKill();
    lbl_1_bss_E = Hu3DGLightCreateV(&lbl_1_data_2C, &lbl_1_data_38, &lbl_1_data_44);
    Hu3DGLightInfinitytSet(lbl_1_bss_E);
    var_r30 = &Hu3DGlobalLight[lbl_1_bss_E];
    var_r30->unk_00 |= 0x8000;
    sp8.x = sp8.y = sp8.z = 0.0f;
    Hu3DGLightPosAimSetV(lbl_1_bss_E, &lbl_1_data_2C, &sp8);
    Hu3DShadowCreate(45.0f, 20.0f, 10000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&lbl_1_data_54, &lbl_1_data_60, &lbl_1_data_6C);
    HuAudSndGrpSet(0x42);
    var_r31 = omInitObjMan(0x32, 0x2000);
    omGameSysInit(var_r31);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 41.5f, 5.0f, 5000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    omAddObjEx(var_r31, 0x7FDA, 0, 0, -1, omOutView);
    CRot.x = lbl_1_data_78[0].rot.x;
    CRot.y = lbl_1_data_78[0].rot.y;
    CRot.z = lbl_1_data_78[0].rot.z;
    Center.x = lbl_1_data_78[0].center.x;
    Center.y = lbl_1_data_78[0].center.y;
    Center.z = lbl_1_data_78[0].center.z;
    CZoom = lbl_1_data_78[0].zoom;
    omAddObjEx(var_r31, 0x3E8, 0, 0, -1, fn_1_3C4);
    lbl_1_bss_6C = omAddObjEx(var_r31, 10, 9, 0, -1, fn_1_8F0);
    lbl_1_bss_68 = omAddObjEx(var_r31, 50, 9, 9, -1, fn_1_2470);
    Hu3DBGColorSet(0, 0, 0);
    fn_1_AE08(var_r31);
}

void fn_1_3C4(omObjData* object) {
    if ((omSysExitReq != 0) || (lbl_1_bss_0 != 0)) {
        WipeCreate(2, 0, 0x3C);
        object->func = &fn_1_434;
    }
}

void fn_1_434(omObjData* object) {
    if ((WipeStatGet() == 0) && (MGSeqDoneCheck() != 0)) {
        HuMemDirectFree(lbl_1_bss_64);
        fn_1_9AB0(lbl_1_bss_10[0]);
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

s32 fn_1_4A4(void) {
    f32 var_f31;
    unkStruct *var_r31;
    s32 var_r30;

    var_r31 = &lbl_1_data_78[0];
    var_r30 = 0;
    lbl_1_bss_4++;
    var_f31 = lbl_1_bss_4 / 120.0f;
    if (var_f31 > 1.0f) {
        lbl_1_bss_4 = 0;
        var_f31 = 1.0f;
        var_r30 = 1;
    }
    
    var_f31 = (sin((M_PI * (90.0f * var_f31)) / 180.0) * sin((M_PI * (90.0f * var_f31)) / 180.0));
    CZoom = fn_1_93C0(var_r31[0].zoom, var_r31[1].zoom, var_f31);
    Center.x = fn_1_93C0(var_r31[0].center.x, var_r31[1].center.x, var_f31);
    Center.y = fn_1_93C0(var_r31[0].center.y, var_r31[1].center.y, var_f31);
    Center.z = fn_1_93C0(var_r31[0].center.z, var_r31[1].center.z, var_f31);
    CRot.x = fn_1_93C0(var_r31[0].rot.x, var_r31[1].rot.x, var_f31);
    CRot.y = fn_1_93C0(var_r31[0].rot.y, var_r31[1].rot.y, var_f31);
    CRot.z = fn_1_93C0(var_r31[0].rot.z, var_r31[1].rot.z, var_f31);
    return var_r30;
}

s32 fn_1_6C8(void) {
    f32 var_f31;
    unkStruct *var_r31;
    s32 var_r30;

    var_r31 = &lbl_1_data_78[1];
    var_r30 = 0;
    lbl_1_bss_4++;
    var_f31 = lbl_1_bss_4 / 120.0f;
    if (var_f31 > 1.0f) {
        lbl_1_bss_4 = 0;
        var_f31 = 1.0f;
        var_r30 = 1;
    }
    
    var_f31 = (sin((M_PI * (90.0f * var_f31)) / 180.0) * sin((M_PI * (90.0f * var_f31)) / 180.0));
    CZoom = fn_1_93C0(var_r31[0].zoom, var_r31[1].zoom, var_f31);
    Center.x = fn_1_93C0(var_r31[0].center.x, var_r31[1].center.x, var_f31);
    Center.y = fn_1_93C0(var_r31[0].center.y, var_r31[1].center.y, var_f31);
    Center.z = fn_1_93C0(var_r31[0].center.z, var_r31[1].center.z, var_f31);
    CRot.x = fn_1_93C0(var_r31[0].rot.x, var_r31[1].rot.x, var_f31);
    CRot.y = fn_1_93C0(var_r31[0].rot.y, var_r31[1].rot.y, var_f31);
    CRot.z = fn_1_93C0(var_r31[0].rot.z, var_r31[1].rot.z, var_f31);
    return var_r30;
}

void fn_1_8F0(omObjData* arg0) {
    s16 var_r30;
    unkStruct2* temp_r31;
    AnimData *anim;

    arg0->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0x10, 0x10000000);
    temp_r31 = (unkStruct2*)arg0->data;
    temp_r31->unk0 = 1;
    temp_r31->unk4 = -1;
    temp_r31->unk8 = -1;
    temp_r31->unk6 = 0x12C;
    temp_r31->unkA = 0;
    temp_r31->unkC = -1;
    
    for (var_r30 = 1; var_r30 < 4; var_r30++) {
        lbl_1_bss_10[var_r30] = Hu3DModelCreate(HuDataSelHeapReadNum(0x47000A, 0x10000000, HEAP_DATA));
        Hu3DModelAttrSet(lbl_1_bss_10[var_r30], 1);
        Hu3DModelAttrSet(lbl_1_bss_10[var_r30], 0x40000002);
        Hu3DModelLayerSet(lbl_1_bss_10[var_r30], 7);
        Hu3DModelScaleSet(lbl_1_bss_10[var_r30], 3.0f, 3.0f, 3.0f);
    }
    
    anim = HuSprAnimRead(HuDataReadNum(0x47000B, 0x10000000));
    lbl_1_bss_10[0] = fn_1_956C(anim, 0x40, 50.0f, 0x40, 0x40);
    fn_1_9B94(lbl_1_bss_10[0], &fn_1_2240);
    Hu3DModelLayerSet(lbl_1_bss_10[0], 7);
    arg0->func = &fn_1_AE0;
}

void fn_1_AE0(omObjData* arg0) {
    f32 temp_f31;
    unkStruct2* temp_r31;

    temp_r31 = arg0->data;
    switch (fn_1_23E4(7)) {
        case 1:
            if (lbl_1_bss_A == 0) {
                WipeCreate(1, 0, 0x3C);
                lbl_1_bss_A = 1;
            }
            if (WipeStatGet() != 0) break;
            fn_1_2428(7, 2);
            break;
        case 2:
            if (fn_1_E14(arg0) != 0) {
                fn_1_2428(7, 3);
            }
            break;
        case 3:
            if (temp_r31->unk8 != -1) {
                MGSeqParamSet(temp_r31->unk8, 1, ((temp_r31->unk6 + 0x3B) / 60));
            }
            if ((temp_r31->unkC < 0) && ((MGSeqStatGet(temp_r31->unk4) & 0x10) != 0)) {
                temp_r31->unkC = HuAudSeqPlay(0x49);
            }
            if (lbl_1_bss_2 == 0) {
                if (temp_r31->unkA != 0) {
                    temp_r31->unkA++;
                    temp_f31 = (((rand8() << 8) | rand8()) % 361);
                    Center.x = (lbl_1_data_78[1].center.x + (10.0 * sin((M_PI * temp_f31) / 180.0)));
                    Center.y = (lbl_1_data_78[1].center.y + (10.0 * cos((M_PI * temp_f31) / 180.0)));
                    if (temp_r31->unkA > 0x28) {
                        temp_r31->unkA = 0;
                        return;
                    }
                } else {
                    Center.x = lbl_1_data_78[1].center.x;
                    Center.y = lbl_1_data_78[1].center.y;
                    Center.z = lbl_1_data_78[1].center.z;
                    return;
                }
            }
            break;
        case 4:
            if (fn_1_1138(arg0) != 0) {
                fn_1_2428(7, 5);
                return;
            }
            break;
        case 5:
            lbl_1_bss_0 = 1;
            break;
    }
}

s32 fn_1_E14(omObjData* arg0) {
    f32 var_f31;
    unkStruct* var_r31;
    u8 var_r30;

    switch (lbl_1_bss_6) {
        case 0:
            fn_1_4EEC(7, 1);
            fn_1_4EEC(0x18, 8);
            HuAudFXPlay(0x70E);
            lbl_1_bss_6++;
            break;
        case 1:
            if (++lbl_1_bss_8 > 0x1E) {
                fn_1_F168();
                lbl_1_bss_8 = 0;
                lbl_1_bss_6++;
            }
            break;
        case 2:
            var_r31 = lbl_1_data_78;
            var_r30 = 0;
            lbl_1_bss_4++;
            var_f31 = lbl_1_bss_4 / 120.0f;
            if (var_f31 > 1.0f) {
                lbl_1_bss_4 = 0;
                var_f31 = 1.0f;
                var_r30 = 1;
            }
            var_f31 = (sin((M_PI * (90.0f * var_f31)) / 180.0) * sin((M_PI * (90.0f * var_f31)) / 180.0));
            CZoom = fn_1_93C0(var_r31[0].zoom, var_r31[1].zoom, var_f31);
            Center.x = fn_1_93C0(var_r31[0].center.x, var_r31[1].center.x, var_f31);
            Center.y = fn_1_93C0(var_r31[0].center.y, var_r31[1].center.y, var_f31);
            Center.z = fn_1_93C0(var_r31[0].center.z, var_r31[1].center.z, var_f31);
            CRot.x = fn_1_93C0(var_r31[0].rot.x, var_r31[1].rot.x, var_f31);
            CRot.y = fn_1_93C0(var_r31[0].rot.y, var_r31[1].rot.y, var_f31);
            CRot.z = fn_1_93C0(var_r31[0].rot.z, var_r31[1].rot.z, var_f31);
            if (var_r30 != 0) {
                lbl_1_bss_8 = 0;
                lbl_1_bss_6 = 0;
                return 1;
            }
            break;
    }
    return 0;
}