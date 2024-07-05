#include "REL/m409Dll.h"

#include "math.h"
#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/gamework_data.h"
#include "game/pad.h"

// bss
omObjData* lbl_1_bss_3A0[4];
omObjData* lbl_1_bss_39C;
s32 lbl_1_bss_38C[4];
unkStruct10 lbl_1_bss_10C[8];
s16 lbl_1_bss_108;
s16 lbl_1_bss_106;
s16 lbl_1_bss_104;
unkStruct9 lbl_1_bss_F0;

// data
u32 lbl_1_data_138 = 0xFFFF0000;
s32 lbl_1_data_13C[7] = { 0x30, 0x2D, 0x3A, 0x2E, 0x280032, 0x17, 0x18 };
GXColor lbl_1_data_158[8] = {
    { 0xFF, 0x00, 0x00, 0xFF },
    { 0x00, 0x00, 0xFF, 0xFF },
    { 0xFF, 0x80, 0x80, 0xFF },
    { 0x00, 0xFF, 0x00, 0xFF },
    { 0x80, 0x00, 0xC0, 0xFF },
    { 0x90, 0x30, 0x00, 0xFF },
    { 0xFF, 0xFF, 0x00, 0xFF },
    { 0x00, 0x00, 0x00, 0xFF }
};
HsfVector2f lbl_1_data_178[4] = {
    { 72.0f, 80.0f }, { 504.0f, 80.0f },
    { 72.0f, 400.0f }, { 504.0f, 400.0f },
};
GXColor lbl_1_data_198[8] = {
    { 0xD0, 0x00, 0x00, 0xFF },
    { 0x00, 0x00, 0xFF, 0xFF },
    { 0x00, 0xA0, 0x00, 0xFF },
    { 0xFF, 0xFF, 0x00, 0xFF },
    { 0xA0, 0x00, 0xFF, 0xFF },
    { 0xFF, 0x80, 0x40, 0xFF },
    { 0xFF, 0xA0, 0xF0, 0xFF },
    { 0x00, 0xFF, 0x40, 0xFF }
};

void fn_1_67E0(Process* arg0) {
    s32 var_r31;
    s32 temp_r28;
    omObjData* var_r30;

    omMakeGroupEx(arg0, 0U, 4U);
    omGetGroupMemberListEx(arg0, 0);
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_3A0[var_r31] = var_r30 = omAddObjEx(arg0, 0x30, 3U, 7U, 0, fn_1_6928);
        var_r30->work[0] = var_r31;
    }
    lbl_1_bss_39C = var_r30 = omAddObjEx(arg0, 0x40, 8U, 0xAU, 4, fn_1_91C0);
    fn_1_BF88(0x40, 0x40);
    fn_1_DF20(0x28002C, 0x40, 0x40);
    temp_r28 = (u8)frand();
    
    for (var_r31 = 0; var_r31 < (temp_r28 + 1); var_r31++) {
        fn_1_ABB4();
    }
}

void fn_1_6900(void) {
    CharModelKill(-1);
    fn_1_C0C0();
}

void fn_1_6928(omObjData* arg0) {
    Vec sp8[4] = {
        { -185.0f, 35.0f, 100.0f },
        { -62.5f,  35.0f, 100.0f },
        { 62.5f,   35.0f, 100.0f },
        { 185.0f,  35.0f, 100.0f }
    };
    s8 sp38[8][32] = {
        "test11_tex_we-itemhook-r",
        "test11_tex_we-itemhook-r",
        "test11_tex_we-itemhook-r",
        "test11_tex_we-itemhook-r",
        "test11_tex_we-itemhook-r",
        "test11_tex_we-itemhook-r",
        "test11_tex_we-itemhook-r"
    };
    unkStruct7* var_r31;
    s32 var_r30;
    s32 var_r28;
    
    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(unkStruct7), 0x10000000);
    arg0->data = var_r31;
    var_r31->unk0 = arg0->work[0];
    var_r31->unk1 = GWPlayerCfg[var_r31->unk0].character;
    var_r31->unk2 = (var_r31->unk0 >> 1);
    var_r31->unk3 = (var_r31->unk0 & 1);
    var_r31->unk4 = GWPlayerCfg[var_r31->unk0].pad_idx;
    var_r31->unk5 = GWPlayerCfg[var_r31->unk0].iscom;
    var_r31->unk6 = GWPlayerCfg[var_r31->unk0].diff;
    var_r31->unk1C = 0;
    var_r31->unk13 = 1;
    var_r31->unk14 = 0;
    var_r31->unk61 = fn_1_ABB4() & 0x1;
    var_r31->unk64 = var_r31->unk63 = 0;
    var_r31->unk18 = -1;
    var_r31->unk24.x = sp8[var_r31->unk0].x;
    var_r31->unk24.y = sp8[var_r31->unk0].y;
    var_r31->unk24.z = sp8[var_r31->unk0].z;
    var_r31->unk30.x = var_r31->unk30.y = var_r31->unk30.z = 0.0f;
    var_r31->unk3C.y = 180.0f;
    var_r31->unk3C.x = var_r31->unk3C.z = 0.0f;
    var_r30 = CharModelCreate(var_r31->unk1, 4);
    arg0->model[0] = var_r30;
    Hu3DModelAttrSet(var_r30, 0x40000001);
    
    for (var_r28 = 0; var_r28 < 7; var_r28++) {
        if ((lbl_1_data_13C[var_r28] & 0xFFFF0000) != 0) {
            arg0->motion[var_r28] = CharModelMotionCreate(var_r31->unk1, var_r31->unk1 + lbl_1_data_13C[var_r28]);
        } else {
            arg0->motion[var_r28] = CharModelMotionCreate(var_r31->unk1, lbl_1_data_13C[var_r28]);
        }
    }
    CharModelMotionDataClose(var_r31->unk1);
    CharModelMotionSet(var_r31->unk1, arg0->motion[var_r31->unk1C]);
    omSetTra(arg0, var_r31->unk24.x, var_r31->unk24.y, var_r31->unk24.z);
    Hu3DModelPosSet(var_r30, var_r31->unk24.x, var_r31->unk24.y, var_r31->unk24.z);
    Hu3DModelRotSet(var_r30, 0.0f, 30.0f, 0.0f);
    CharModelStepTypeSet(var_r31->unk1, 0);
    arg0->model[1] = var_r30 = Hu3DModelCreate(HuDataSelHeapReadNum(0x280012, 0x10000000, HEAP_DATA));
    Hu3DModelHookSet(arg0->model[0], (char*)sp38[var_r31->unk1], arg0->model[1]);
    var_r30 = fn_1_DA48(2, 1);
    var_r31->unk57 = var_r30;
    lbl_1_bss_F0.unk10[var_r30].unk30 = fn_1_8838;
    fn_1_E2A8(var_r30, 0, 0x28002B, 0x40, 0x40);
    fn_1_F098(var_r30, lbl_1_data_158[var_r31->unk1].r, lbl_1_data_158[var_r31->unk1].g, lbl_1_data_158[var_r31->unk1].b, lbl_1_data_158[var_r31->unk1].a);
    fn_1_F024(var_r30, 1, lbl_1_data_158[var_r31->unk1].r, lbl_1_data_158[var_r31->unk1].g, lbl_1_data_158[var_r31->unk1].b, 0x98);
    fn_1_E85C(var_r30, 0, var_r31->unk24.x, 100.0f + var_r31->unk24.y, -1200.0f);
    fn_1_ED44(var_r30, 0, 0x10);
    fn_1_EC1C(var_r30, 0, 2.0f, 2.0f, 1.0f);
    fn_1_EC1C(var_r30, 1, 2.5f, 2.5f, 1.0f);
    fn_1_ED44(var_r30, 1, 0x14);
    fn_1_F408(var_r30, 1, 1);
    var_r30 = fn_1_DA48(1, 1);
    fn_1_DEF4(var_r30, 0, 0);
    fn_1_E7C8(lbl_1_bss_F0.unk6, 0, 0x28002D);
    var_r31->unk58 = var_r30;
    lbl_1_bss_F0.unk10[var_r30].unk30 = &fn_1_8D6C;
    fn_1_ED44(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 4);
    lbl_1_bss_F0.unk10[lbl_1_bss_F0.unk6].unk3C[lbl_1_bss_F0.unk8].unk70 = var_r31->unk0;
    lbl_1_bss_F0.unk10[lbl_1_bss_F0.unk6].unk3C[lbl_1_bss_F0.unk8].unk72 = -1;
    fn_1_EC1C(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 0.5f, 0.5f, 1.0f);
    var_r31->unk59 = 0;
    var_r31->unk60 = 0;
    var_r30 = espEntry(0x280031, 1, 0);
    var_r31->unk55 = var_r30;
    espColorSet(var_r30, 0, 0, 0);
    espTPLvlSet(var_r30, 0.5);
    espPosSet(var_r30, lbl_1_data_178[var_r31->unk0].x, lbl_1_data_178[var_r31->unk0].y);
    espAttrSet(var_r30, 4);
    var_r30 = espEntry(0x280030, 1, 0);
    var_r31->unk54 = var_r30;
    espPosSet(var_r30, lbl_1_data_178[var_r31->unk0].x, lbl_1_data_178[var_r31->unk0].y);
    espAttrSet(var_r30, 4);
    var_r30 = espEntry(var_r31->unk1 + 0x610000, 1, 0);
    var_r31->unk56 = var_r30;
    espPosSet(var_r30, lbl_1_data_178[var_r31->unk0].x - 27.0f, lbl_1_data_178[var_r31->unk0].y - 20.0f);
    espAttrSet(var_r30, 4);
    
    for (var_r28 = 0; var_r28 < 3; var_r28++) {
        var_r30 = espEntry(0x61000A, 0, 0);
        var_r31->unk5A[var_r28][0] = var_r30;
        espAttrSet(var_r30, 4);
        espPosSet(var_r30, lbl_1_data_178[var_r31->unk0].x - 32.0f + (var_r28 * 0x1E), 16.0f + lbl_1_data_178[var_r31->unk0].y);
        var_r30 = espEntry(0x61000B, 0, 0);
        var_r31->unk5A[var_r28][1] = var_r30;
        espAttrSet(var_r30, 4);
        espPosSet(var_r30, lbl_1_data_178[var_r31->unk0].x - 32.0f + (var_r28 * 0x1E), 16.0f + lbl_1_data_178[var_r31->unk0].y);
    }
    arg0->func = fn_1_7344;
}

void fn_1_7344(omObjData* arg0) {
    s16 sp8;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 var_f25;
    f32 var_f26;
    f32 var_f27;
    f32 var_f31;
    s16 temp_r0;
    s32 temp_r19;
    s16 temp_r22;
    s16 temp_r26;
    s16 temp_r25;
    s16 var_r20;
    s16 var_r21;
    s16 var_r27;
    s16 var_r28;
    s32 var_r24;
    s32 temp_r23;
    Vec* temp_r30;
    unkStruct7* temp_r31;

    var_f31 = 0.0f;
    temp_r31 = (unkStruct7*)arg0->data;
    temp_r19 = arg0->model[0];
    temp_r31->unk48 = temp_r31->unk24;
    var_r28 = temp_r31->unk1C;
    if (temp_r31->unk5 != 0) {
        fn_1_7FE8(arg0);
    } else {
        temp_r31->unkA = HuPadStkX[temp_r31->unk4];
        temp_r31->unkC = HuPadStkY[temp_r31->unk4];
        temp_r31->unkE = HuPadBtnDown[temp_r31->unk4];
        temp_r31->unk10 = HuPadBtn[temp_r31->unk4];
    }
    temp_r26 = temp_r31->unkA;
    temp_r25 = temp_r31->unkC;
    temp_r22 = temp_r31->unkE;
    sp8 = temp_r31->unk10;
    fn_1_DEF4(temp_r31->unk57, 0, 0);
    fn_1_F478(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, lbl_1_bss_F0.unkA, 2);
    temp_r30 = fn_1_CCCC(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8);
    if (fn_1_2454(7) != 3) {
        fn_1_ED00(temp_r31->unk57, 4);
    } else {
        espAttrReset(temp_r31->unk54, 4);
        espAttrReset(temp_r31->unk55, 4);
        
        for (var_r24 = 0; var_r24 < 3; var_r24++) {
            espAttrReset(temp_r31->unk5A[var_r24][0], 4);
        }
        espAttrReset(temp_r31->unk56, 4);
        fn_1_EE24(temp_r31->unk57, 4);
        temp_f28 = (ABS(temp_r26) + ABS(temp_r25));
        temp_f30 = 0.008f * (temp_f28 * temp_r26);
        temp_f29 = 0.008f * (temp_f28 * temp_r25);
        fn_1_E99C(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, temp_f30, temp_f29, 0.0f);
    }
    switch (lbl_1_bss_108) {
        case 4:
            if (temp_r31->unk1C == 2) {
                fn_1_F478(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, lbl_1_bss_F0.unkA, 0);
                if ((temp_r22 & 0x100) != 0) {
                    temp_r23 = fn_1_8D08(temp_r31->unk0);
                    fn_1_DEF4(temp_r31->unk58, 0, 0);
                    fn_1_EE68(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 4);
                    lbl_1_bss_F0.unk10[lbl_1_bss_F0.unk6].unk3C[lbl_1_bss_F0.unk8].unk72 = temp_r23;
                    lbl_1_bss_F0.unk10[lbl_1_bss_F0.unk6].unk3C[lbl_1_bss_F0.unk8].unk74 = 0;
                    lbl_1_bss_F0.unk10[lbl_1_bss_F0.unk6].unk3C[lbl_1_bss_F0.unk8].unk76 = 0;
                    fn_1_E85C(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, temp_r31->unk24.x, 100.0f + temp_r31->unk24.y, temp_r31->unk24.z);
                    if (temp_r23 == -1) {
                        lbl_1_bss_F0.unk10[temp_r31->unk58].unk3C[0].unk58.x = temp_r30->x;
                        lbl_1_bss_F0.unk10[temp_r31->unk58].unk3C[0].unk58.y = temp_r30->y;
                        lbl_1_bss_F0.unk10[temp_r31->unk58].unk3C[0].unk58.z = temp_r30->z;
                    }
                }
            }
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
            if (temp_r31->unk59 >= 3) {
                lbl_1_bss_104 = temp_r31->unk0 + 1;
            }
            if (temp_r31->unk60 == 0) {
                temp_f29 = (180.0 * (atan2((temp_r30->x - temp_r31->unk24.x), (temp_r30->z - temp_r31->unk24.z)) / M_PI));
                temp_f30 = (180.0 * (atan2((temp_r31->unk24.y - temp_r30->y), (temp_r31->unk24.z - temp_r30->z)) / M_PI));
                temp_f30 *= (1.0f - (0.015f * ABS(temp_f30)));
                temp_r31->unk3C.x = fn_1_AD40(temp_r31->unk3C.x, temp_f30, 0.5f);
                temp_r31->unk3C.y = fn_1_AD40(temp_r31->unk3C.y, temp_f29, 0.5f);
            }
            break;
        case 6:
            fn_1_ED44(temp_r31->unk57, 0, 4);
            Hu3DModelHookReset(temp_r19);
            Hu3DModelAttrSet(arg0->model[1], 1);
            temp_r23 = fn_1_DA48(1, 1);
            fn_1_DEF4(temp_r23, 0, 0);
            fn_1_E7C8(lbl_1_bss_F0.unk6, 0, 0x28002C);
            fn_1_E85C(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 20.0f + temp_r31->unk24.x, 100.0f + temp_r31->unk24.y, temp_r31->unk24.z - 25.0f);
            fn_1_EC1C(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 2.0f, 2.0f, 1.0f);
            fn_1_ED44(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 0x80000000);
            fn_1_F024(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 0xFF, 0xFF, 0xFF, 0xFF);
            fn_1_F17C(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, lbl_1_bss_F0.unkA, 0x11);
            fn_1_F2F8(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, lbl_1_bss_F0.unkA, 0.5f);
        case 7:
            temp_r31->unk3C.y = fn_1_AD40(temp_r31->unk3C.y, 0.0f, 0.8f);
            temp_r31->unk3C.x = 0.0f;
            if (fn_1_2454(0x80) == 0x80) {
                if (temp_r31->unk59 >= 3) {
                    var_r28 = 5;
                } else {
                    var_r28 = 6;
                }
                var_r27 = 0;
                var_f31 = 0.0f;
            }
            break;
    }
    switch (temp_r31->unk1C) {
        case 0:
            if ((lbl_1_bss_108 != 0) && (lbl_1_bss_108 < 6)) {
                var_r28 = 1;
                var_r27 = 0;
                var_f31 = 0.0f;
                temp_r31->unk62 = (s8)(8.0f * (fn_1_ABB4() / 65536.0f));
            }
            break;
        case 2:
            if (lbl_1_bss_108 == 0) {
                var_r28 = 1;
                var_r27 = 4;
                var_f31 = fn_1_BF38(arg0->motion[1]);
                lbl_1_bss_38C[arg0->work[0]] = 1;
            }
            if ((lbl_1_bss_108 == 4) && ((temp_r22 & 0x100) != 0)) {
                HuAudFXPlay(0x556);
                var_r28 = 3;
                var_r27 = 0;
                var_f31 = 0.0f;
            }
            break;
        case 1:
            if (CharModelMotionEndCheck(temp_r31->unk1) != 0) {
                if (CharModelMotionTimeGet(temp_r31->unk1) <= 0.0f) {
                    var_r28 = 0;
                } else {
                    var_r28 = 2;
                }
                var_r27 = 1;
                var_f31 = 0.0f;
            }
            break;
        case 3:
            if (temp_r31->unk60 != 0) {
                temp_r31->unk3C.x = fn_1_AD40(temp_r31->unk3C.x, 0.0f, 0.8f);
                temp_r31->unk3C.y = fn_1_AD40(temp_r31->unk3C.y, 0.0f, 0.8f);
                if (ABS(temp_r31->unk3C.y) < 10.0f) {
                    temp_r31->unk3C.y = 0.0f;
                    var_r28 = 4;
                    var_r27 = 0;
                    var_f31 = 0.0f;
                }
            } else if (CharModelMotionEndCheck(temp_r31->unk1) != 0) {
                var_r28 = 2;
                var_r27 = 1;
                var_f31 = 0.0f;
            }
            break;
        case 4:
            if (temp_r31->unk18 < 0) {
                temp_r31->unk18 = HuAudCharVoicePlay(temp_r31->unk1, 0x125);
            }
            if (CharModelMotionEndCheck(temp_r31->unk1) != 0) {
                temp_r31->unk3C.y = fn_1_AD40(temp_r31->unk3C.y, 180.0f, 0.8f);
                if (ABS(temp_r31->unk3C.y) > 170.0f) {
                    var_r28 = 2;
                    var_r27 = 1;
                    var_f31 = 0.0f;
                    temp_r31->unk60 = 0;
                    temp_r31->unk18 = -1;
                }
            } else {
                temp_r31->unk3C.y = 0.0f;
            }
            break;
        case 5:
        case 6:
            break;
    }
    if (var_r28 != temp_r31->unk1C) {
        temp_r31->unk1C = var_r28;
        CharModelMotionShiftSet(temp_r31->unk1, arg0->motion[temp_r31->unk1C], var_f31, 8.0f, (u32) var_r27);
    }
    omSetTra(arg0, temp_r31->unk24.x, temp_r31->unk24.y, temp_r31->unk24.z);
    omSetRot(arg0, temp_r31->unk3C.x, temp_r31->unk3C.y, temp_r31->unk3C.z);
}

void fn_1_7FE8(omObjData* arg0) {
    Vec sp20;
    Vec sp14;
    s32 sp10;
    f32 spC;
    s16 sp8;
    unkStruct10* var_r30;
    Vec* temp_r29;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f1;
    f32 temp_f29;
    f32 temp_f30;
    f32 var_f28;
    s32 var_r28;
    unkStruct7* temp_r31;

    temp_r31 = (unkStruct7*)arg0->data;
    sp10 = arg0->model[0];
    sp8 = temp_r31->unk1C;
    temp_r31->unkE = temp_r31->unk10 = 0;
    temp_r29 = fn_1_CCCC(temp_r31->unk57, 0);
    sp20.x = sp20.y = sp20.z = 0.0f;
    switch (lbl_1_bss_108) {                  /* irregular */
        case 2:
            if (temp_r31->unk61 == 0) {
                var_r30 = &lbl_1_bss_10C[0];
                
                for (var_r28 = 0; var_r28 < 8; var_r28++, var_r30++) {
                    if (var_r30->unk2 == 0) break;
                    sp20.x += var_r30->unkC.x;
                    sp20.y += var_r30->unkC.y;
                    sp20.z += var_r30->unkC.z;
                }
                sp20.x /= var_r28;
                sp20.y /= var_r28;
                sp20.z /= var_r28;
            } else {
                var_r30 = &lbl_1_bss_10C[temp_r31->unk62];
                if (var_r30->unk2 != 0) {
                    sp20.x = var_r30->unkC.x;
                    sp20.y = var_r30->unkC.y;
                    sp20.z = var_r30->unkC.z;
                } else {
                    sp20.x = 0.0f;
                    sp20.y = 800.0f;
                    sp20.z = -1200.0f;
                }
            }
            break;
        case 3:
            temp_r31->unk62 = 0xFFU;
            temp_r31->unk64 = (0x28 - (temp_r31->unk6 * 10));
        case 4:
            sp20.x = temp_r29->x;
            sp20.y = temp_r29->y;
            sp20.z = temp_r29->z;
            if (temp_r31->unk64 != 0) {
                temp_r31->unk64--;
            }
            if ((temp_r31->unk64 == 0)) {
                if (((s32)((0x30 - (temp_r31->unk6 * 8)) * (fn_1_ABB4() / 65536.0f)) == 0)) {
                    temp_r31->unk62 = lbl_1_bss_106;
                }
            }
            if (temp_r31->unk62 != 0xFF) {
                var_r30 = &lbl_1_bss_10C[temp_r31->unk62];
                sp20.x = var_r30->unkC.x;
                sp20.y = var_r30->unkC.y;
                sp20.z = var_r30->unkC.z;
                temp_f29 = 100.0f * (0.5f * (4 - temp_r31->unk6));
                temp_f29 = 20.0f + (temp_f29 * (fn_1_ABB4() / 65536.0f));
                temp_f30 = ((var_r30->unkC.z - temp_r29->z) * (var_r30->unkC.z - temp_r29->z)) + (((var_r30->unkC.x - temp_r29->x) * (var_r30->unkC.x - temp_r29->x)) + ((var_r30->unkC.y - temp_r29->y) * (var_r30->unkC.y - temp_r29->y)));
                if ((sqrtf(temp_f30) < temp_f29) && ((s32)((0x20 - (temp_r31->unk6 * 8)) * (fn_1_ABB4() / 65536.0f)) == 0)) {
                    temp_r31->unkE = (temp_r31->unkE | 0x100);
                }
            }
            break;
        default:
            sp20.x = 0.0f;
            sp20.y = 800.0f;
            sp20.z = -1200.0f;
            break;
    }
    if (temp_r31->unk63 == 0) {
        temp_f29 = 100.0f * (0.5f * (4 - temp_r31->unk6));
        sp20.x += (temp_f29 * ((fn_1_ABB4() - 0x8000) / 32768.0f));
        sp20.y += (temp_f29 * ((fn_1_ABB4() - 0x8000) / 32768.0f));
        temp_r31->unk68.x = sp20.x;
        temp_r31->unk68.y = sp20.y;
        temp_r31->unk68.z = sp20.z;
        sp14.x = temp_r31->unk68.x - temp_r29->x;
        sp14.y = temp_r31->unk68.y - temp_r29->y;
        sp14.z = temp_r31->unk68.z - temp_r29->z;
        fn_1_B378(&sp14);
        temp_r31->unkA = (sp14.x * ((temp_r31->unk6 * 6) + 0x18));
        temp_r31->unkC = (sp14.y * ((temp_r31->unk6 * 6) + 0x18));
        temp_r31->unk63 = ((s32)(((4 - temp_r31->unk6) * 8) * (fn_1_ABB4() / 65536.0f)) + 8);
    }
    temp_r31->unk63--;
}