#include "REL/m409Dll.h"

#include "rel_sqrt_consts.h"
#include "math.h"
#include "game/hsfman.h"
#include "game/objsub.h"
#include "game/audio.h"
#include "game/wipe.h"
#include "game/minigame_seq.h"
#include "game/sprite.h"
#include "game/pad.h"
#include "game/hsfmotion.h"
#include "game/gamework_data.h"

// bss
Process* lbl_1_bss_E8;
s16 lbl_1_bss_E4;
omObjData* lbl_1_bss_E0;
omObjData* lbl_1_bss_DC;
unkStruct3 lbl_1_bss_24;
s8 lbl_1_bss_14;
f32 lbl_1_bss_10;
f32 lbl_1_bss_C;
s8 lbl_1_bss_A;
s16 lbl_1_bss_8;
s8 lbl_1_bss_6;
s16 lbl_1_bss_4;
s16 lbl_1_bss_2;
s8 lbl_1_bss_0;

// data
Vec lbl_1_data_0 = { 800.0f, 1300.0f, 1000.0f };
Vec lbl_1_data_C = { 0.0f, 0.0f, 0.0f };
unkStruct2 lbl_1_data_18 = {
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 10.0f, 45.0f, 0.0f }
};
Vec lbl_1_data_28 = { 1300.0f, 2500.0f, 1300.0f };
Vec lbl_1_data_34 = { 0.0f, 1.0f, 0.0f };
Vec lbl_1_data_40 = { 0.0f, 0.0f, -1200.0f };
unkStruct lbl_1_data_4C[4] = {
    { 469.8f, { 225.0f, 184.0f, -1358.0f }, { 10.62f, -109.0f, 0.0f } },
    { 1800.0f, { 0.0f, 300.0f, -1316.0f }, { -20.38f, 0.0f, 0.0f } },
    { 2209.82f, { 0.0f, 478.0f, -1316.0f }, { 4.62f, 0.0f, 0.0f } },
    { 2059.82f, { 0.0f, 528.0f, -1316.0f }, { 10.62f, 0.0f, 0.0f } }
};
u32 lbl_1_data_BC = 0xFFFFFFFF;
s32 lbl_1_data_C0 = -1;


void ObjectSetup(void) {
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    LightData* temp_r31;

    Hu3DLightAllKill();
    lbl_1_bss_E4 = Hu3DGLightCreateV(&lbl_1_data_0, &lbl_1_data_C, &lbl_1_data_18.unk0);
    Hu3DGLightInfinitytSet(lbl_1_bss_E4);
    temp_r31 = &Hu3DGlobalLight[lbl_1_bss_E4];
    temp_r31->unk_00 |= 0x8000;
    sp2C.x = sp2C.y = sp2C.z = 0.0f;
    Hu3DGLightPosAimSetV(lbl_1_bss_E4, &lbl_1_data_0, &sp2C);
    Hu3DShadowCreate(45.0f, 20.0f, 10000.0f);
    Hu3DShadowTPLvlSet(0.8f);
    Hu3DShadowPosSet(&lbl_1_data_28, &lbl_1_data_34, &lbl_1_data_40);
    lbl_1_bss_E8 = omInitObjMan(0x32, 0x2000);
    omGameSysInit(lbl_1_bss_E8);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 41.5f, 5.0f, 5000.0f, 1.2f);
    omAddObjEx(lbl_1_bss_E8, 0x7FDA, 0U, 0U, -1, omOutView);
    sp14.x = 0.0f;
    sp14.y = 374.0f;
    sp14.z = 1086.0f;
    sp20.x = 0.0f;
    sp20.y = 568.0f;
    sp20.z = -1316.0f;
    sp8.z = sp20.x - sp14.x;
    sp8.y = sp20.y - sp14.y;
    sp8.x = sp20.z - sp14.z;
    CRot.x = lbl_1_data_4C[0].rot.x;
    CRot.y = lbl_1_data_4C[0].rot.y;
    CRot.z = lbl_1_data_4C[0].rot.z;
    Center.x = lbl_1_data_4C[0].center.x;
    Center.y = lbl_1_data_4C[0].center.y;
    Center.z = lbl_1_data_4C[0].center.z;
    CZoom = lbl_1_data_4C[0].zoom;
    omAddObjEx(lbl_1_bss_E8, 0x3E8, 0, 0, -1, fn_1_434);
    lbl_1_bss_E0 = omAddObjEx(lbl_1_bss_E8, 0xA, 3U, 0U, -1, fn_1_DDC);
    lbl_1_bss_DC = omAddObjEx(lbl_1_bss_E8, 0x32, 7U, 0U, -1, fn_1_2484);
    Hu3DBGColorSet(0, 0, 0);
    HuAudSndGrpSet(0x22);
    fn_1_67E0(lbl_1_bss_E8);
}

void fn_1_434(omObjData* object) {
    if ((omSysExitReq != 0) || (lbl_1_bss_0 != 0)) {
        HuAudFXListnerKill();
        fn_1_5F5C(lbl_1_bss_E0->model[0]);
        fn_1_5F5C(lbl_1_bss_E0->model[1]);
        WipeCreate(2, 0, 0x3C);
        MGSeqKillAll();
        object->func = fn_1_4DC;
    }
}

void fn_1_4DC(omObjData* object) {
    if ((WipeStatGet() == 0) && (MGSeqDoneCheck() != 0)) {
        fn_1_6900();
        omOvlReturnEx(1, 1);
    }
}

s8 fn_1_524(void) {
    Vec sp8;
    f32 temp_f29;
    f32 var_f30;
    f32 temp_f31;
    s8 var_r30;
    unkStruct* var_r31;

    var_r31 = lbl_1_data_4C;
    var_r30 = 0;
    if (++lbl_1_bss_2 > 0x12C) {
        lbl_1_bss_2 = 0x12C;
        var_r30 = 1;
    }
    var_f30 = lbl_1_bss_2 / 300.0f;
    temp_f31 = (sin((M_PI * (90.0f * var_f30)) / 180.0) * sin((M_PI * (90.0f * var_f30)) / 180.0));
    CZoom = fn_1_4120(var_r31[0].zoom, var_r31[1].zoom, var_r31[2].zoom, temp_f31);
    Center.x = fn_1_4120(var_r31[0].center.x, var_r31[1].center.x, var_r31[2].center.x, temp_f31);
    Center.y = fn_1_4120(var_r31[0].center.y, var_r31[1].center.y, var_r31[2].center.y, temp_f31);
    Center.z = fn_1_4120(var_r31[0].center.z, var_r31[1].center.z, var_r31[2].center.z, temp_f31);
    CRot.x = fn_1_4120(var_r31[0].rot.x, var_r31[1].rot.x, var_r31[2].rot.x, temp_f31);
    CRot.y = fn_1_4120(var_r31[0].rot.y, var_r31[1].rot.y, var_r31[2].rot.y, temp_f31);
    CRot.z = fn_1_4120(var_r31[0].rot.z, var_r31[1].rot.z, var_r31[2].rot.z, temp_f31);
    if (var_f30 > 0.65f) {
        Hu3DModelAttrSet(lbl_1_bss_DC->model[1], 1U);
    }
    temp_f29 = var_r31[0].rot.x + (-var_r31[0].rot.x * temp_f31);
    Hu3DModelRotSet(lbl_1_bss_DC->model[2], 0.2f * temp_f29, 0.85f * CRot.y, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_DC->model[3], 0.2f * temp_f29, 0.85f * CRot.y, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_DC->model[6], 0.2f * temp_f29, 0.85f * CRot.y, 0.0f);
    var_f30 *= 1.2f;
    if (var_f30 > 1.0f) {
        var_f30 = 1.0f;
    }
    temp_f31 = cos((M_PI * (-45.0f + (135.0f * var_f30))) / 180.0);
    Hu3DTexScrollPosSet(lbl_1_bss_24.unk12, lbl_1_bss_24.unk14, 0.0f, 0.0f);
    lbl_1_bss_24.unk14 -= 0.01f * temp_f31;
    Hu3DTexScrollPosMoveSet(lbl_1_bss_24.unkC, -0.0001f - (0.005f * temp_f31), 0.0f, 0.0f);
    Hu3DTexScrollPosMoveSet(lbl_1_bss_24.unkE, -0.0002f - (0.005f * temp_f31), 0.0f, 0.0f);
    Hu3DTexScrollPosMoveSet(lbl_1_bss_24.unk10, -0.0003f - (0.005f * temp_f31), 0.0f, 0.0f);
    sp8.x = -(sin((M_PI * CRot.y) / 180.0) * cos((M_PI * CRot.x) / 180.0));
    sp8.y = sin((M_PI * CRot.x) / 180.0);
    sp8.z = -(cos((M_PI * CRot.y) / 180.0) * cos((M_PI * CRot.x) / 180.0));
    HuAudFXListnerUpdate(&Hu3DCamera->pos, &sp8);
    return var_r30;
}

s8 fn_1_B80(void) {
    f32 temp_f30;
    f32 temp_f31;
    s8 var_r30;
    unkStruct* var_r31;

    var_r31 = &lbl_1_data_4C[2];
    var_r30 = 0;
    if (++lbl_1_bss_4 > 0x3C) {
        lbl_1_bss_4 = 0x3C;
        var_r30 = 1;
    }
    temp_f30 = lbl_1_bss_4 / 60.0f;
    temp_f31 = (sin((M_PI * (90.0f * temp_f30)) / 180.0) * sin((M_PI * (90.0f * temp_f30)) / 180.0));
    CZoom = var_r31[0].zoom + (temp_f31 * (var_r31[1].zoom - var_r31[0].zoom));
    Center.x = var_r31[0].center.x + (temp_f31 * (var_r31[1].center.x - var_r31[0].center.x));
    Center.y = var_r31[0].center.y + (temp_f31 * (var_r31[1].center.y - var_r31[0].center.y));
    Center.z = var_r31[0].center.z + (temp_f31 * (var_r31[1].center.z - var_r31[0].center.z));
    CRot.x = var_r31[0].rot.x + (temp_f31 * (var_r31[1].rot.x - var_r31[0].rot.x));
    CRot.y = var_r31[0].rot.y + (temp_f31 * (var_r31[1].rot.y - var_r31[0].rot.y));
    CRot.z = var_r31[0].rot.z + (temp_f31 * (var_r31[1].rot.z - var_r31[0].rot.z));
    return var_r30;
}

void fn_1_DDC(omObjData* object) {
    s16* var_r29;
    AnimData* var_r30;
    
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, 6, 0x10000000);
    var_r29 = (s16*)object->data;
    var_r29[0] = 1;
    var_r30 = HuSprAnimRead(HuDataReadNum(0x28000D, 0x10000000));
    object->model[0] = fn_1_5A18(var_r30, 0x800, 10.0f, 0x40, 0x40);
    fn_1_5FBC(object->model[0], fn_1_5408);
    Hu3DModelLayerSet(object->model[0], 5);
    var_r30 = HuSprAnimRead(HuDataReadNum(0x28000E, 0x10000000));
    object->model[1] = fn_1_5A18(var_r30, 0x400, 2.0f, 0, 0);
    fn_1_5FBC(object->model[1], fn_1_55E0);
    fn_1_5FF4(object->model[1], 1);
    Hu3DModelLayerSet(object->model[1], 5);
    HuAudFXListnerSetEX(&Hu3DCamera->pos, &Hu3DCamera->up, 10000.0f, 566.6667f, 0.0f, 300.0f, 300.0f);
    object->func = fn_1_F70;
}

void fn_1_F70(omObjData* object) {
    s16* sp8;
    s16 temp_r3;
    s16 temp_r3_2;
    s32 var_r31;

    sp8 = (s16*)object->data;
    switch (fn_1_2454(7)) {
        case 1:
            if (lbl_1_bss_6 == 0) {
                lbl_1_bss_6 = 1;
                WipeCreate(1, 0, 0x3C);
            }
            if (WipeStatGet() == 0) {
                fn_1_2414(7, 2);
                
                for (var_r31 = 0; var_r31 < 4; var_r31++) {
                    omVibrate(var_r31, 0xC8, 6, 6);
                }
            }
            break;
        case 2:
            if (fn_1_10E8(object) != 0) {
                fn_1_2414(7, 3);
            }
            break;
        case 3:
            switch (fn_1_2454(0x60)) {
                case 0x40:
                    break;
                case 0x20:
                    fn_1_2098(object);
                    break;
            }
            break;
        case 4:
            if (fn_1_1B74(object) != 0) {
                fn_1_2414(7, 5);
                return;
            }
            break;
        case 5:
            lbl_1_bss_0 = 1;
            break;
    }
}

s8 fn_1_10E8(omObjData* object) {
    Vec sp8;
    ModelData* temp_r31;
    f32 temp_f1;
    f32 var_f26;
    f32 var_f27;
    f32 temp_f29;
    f32 temp_f28;
    f32 temp_f30;
    f32 var_f31;
    s8 var_r29;
    u8 temp_r0;
    unkStruct3* temp_r30;

    temp_r31 = &Hu3DData[lbl_1_bss_DC->model[4]];
    temp_r30 = (unkStruct3*)object->data;
    if (lbl_1_bss_A != 0) {
        var_r29 = fn_1_524();
    }
    switch (lbl_1_bss_8) {                    /* irregular */
        case -1:
            if ((HuPadBtnDown[0] & 0x100) != 0) {
                lbl_1_bss_8 = 0;
            }
            break;
        case 0:
            Hu3DModelAttrReset(lbl_1_bss_DC->model[1], 0x40000002);
            if (lbl_1_bss_C == 0.0f) {
                fn_1_3840();
                sp8.x = 1520.0f;
                sp8.y = 0.0f;
                sp8.z = -1200.0f;
                lbl_1_data_BC = HuAudFXEmiterPlay(0x554, &sp8);
                HuAudFXEmiterPlay(0x559, &sp8);
            }
            lbl_1_bss_C += 0.004f;
            if (lbl_1_bss_C >= 1.0f) {
                lbl_1_bss_C = 1.0f;
                lbl_1_bss_8 = 0x63;
            } else if (lbl_1_bss_C > 0.2f) {
                lbl_1_bss_A = 1;
            }
            var_f31 = sin((M_PI * (90.0f * lbl_1_bss_C)) / 180.0);
            var_f27 = 1520.0f;
            var_f26 = -1030.0f;
            temp_f30 = var_f27 + (var_f31 * (var_f26 - var_f27));
            Hu3DModelPosSet(lbl_1_bss_DC->model[4], temp_f30, 0.0f, -1200.0f);
            Hu3DModelPosSet(lbl_1_bss_DC->model[1], temp_f30, 0.0f, -1200.0f);
            if ((lbl_1_data_BC + 0x10000) != 0xFFFF) {
                sp8.x = temp_f30;
                sp8.y = 0.0f;
                sp8.z = -1200.0f;
                HuAudFXEmiterUpDate(lbl_1_data_BC, &sp8);
            }
            var_f31 = 1.2f * lbl_1_bss_C;
            if ((var_f31 >= 1.0f) && ((lbl_1_data_BC + 0x10000) != 0xFFFF)) {
                HuAudFXEmiterPlay(0x555, &sp8);
                sp8.x += 200.0f;
                HuAudFXEmiterPlay(0x55E, &sp8);
                HuAudFXStop(lbl_1_data_BC);
                lbl_1_data_BC = -1;
            }
            if (var_f31 >= 1.0f) {
                var_f31 = 0.0f;
            } else {
                var_f31 = sin((M_PI * (90.0f + (90.0f * var_f31))) / 180.0);
            }
            Hu3DMotionSpeedSet(lbl_1_bss_DC->model[4], 2.0f * var_f31);
            if (lbl_1_bss_C > 0.5f) {
                var_f31 = 2.0f * (9.0f * (1.0f - lbl_1_bss_C));
            } else {
                var_f31 = 9.0f;
            }
            fn_1_44F0(lbl_1_bss_E0->model[0], 0.0f, 0.0f, 0.0f, 0, var_f31);
            if ((lbl_1_bss_C > 0.7f) && (lbl_1_bss_C < 0.9f)) {
                var_f31 = (lbl_1_bss_C - 3.5f);
                if (++lbl_1_bss_10 > (var_f31 * 10.0f)) {
                    lbl_1_bss_10 = 0.0f;
                    temp_f30 = 190.0f + temp_r31->pos.x;
                    temp_f29 = 20.0f + temp_r31->pos.y;
                    temp_f28 = 95.0f + temp_r31->pos.z;
                    var_f31 = 1.0f - (lbl_1_bss_C - 3.5f);
                    fn_1_4FFC(lbl_1_bss_E0->model[1], temp_f30, temp_f29, temp_f28, (s8)(2.0f * var_f31));
                    temp_f30 = 370.0f + temp_r31->pos.x;
                    fn_1_4FFC(lbl_1_bss_E0->model[1], temp_f30, temp_f29, temp_f28, (s8)var_f31);
                    temp_f30 = 490.0f + temp_r31->pos.x;
                    fn_1_4FFC(lbl_1_bss_E0->model[1], temp_f30, temp_f29, temp_f28, (s8)var_f31);
                }
            }
            if (++lbl_1_bss_14 > 1) {
                lbl_1_bss_14 = 0;
                fn_1_44F0(lbl_1_bss_E0->model[0], 190.0f + temp_r31->pos.x, 15.0f, temp_r31->pos.z + 95.0f, 1, 1);
                fn_1_44F0(lbl_1_bss_E0->model[0], 370.0f + temp_r31->pos.x, 15.0f, temp_r31->pos.z + 95.0f, 1, 1);
                fn_1_44F0(lbl_1_bss_E0->model[0], 490.0f + temp_r31->pos.x, 15.0f, temp_r31->pos.z + 95.0f, 1, 1);
                fn_1_44F0(lbl_1_bss_E0->model[0], 190.0f + temp_r31->pos.x, 15.0f, temp_r31->pos.z - 95.0f, 1, 1);
                fn_1_44F0(lbl_1_bss_E0->model[0], 370.0f + temp_r31->pos.x, 15.0f, temp_r31->pos.z - 95.0f, 1, 1);
                fn_1_44F0(lbl_1_bss_E0->model[0], 490.0f + temp_r31->pos.x, 15.0f, temp_r31->pos.z - 95.0f, 1, 1);
            }
            break;
        case 99:
            if (var_r29 == 0) {
                return 0;
            }
            temp_r30->unk2 = MGSeqCreate(3, 0);
            MGSeqPosSet(temp_r30->unk2, 320.0f, 240.0f);
            lbl_1_bss_8 = 0x270F;
            break;
        default:
            if (MGSeqStatGet(temp_r30->unk2) == 0) {
                lbl_1_bss_8 = 0;
                return 1;
            }
            if ((lbl_1_data_C0 == -1) && ((MGSeqStatGet(temp_r30->unk2) & 0x10) != 0)) {
                lbl_1_data_C0 = HuAudSeqPlay(0x48);
            }
            break;
    }
    return 0;
}

s8 fn_1_1B74(omObjData* object) {
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r27;
    s32 temp_r28;
    unkStruct3* temp_r30;

    temp_r30 = (unkStruct3*)object->data;
    switch (lbl_1_bss_8) {
        case 0:
            temp_r30->unk2 = MGSeqCreate(3, 1);
            MGSeqPosSet(temp_r30->unk2, 320.0f, 240.0f);
            HuAudSeqFadeOut(lbl_1_data_C0, 0x64);
            lbl_1_bss_16 = 0;
            lbl_1_bss_8 = 1;
            break;
        case 1:
            if (++lbl_1_bss_16 > 30) {
                lbl_1_bss_8 = 2;
            }
            break;
        case 2:
            if (fn_1_B80()) {
                lbl_1_bss_8 = 3;
            }
            break;
        case 3:
            fn_1_2414(0x80, 0x80);
            if (temp_r30->unk4 >= 0) {
                GWPlayerCoinWinAdd(temp_r30->unk4, 10);
                temp_r30->unk2 = MGSeqCreate(5, 3, GWPlayerCfg[temp_r30->unk4].character, -1, -1, -1);
                HuAudSStreamPlay(1);
            } else {
                temp_r30->unk2 = MGSeqCreate(3, 2);
                HuAudSStreamPlay(4);
            }
            MGSeqPosSet(temp_r30->unk2, 320.0f, 240.0f);
            lbl_1_bss_8 = 4;
            lbl_1_bss_16 = 0;
            break;
        case 4:
            lbl_1_bss_16++;
            if (MGSeqStatGet(temp_r30->unk2) == 0) {
                lbl_1_bss_8 = 5;
            }
            break;
        case 5:
            lbl_1_bss_16++;
            if (lbl_1_bss_16 > 210.0f) {
                return 1;
            }
            break;
    }
    return 0;
}