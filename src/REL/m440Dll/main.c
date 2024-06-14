#include "REL/m440Dll.h"

#include "rel_sqrt_consts.h"
#include "math.h"
#include "game/frand.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/wipe.h"
#include "game/audio.h"
#include "game/objsub.h"
#include "game/minigame_seq.h"
#include "game/sprite.h"

// prototypes
void fn_1_33D4(omObjData* object);
void fn_1_3DD8(omObjData* object);
void fn_1_4660(omObjData* object);
u16 fn_1_4EA8(s32);
void fn_1_4EEC(s32, s32);
void fn_1_57B4(s32);
void fn_1_5C2C(s16, HsfObject*, unkStruct6*, s32);
f32 fn_1_93C0(f32, f32, f32);
unkStruct4* fn_1_942C(s16, Vec*, Vec*, f32, GXColor*);
s16 fn_1_956C(AnimData*, s32, f32, s32, s32);
void fn_1_9AB0(s16);
void fn_1_9B94(s16, m440Func5);
void fn_1_AE08(Process*);
// object.c
s16 fn_1_F0FC(void);
void fn_1_F168(void);

// bss
omObjData* lbl_1_bss_6C;
omObjData* lbl_1_bss_68;
s16 lbl_1_bss_10[10];
s16 lbl_1_bss_E;
u8 lbl_1_bss_C;
u8 lbl_1_bss_B;
u8 lbl_1_bss_A;
s16 lbl_1_bss_8;
s16 lbl_1_bss_6;
s16 lbl_1_bss_4;
s8 lbl_1_bss_2;
s8 lbl_1_bss_1;
s8 lbl_1_bss_0;

// data
f32 lbl_1_data_0[5] = { 90.0f, 80.0f, 100.0f, 70.0f, 110.0f };
Vec lbl_1_data_2C = { 800.0f, 1300.0f, 1000.0f };
Vec lbl_1_data_38 = { 0.0f, 0.0f, 0.0f };
GXColor lbl_1_data_44 = { 0xFF, 0xFF, 0xFF, 0xFF };
Vec lbl_1_data_48 = { 10.0f, 45.0f, 0.0f }; // UNUSED
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
    fn_1_9B94(lbl_1_bss_10[0], fn_1_2240);
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

s32 fn_1_1138(omObjData* object) {
    unkStruct2* sp8;
    f32 var_f31;
    f32 var_f30;
    s16 temp_r29;
    u8 var_r28;
    unkStruct3* temp_r30;
    unkStruct* var_r31;

    sp8 = (unkStruct2*)lbl_1_bss_6C->data;
    temp_r29 = fn_1_F0FC();
    temp_r30 = (unkStruct3*)lbl_1_bss_C0[temp_r29]->data;
    switch (lbl_1_bss_6) {
    case 0:
        if (lbl_1_bss_8 == 0) {
            Hu3DMotionShiftSet(lbl_1_bss_C0[temp_r29]->model[0], lbl_1_bss_C0[temp_r29]->motion[1], 0.0f, 7.0f, 0x40000001);
            temp_r30->unk40 = temp_r30->unk34;
        }
        lbl_1_bss_8++;
        var_f30 = lbl_1_bss_8 / 30.0f;
        if (var_f30 >= 1.0f) {
            var_f30 = 1.0f;
            if (lbl_1_bss_B == 0) {
                lbl_1_bss_B = 1;
                Hu3DMotionShiftSet(lbl_1_bss_C0[temp_r29]->model[0], lbl_1_bss_C0[temp_r29]->motion[0], 0.0f, 7.0f, 0x40000001);
            }
        }
        temp_r30->unk34 = (temp_r30->unk40 + (var_f30 * (360.0f - temp_r30->unk40)));
        var_r31 = &lbl_1_data_78[1]; // could be fn_1_6C8
        var_r28 = 0;
        lbl_1_bss_4++;
        var_f31 = lbl_1_bss_4 / 120.0f;
        if (var_f31 > 1.0f) {
            lbl_1_bss_4 = 0;
            var_f31 = 1.0f;
            var_r28 = 1;
        }
        var_f31 = (sin((M_PI * (90.0f * var_f31)) / 180.0) * sin((M_PI * (90.0f * var_f31)) / 180.0));
        CZoom = fn_1_93C0(var_r31[0].zoom, var_r31[1].zoom, var_f31);
        Center.x = fn_1_93C0(var_r31[0].center.x, var_r31[1].center.x, var_f31);
        Center.y = fn_1_93C0(var_r31[0].center.y, var_r31[1].center.y, var_f31);
        Center.z = fn_1_93C0(var_r31[0].center.z, var_r31[1].center.z, var_f31);
        CRot.x = fn_1_93C0(var_r31[0].rot.x, var_r31[1].rot.x, var_f31);
        CRot.y = fn_1_93C0(var_r31[0].rot.y, var_r31[1].rot.y, var_f31);
        CRot.z = fn_1_93C0(var_r31[0].rot.z, var_r31[1].rot.z, var_f31);
        if (var_r28 != 0) {
            lbl_1_bss_8 = 0;
            lbl_1_bss_6++;
        }
        break;
    case 1:
        Hu3DMotionShiftSet(lbl_1_bss_C0[temp_r29]->model[0], lbl_1_bss_C0[temp_r29]->motion[5], 0.0f, 7.0f, 0);
        HuAudSStreamPlay(1);
        lbl_1_bss_6++;
        lbl_1_bss_8 = 0;
        break;
    case 2:
        if (++lbl_1_bss_8 > 210.0f) {
            lbl_1_bss_6 = 0;
            return 1;
        }
        break;
    }
    return 0;
}

void fn_1_16D8(void) {
    unkStruct2* temp_r31;

    temp_r31 = (unkStruct2*)lbl_1_bss_6C->data;
    temp_r31->unk6--;
}

void fn_1_1708(void) {
    unkStruct2* temp_r31;

    temp_r31 = (unkStruct2*)lbl_1_bss_6C->data;
    if (temp_r31->unk8 != -1) {
        MGSeqParamSet(temp_r31->unk8, 2, -1);
        temp_r31->unk8 = -1;
        temp_r31->unk6 = 0;
    }
}

void fn_1_1768(void) {
    unkStruct2* temp_r31;

    temp_r31 = (unkStruct2*)lbl_1_bss_6C->data;
    if (temp_r31->unk8 == -1) {
        temp_r31->unk6 = 0x12C;
        temp_r31->unk8 = MGSeqCreate(1, 5, -1, -1);
    }
}

s16 fn_1_17CC(void) {
    unkStruct2* var_r31;

    var_r31 = (unkStruct2*)lbl_1_bss_6C->data;
    return var_r31->unk6;
}

s16 fn_1_17F4(void) {
    unkStruct2* var_r31;

    var_r31 = (unkStruct2*)lbl_1_bss_6C->data;
    return var_r31->unk8;
}

void fn_1_181C(void) {
    unkStruct2* temp_r31;

    temp_r31 = (unkStruct2*)lbl_1_bss_6C->data;
    if (temp_r31->unk4 == -1) {
        temp_r31->unk4 = MGSeqCreate(3, 0);
        MGSeqPosSet(temp_r31->unk4, 320.0f, 240.0f);
    }
}

u8 fn_1_1890(void) {
    unkStruct2* temp_r31;

    temp_r31 = (unkStruct2*)lbl_1_bss_6C->data;
    if (temp_r31->unk4 != -1) {
        return MGSeqStatGet(temp_r31->unk4);
    } else {
        return 0;
    }
}

void fn_1_18E0(void) {
    unkStruct2* temp_r31;

    temp_r31 = (unkStruct2*)lbl_1_bss_6C->data;
    temp_r31->unk4 = MGSeqCreate(3, 1);
    MGSeqPosSet(temp_r31->unk4, 320.0f, 240.0f);
    HuAudSeqFadeOut(temp_r31->unkC, 0x64);
}

s32 fn_1_1954(void) {
    unkStruct2* sp8;

    sp8 = (unkStruct2*)lbl_1_bss_6C->data;
    if ((lbl_1_bss_2 != 0) || (lbl_1_bss_1 != 0)) {
        return 0;
    } else {
        return 1;
    }
}

void fn_1_19B0(void) {
    f32 temp_f29;
    f32 var_f28;
    f32 var_f27;
    f32 temp_f31;
    f32 var_f30;
    s16 var_r31;

    var_f30 = (((rand8() << 8) | rand8()) % 361);
    
    for (var_r31 = 1; var_r31 < 4; var_r31++, var_f30+=120.0f) {
        temp_f31 = 0.01f * ((((rand8() << 8) | rand8()) % 51) + 50);
        temp_f29 = (temp_f31 * (200.0 * sin((M_PI * var_f30) / 180.0)));
        var_f28 = (temp_f31 * (200.0 * cos((M_PI * var_f30) / 180.0)));
        var_f27 = 0.0f;
        Hu3DModelPosSet(lbl_1_bss_10[var_r31], temp_f29, 300.0f + var_f28, var_f27);
        temp_f31 = 0.1f * ((((rand8() << 8) | rand8()) % 11) + 25);
        Hu3DModelScaleSet(lbl_1_bss_10[var_r31], temp_f31, temp_f31, temp_f31);
        Hu3DModelAttrReset(lbl_1_bss_10[var_r31], 1);
        Hu3DModelAttrReset(lbl_1_bss_10[var_r31], 0x40000002);
    }
}

void fn_1_1CAC(void) {
    s16 var_r31;
    
    for (var_r31 = 1; var_r31 < 4; var_r31++) {
        Hu3DMotionTimeSet(lbl_1_bss_10[var_r31], 0.0f);
        Hu3DModelAttrSet(lbl_1_bss_10[var_r31], 1);
        Hu3DModelAttrSet(lbl_1_bss_10[var_r31], 0x40000002);
    }
}

void fn_1_1D54(f32 arg8, f32 arg9, f32 argA, s16 arg0, f32 argB, s16 arg1) {
    Vec sp30;
    Vec sp24;
    GXColor sp1E;
    f32 temp_f30;
    f32 temp_f29;
    f32 temp_f31;
    s16 var_r30;
    unkStruct4* var_r31;
    
    for (var_r30 = 0; var_r30 < arg0; var_r30++) {
        temp_f31 = argB + ((((rand8() << 8) | rand8()) % 11) - 5);
        temp_f30 = sin((M_PI * temp_f31) / 180.0);
        temp_f29 = cos((M_PI * temp_f31) / 180.0);
        sp30.x = arg8 + ((((rand8() << 8) | rand8()) % 21) - 10);
        sp30.y = arg9 + ((((rand8() << 8) | rand8()) % 21) - 10);
        sp30.z = argA;
        sp24.x = sp24.y = sp24.z = 1.0f;
        sp1E.r = sp1E.g = sp1E.b = 0xFF;
        sp1E.a = 0x80;
        var_r31 = fn_1_942C(arg1, &sp30, &sp24, 0.0f, &sp1E);
        if (!var_r31) break;
        
        var_r31->unk34 = 0;
        var_r31->unk36 = ((rand8() << 8) | rand8()) % 2 + 2;
        var_r31->unk0.x = (temp_f30 * (0.1f * ((((rand8() << 8) | rand8()) % 41) + 0x28)));
        var_r31->unk0.y = (temp_f29 * (0.1f * ((((rand8() << 8) | rand8()) % 61) + 0x3C)));
        var_r31->unk0.z = 0.0f;
        var_r31->unk18 = (0.01f * var_r31->unk0.x);
        var_r31->unk1C = 0.1f;
        var_r31->unk24 = 1.5f;
        var_r31->unk28 = ((0.1f * ((((rand8() << 8) | rand8()) % 7) + 2)) / (var_r31->unk36 * 0xE));
        var_r31->unk2C = sp1E.a;
        var_r31->unk30 = (var_r31->unk2C / (var_r31->unk36 * 0xE));
    }
}

void fn_1_2240(omObjData* object, unkStruct5* arg1, Mtx* arg2) {
    unkStruct4* var_r31;
    GXColor* var_r30;
    s16 var_r29;

    var_r31 = arg1->unk18;
    var_r30 = arg1->unk24;
    
    for (var_r29 = 0; var_r29 < arg1->unk0; var_r29++, var_r31++, var_r30++) {
        if (var_r31->unk62 != 0) {
            var_r31->unk54.x += var_r31->unk0.x;
            var_r31->unk54.y += var_r31->unk0.y;
            var_r31->unk54.z += var_r31->unk0.z;
            var_r31->unk0.x -= var_r31->unk18;
            var_r31->unk0.y += var_r31->unk1C;
            var_r31->unk18 = (0.001f * var_r31->unk0.x);
            var_r31->unk1C *= 1.05f;
            var_r31->unk24 += var_r31->unk28;
            var_r31->unk48.x = var_r31->unk48.y = var_r31->unk48.z = var_r31->unk24;
            var_r31->unk2C -= var_r31->unk30;
            var_r30->a = var_r31->unk2C > 255.0f ? 255 : (u8)var_r31->unk2C;
            var_r31->unk34++;
            if (var_r31->unk34 >= var_r31->unk36) {
                var_r31->unk34 = 0;
                var_r31->unk60++;
            }
            if (var_r31->unk60 >= arg1->unk14 - 2) {
                var_r31->unk62 = 0;
            }
        }
    }
}

u16 fn_1_23E4(u16 arg0) {
    unkStruct2* temp_r31;

    temp_r31 = (unkStruct2*)lbl_1_bss_6C->data;
    if (!temp_r31) {
        return 0;
    }
    return temp_r31->unk0 & arg0;
}

void fn_1_2428(u16 arg0, u16 arg1) {
    unkStruct2* temp_r31;

    temp_r31 = (unkStruct2*)lbl_1_bss_6C->data;
    temp_r31->unk0 = (temp_r31->unk0 & ~arg0);
    temp_r31->unk0 = (temp_r31->unk0 | arg1);
}

void fn_1_2470(omObjData* arg0) {
    ModelData* temp_r29;
    HsfObject* temp_r28;
    f32 temp_f31;
    f32 var_f30;
    f32 var_f29;
    s16 temp_r26;
    s16 var_r30;
    unkStruct2* temp_r27;

    arg0->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0x34, 0x10000000);
    temp_r27 = arg0->data;
    arg0->stat |= 0x100;
    arg0->model[0] = Hu3DModelCreateFile(0x470008);
    arg0->model[1] = Hu3DModelCreateFile(0x470009);
    arg0->model[2] = Hu3DModelCreateFile(0x470000);
    arg0->model[3] = Hu3DModelCreateFile(0x470002);
    arg0->model[8] = Hu3DModelCreateFile(0x470003);
    arg0->model[6] = Hu3DModelCreateFile(0x470004);
    arg0->model[4] = Hu3DModelCreateFile(0x470005);
    arg0->model[5] = Hu3DModelCreateFile(0x470006);
    arg0->model[7] = Hu3DModelCreateFile(0x470007);
    temp_r26 = Hu3DModelCreateFile(0x470001);
    Hu3DModelAttrSet(arg0->model[0], 0x40000001);
    Hu3DModelAttrSet(arg0->model[2], 0x20000);
    Hu3DModelAttrSet(arg0->model[2], 0x40000002);
    Hu3DModelAttrSet(temp_r26, 1);
    
    for (var_r30 = 0; var_r30 < 8; var_r30++) {
        Hu3DModelLayerSet(arg0->model[var_r30], 1);
    }
    Hu3DModelPosSet(arg0->model[2], 0.0f, 5000.0f, 0.0f);
    Hu3DModelPosSet(arg0->model[3], 0.0f, 5000.0f, 0.0f);
    Hu3DModelShadowSet(arg0->model[2]);
    Hu3DModelShadowSet(arg0->model[3]);
    Hu3DModelShadowMapSet(arg0->model[0]);
    
    for (var_r30 = 0; var_r30 < 5; var_r30++) {
        temp_f31 = (450.0 * cos(M_PI * lbl_1_data_0[var_r30] / 180.0));
        var_f29 = (450.0 * sin(M_PI * lbl_1_data_0[var_r30] / 180.0));
        Hu3DModelPosSet(arg0->model[var_r30+4], temp_f31, 0.0f, var_f29);
        var_f30 = 90.0f - lbl_1_data_0[var_r30];
        Hu3DModelRotSet(arg0->model[var_r30+4], 0.0f, var_f30, 0.0f);
        Hu3DMotionSpeedSet(arg0->model[var_r30+4], 0.0f);
    }
    temp_r27->unk0 = 0;
    temp_r27->unk1C = 5;
    temp_r29 = &Hu3DData[temp_r26];
    temp_r28 = temp_r29->hsfData->root;
    lbl_1_bss_60 = temp_r28->data.childrenCount;
    lbl_1_bss_64 = HuMemDirectMalloc(HEAP_DATA, lbl_1_bss_60 * 64);
    OSReport("Koopa Object Count %d\n", temp_r29->hsfData->objectCnt);
    
    for (var_r30 = 0; var_r30 < lbl_1_bss_60; var_r30++) {
        lbl_1_bss_64[var_r30].unk20 = 0;
    }
    
    for (var_r30 = 0; var_r30 < lbl_1_bss_60; var_r30++) {
        lbl_1_bss_64[var_r30].unk4 = var_r30;
        fn_1_5C2C(temp_r26, temp_r28->data.children[var_r30], &lbl_1_bss_64[var_r30], 2);
        if (lbl_1_bss_64[var_r30].unk20 != 0) {
            Hu3DModelAttrSet(lbl_1_bss_64[var_r30].unk0, 1);
            Hu3DModelPosSet(lbl_1_bss_64[var_r30].unk0, 0.0f, 250.0f, 0.0f);
            lbl_1_bss_64[var_r30].unk38 = &fn_1_57B4;
        }
    }
    arg0->func = &fn_1_2A74;
}

void fn_1_2A74(omObjData* object) {
    fn_1_2AB4(object);
    fn_1_2CA8(object);
    fn_1_4660(object);
}

void fn_1_2AB4(omObjData* object) {
    unkStruct2* sp8;

    sp8 = (unkStruct2*)object->data;
    
    switch (fn_1_4EA8(0x20)) {
        case 0x20:
            fn_1_2B04(object);
    }
}

s16 lbl_1_data_E4[2] = {0, 0};
s16 lbl_1_data_E8[2] = {0, 0};
s16 lbl_1_data_EC[2] = {0, 0};
s16 lbl_1_data_F0[2] = {0, 0};

void fn_1_2B04(omObjData* object) {
    f32 temp_f31;
    unkStruct* temp_r31;

    temp_r31 = (unkStruct*)object->data;
    switch (lbl_1_data_E4[0]) {
        case 0:
            lbl_1_data_E8[0]++;
            temp_f31 = lbl_1_data_E8[0] / 360.0f;
            if (temp_f31 > 1.0f) {
                temp_f31 = 1.0f;
                Hu3DModelAttrSet(object->model[3], 1);
                lbl_1_data_E8[0] = 0;
                lbl_1_data_E4[0] = 0;
                fn_1_4EEC(0x20, 0);
                return;
            }
            temp_f31 = sin((M_PI * (90.0f * temp_f31)) / 180.0);
            temp_r31->center.y = (250.0f + (1750.0f * temp_f31));
    }
    Hu3DModelPosSet(object->model[3], temp_r31->center.x, temp_r31->center.y, temp_r31->center.z);
    Hu3DModelRotSet(object->model[3], temp_r31->rot.x, temp_r31->rot.y, temp_r31->rot.z);
}

void fn_1_2CA8(omObjData* arg0) {
    unkStruct2* sp8;

    sp8 = (unkStruct2*)arg0->data;
    
    switch (fn_1_4EA8(7)) {
        case 1:
            fn_1_2D28(arg0);
            break;
        case 3:
            fn_1_33D4(arg0);
            break;
        case 4:
        case 5:
            fn_1_3DD8(arg0);
    }
}

void fn_1_2D28(omObjData* object) {
    f32 var_f31;
    unkStruct* temp_r31;

    temp_r31 = (unkStruct*)object->data;
    switch (lbl_1_data_EC[0]) {
        case 0x0:
            temp_r31->center.x = temp_r31->center.z = 0.0f;
            temp_r31->center.y = 2000.0f;
            temp_r31->rot.x = temp_r31->rot.y = temp_r31->rot.z = 0.0f;
            Hu3DModelAttrReset(object->model[2], 1);
            Hu3DModelAttrReset(object->model[3], 1);
            Hu3DModelAttrSet(object->model[3], 0x40000002);
            Hu3DMotionTimeSet(object->model[3], 0.0f);
            lbl_1_data_EC[0] ++;
            lbl_1_data_F0[0] = 0;
            HuAudFXPlay(0x709);
            HuAudFXPlay(0x711);
            break;
        case 0x1:
            lbl_1_data_F0[0] ++;
            var_f31 = lbl_1_data_F0[0] / 120.0f;
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
                lbl_1_data_F0[0] = 0;
                lbl_1_data_F0[1] = 0xF;
                lbl_1_data_EC[1] = (lbl_1_data_EC[0] + 1);
                lbl_1_data_EC[0] = 0x63;
            }
            if (110.0f == lbl_1_data_F0[0]) {
                HuAudFXPlay(0x70A);
            }
            var_f31 = sin((M_PI * (90.0f * var_f31)) / 180.0);
            temp_r31->center.y = (2000.0f + (-1750.0f * var_f31));
            break;
        case 0x2:
            if (lbl_1_data_F0[0] == 0) {
                HuAudFXPlay(0x713);
            }
            lbl_1_data_F0[0] ++;
            var_f31 = lbl_1_data_F0[0] / 60.0f;
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
                lbl_1_data_F0[0] = 0;
                lbl_1_data_F0[1] = 0xF;
                lbl_1_data_EC[1] = lbl_1_data_EC[0] + 1;
                lbl_1_data_EC[0] = 0x63;
                HuAudFXPlay(0x714);
            }
            temp_r31->rot.y = (360.0f * var_f31);
            break;
        case 0x3:
            Hu3DModelAttrReset(object->model[3], 0x40000002);
            Hu3DMotionSpeedSet(object->model[3], 2.0f);
            if (lbl_1_data_F0[0] == 0) {
                HuAudFXPlay(0x711);
            }
            if (++lbl_1_data_F0[0] > 12.0) {
                if (fn_1_4EA8(0x40) != 0) {
                    fn_1_4EEC(0x40, 0);
                    fn_1_F228();
                }
                fn_1_4EEC(0x20, 0x20);
                fn_1_4EEC(7, 2);
                lbl_1_data_F0[0] = 0;
                lbl_1_data_EC[0] = 0;
            }
            break;
        case 0x4:
            lbl_1_data_F0[0]++;
            var_f31 = lbl_1_data_F0[0] / 360.0f;
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
                Hu3DModelAttrSet(object->model[3], 1);
                lbl_1_data_F0[0] = 0;
                lbl_1_data_EC[0] = 0;
                fn_1_4EEC(7, 2);
                return;
            }
            var_f31 = sin((M_PI * (90.0f * var_f31)) / 180.0);
            temp_r31->center.y = (250.0f + (1750.0f * var_f31));
            break;
        case 0x63:
            if (++lbl_1_data_F0[0] > lbl_1_data_F0[1]) {
                lbl_1_data_F0[0] = 0;
                lbl_1_data_EC[0] = lbl_1_data_EC[1];
            }
            break;
    }
    Hu3DModelPosSet(object->model[3], temp_r31->center.x, temp_r31->center.y, temp_r31->center.z);
    Hu3DModelRotSet(object->model[3], temp_r31->rot.x, temp_r31->rot.y, temp_r31->rot.z);
    Hu3DModelPosSet(object->model[2], temp_r31->center.x, temp_r31->center.y, temp_r31->center.z);
    Hu3DModelRotSet(object->model[2], temp_r31->rot.x, temp_r31->rot.y, temp_r31->rot.z);
    return;
}