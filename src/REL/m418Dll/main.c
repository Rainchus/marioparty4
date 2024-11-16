#include "math.h"
#include "ext_math.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"

#include "REL/m418Dll.h"

// types
typedef struct M418DllUnkStruct2 {
    char unk[0x4];
    s32 unk4[3];
    char unk10[0x4];
} M418DllUnkStruct2; // sizeof 0x14

typedef struct M418DllUnkStruct3 {
    char unk0[0x4];
    s32 unk4;
    char unk[0x58];
} M418DllUnkStruct3; // sizeof 0x60

typedef struct M418DllUnkStruct4 {
    char unk[0x4];
    f32 unk4;
    f32 unk8;
    s32 unkC;
    s32 unk10;
    f32 unk14;
    f32 unk18;
} M418DllUnkStruct4; // sizeof 0x1C

typedef struct M418DllUnkStruct5 {
    char unk[0x14];
    s32 unk14;
    char unk18[0x14];
} M418DllUnkStruct5; // sizeof 0x2C;

typedef struct M418DllUnkStruct6 {
    s32 unk0;
    char unk4[0x40];
} M418DllUnkStruct6;

// bss
M418DllUnkStruct6 lbl_1_bss_3EC;
M418DllUnkStruct3 lbl_1_bss_26C[4];
M418DllUnkStruct5 lbl_1_bss_240;
M418DllUnkStruct lbl_1_bss_1F4;
M418DllUnkStruct2 lbl_1_bss_1E0;
M418DllUnkStruct4 lbl_1_bss_170[4];
M418DllUnkStruct4 lbl_1_bss_11C[3];
s32 lbl_1_bss_8;
s32 lbl_1_bss_4;
Process* lbl_1_bss_0;

// data
s32 lbl_1_data_0[2] = { -1, -1 };
s32 lbl_1_data_8 = -1;

// protos
void fn_1_AD14(omObjData*, s32, s32, s32, s32);

void fn_1_0(void) {
    Hu3DGLightCreate(-2500.0f, 5000.0f, 5000.0f, 0.0f, -1.0f, -1.0f, 0xFF, 0xD8, 0xA0);
}

void fn_1_74(void) {
    M418DllUnkStruct* var_r31 = &lbl_1_bss_1F4;
    Vec sp2C = { 0.0f, 1100.0f, 1800.0f };
    Vec sp20 = { 0.0f, 600.0f, 600.0f };

    fn_1_B104(var_r31, sp2C, sp20);
    fn_1_B41C(var_r31);
    var_r31->rot.x++;
}

void fn_1_158(s32 arg0, f32 arg8) {
    M418DllUnkStruct* var_r31 = &lbl_1_bss_1F4;
    
    var_r31->unk3C[arg0] = arg8;
}

f32 fn_1_180(s32 arg0) {
    M418DllUnkStruct* var_r31 = &lbl_1_bss_1F4;
    
    if (var_r31->unk3C[arg0] != 0.0f) {
        var_r31->unk3C[arg0] *= -0.9f;
        if (var_r31->unk3C[arg0] >= -0.5f) {
            if (var_r31->unk3C[arg0] <= 0.5f) {
                var_r31->unk3C[arg0] = 0.0f;
            }
        }
    }
    return var_r31->unk3C[arg0];
}

void fn_1_248(M418DllFunc arg0) {
    M418DllUnkStruct* var_r31 = &lbl_1_bss_1F4;
    
    var_r31->unk0 = arg0;
}

void fn_1_268(omObjData* object) {
    M418DllUnkStruct* var_r31 = &lbl_1_bss_1F4;
    
    if (var_r31->unk0 != NULL) {
        var_r31->unk0();
    }
    
    Center.x = var_r31->center.x + fn_1_180(0);
    Center.y = var_r31->center.y + fn_1_180(1);
    Center.z = var_r31->center.z + fn_1_180(2);
    CRot.x = var_r31->rot.x;
    CRot.y = var_r31->rot.y;
    CRot.z = var_r31->rot.z;
    CZoom = var_r31->zoom;
}

void fn_1_500(void) {
    M418DllUnkStruct* var_r31;
    Hu3DCameraCreate(1);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 40.0f, 0.1f, 17500.0f, 1.2f);
    var_r31 = &lbl_1_bss_1F4;
    var_r31->unk0 = fn_1_74;
    omAddObjEx(lbl_1_bss_0, 0x7FDA, 0, 0, -1, omOutView);
    omAddObjEx(lbl_1_bss_0, 0x7FD9, 0, 0, -1, fn_1_268);
}

void fn_1_618(void) {
    Vec sp20 = { -1500.0f, 2500.0f, 1000.0f };
    Vec sp14 = { 0.0f, 0.0f, 0.0f };
    Vec sp8 = { 0.0f, 1.0f, 0.0f };

    Hu3DShadowCreate(40.0f, 2000.0f, 25000.0f);
    Hu3DShadowTPLvlSet(0.675f);
    Hu3DShadowPosSet(&sp20, &sp8, &sp14);
}

void fn_1_6DC(s32 arg0) {
    if (lbl_1_bss_8 == 0) {
        lbl_1_bss_8 = 1;
        lbl_1_bss_4 = arg0 * 0x3C;
    }
}

s32 fn_1_714(void) {
    s32 var_r31 = 0;
    
    if (lbl_1_bss_8 == 3) {
        var_r31 = 1;
    }
    return var_r31;
}

void fn_1_748(void) {
    if (lbl_1_bss_8 == 2) {
        lbl_1_bss_8 = 3;
        lbl_1_bss_4 = 30;
    }
}

void fn_1_780(void) {
    switch (lbl_1_bss_8) {
        case 1:
            if (lbl_1_data_8 == -1) {
                lbl_1_data_8 = MGSeqCreate(1, lbl_1_bss_4 / 60, -1, -1);
            }
            lbl_1_bss_8 = 2;
            break;
        case 2:
            lbl_1_bss_4--;
            if (lbl_1_data_8 != -1) {
                MGSeqParamSet(lbl_1_data_8, 1, ((lbl_1_bss_4 + 0x3B) / 60));
            }
            if (lbl_1_bss_4 <= 0) {
                lbl_1_bss_4 = 30;
                lbl_1_bss_8 = 3;
            }
            break;
        case 3:
            if (lbl_1_data_8 != -1) {
                MGSeqParamSet(lbl_1_data_8, 2, -1);
                lbl_1_data_8 = -1;
            }
            lbl_1_bss_4 = 0;
            lbl_1_bss_8 = 0;
            break;
    }
}

s32 fn_1_950(s32 arg0) {
    
    if ((rand8() % arg0) == 0) {
        return 1;
    } else {
        return 0;
    }
}

void fn_1_998(omObjData* object) {
    s32 var_r31;
    M418DllUnkStruct2* var_r30 = &lbl_1_bss_1E0;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        switch (var_r30->unk4[var_r31]) {
            case 1:
                fn_1_ABC4(object, var_r31 + 1, var_r31 + 1, 0, 2);
                var_r30->unk4[var_r31] = 99;
                break;
            case 2:
                fn_1_ABC4(object, var_r31 + 1, var_r31 + 1, 0, 0);
                var_r30->unk4[var_r31] = 99;
                break;
            case 3:
                HuAudFXPlay(0x5DD);
                Hu3DModelAttrSet(object->model[var_r31 + 1], 0x40000004);
                var_r30->unk4[var_r31] = 99;
                break;
        }
    }
}

void fn_1_AA8(omObjData* object) {
    Mtx sp10;
    char* sp8[2] = { "scene02-dai1_null", "scene02-dai2_null1" };
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        Hu3DModelObjMtxGet(object->model[5], sp8[var_r31], sp10);
        Hu3DModelPosSet(object->model[var_r31 + 6], sp10[0][3], sp10[1][3], sp10[2][3]);
    }
    object->func = fn_1_998;
}

void fn_1_B4C(omObjData* object) {
    s32 sp8[3] = { 0x310021, 0x310022, 0x310023 };
    s32 var_r30;

    object->model[0] = Hu3DModelCreateFile(0x310011);
    Hu3DModelShadowMapSet(object->model[0]);
    
    for (var_r30 = 1; var_r30 < 4; var_r30++) {
        object->model[var_r30] = Hu3DModelCreateFile(sp8[var_r30 - 1]);
        object->motion[var_r30] = Hu3DMotionIDGet(object->model[var_r30]);
        Hu3DModelShadowMapSet(object->model[var_r30]);
        Hu3DModelPosSet(object->model[var_r30], 0.0f, 0.0f, 0.0f);
        fn_1_ABC4(object, var_r30, var_r30, 0, 2);
    }
    object->model[4] = Hu3DModelCreateFile(0x310016);
    object->model[5] = Hu3DModelCreateFile(0x310018);
    
    for (var_r30 = 6; var_r30 < 8; var_r30++) {
        object->model[var_r30] = Hu3DModelCreateFile(0x310026);
        object->motion[var_r30] = Hu3DMotionIDGet(object->model[var_r30]);
        Hu3DModelScaleSet(object->model[var_r30], 2.0f, 2.0f, 2.0f);
        Hu3DModelLayerSet(object->model[var_r30], 1);
        fn_1_ABC4(object, var_r30, var_r30, 0, 1);
    }
    
    for (var_r30 = 8; var_r30 < 11; var_r30++) {
        object->model[var_r30] = Hu3DModelCreateFile(0x31002A);
        object->motion[var_r30] = Hu3DJointMotion(object->model[var_r30], HuDataSelHeapReadNum(0x31002E, MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelPosSet(object->model[var_r30], -350.0f + 360.0f * (var_r30 - 8), -200.0f, -660.0f);
        fn_1_ABC4(object, var_r30, var_r30, 0, 1);
    }
    object->func = fn_1_AA8;
}

void fn_1_E74(omObjData* object) {
    Mtx sp18;
    f32 var_f31;

    M418DllUnkStruct4* temp_r30;
    M418DllUnkStruct4* temp_r29;
    M418DllUnkStruct3* temp_r28;
    M418DllUnkStruct4* temp_r27;
    M418DllUnkStruct6* temp_r26;
    HsfObject* temp_r25;
    ModelData* temp_r24;

    temp_r26 = &lbl_1_bss_3EC;
    temp_r28 = &lbl_1_bss_26C[temp_r26->unk0];
    temp_r30 = &lbl_1_bss_170[object->work[0]];
    if (object->work[1] == 0) {
        fn_1_ABC4(object, 2, 2, 0, 2);
    } else if (object->work[1] == 1) {
        Hu3DModelAttrReset(object->model[3], 1);
        Hu3DModelAttrReset(object->model[4], 1);
        Hu3DModelAttrReset(object->model[5], 1);
        Hu3DModelAttrReset(object->model[6], 1);
        fn_1_ABC4(object, 2, 2, 0, 0);
        fn_1_ABC4(object, 3, 3, 0, 0);
        fn_1_ABC4(object, 4, 4, 0, 1);
        object->work[1] = 2;
        lbl_1_bss_240.unk14 = HuAudFXPlay(0x5D6);
    } else if (object->work[1] == 2) {
        if (Hu3DMotionEndCheck(object->model[3]) != 0) {
            object->work[1] = 3;
            object->work[2] = 0;
            temp_r30->unkC = 1;
            HuAudFXFadeOut(lbl_1_bss_240.unk14, 0x3E8);
        }
    } else if (object->work[1] == 3) {
        temp_r29 = &lbl_1_bss_170[object->work[0]];
        temp_r29->unkC = 2;
        temp_r29->unk4 += 1.0f;
        if (temp_r29->unk4 >= 20.0f) {
            temp_r29->unk4 = 20.0f;
        }
        if (object->work[2]++ >= 0x5A) {
            if (temp_r29->unk10 == 1) {
                object->work[1] = 5;
                temp_r29->unk8 = 0.0f;
            } else {
                HuAudFXPlay(0x5D2);
                object->work[1] = 4;
                Hu3DModelObjMtxGet(object->model[0], "taihou-null4", sp18);
                Hu3DModelPosSet(object->model[5], sp18[0][3], sp18[1][3], sp18[2][3]);
                fn_1_ABC4(object, 5, 5, 0, 0);
                fn_1_158(2, 256.0f);
            }
            temp_r29->unkC = 3;
        }
    } else if (object->work[1] == 4) {
            if ((Hu3DMotionEndCheck(object->model[5]) != 0) || (temp_r30->unk10 == 1)) {
                object->work[1] = 99;
                Hu3DModelAttrSet(object->model[3], 1);
                Hu3DModelAttrSet(object->model[4], 1);
                Hu3DModelAttrSet(object->model[5], 1);
            }
    } else if (object->work[1] == 5 || object->work[1] == 6) {
        if (temp_r30->unk8 > 1.7f) {
            temp_r30->unk8 = 1.7f;
        }
        if (object->work[1] == 5) {
            var_f31 = temp_r30->unk8 * temp_r30->unk8 * (temp_r30->unk8 >= 0.0f ? -3.5f : 3.5f);
            temp_r30->unk4 += var_f31;
        } else {
            var_f31 = temp_r30->unk8 * temp_r30->unk8 * (temp_r30->unk8 >= 0.0f ? -1.25f : 1.25f);
            temp_r30->unk4 += var_f31;
        }
        if (temp_r30->unk4 <= 0.0f && object->work[1] == 5) {
            temp_r30->unk4 = 0.0f;
            temp_r30->unk8 = -1.47f;
            object->work[1] = 6;
            fn_1_158(1, 4.0f);
            omVibrate(temp_r28->unk4, 0xC, 6, 6);
            HuAudFXPlay(0x5DA);
        } else {
            if ((temp_r30->unk4 <= 0.0f) && (object->work[1] == 6)) {
                Hu3DModelObjMtxGet(object->model[0], "taihou-null4", sp18);
                Hu3DModelPosSet(object->model[6], sp18[0][3], sp18[1][3], sp18[2][3]);
                fn_1_158(1, 4.0f);
                omVibrate(temp_r28->unk4, 0xC, 6, 6);
                temp_r30->unk4 = 0.0f;
                temp_r30->unk8 = 0.0f;
                object->work[1] = 4;
                fn_1_ABC4(object, 6, 6, 0, 0);
                HuAudFXPlay(0x5DA);
                HuAudFXPlay(0x5DB);
            }
        }
        temp_r30->unk8 += 0.11f;
    }
    if (object->work[1] != 0) {
        const char* sp8[4] = { "doukasen-null_B", "doukasen-null_A", "doukasen-null_X", "doukasen-null_Y" };
        Hu3DModelObjMtxGet(object->model[3], sp8[object->work[0]], sp18);
        Hu3DModelPosSet(object->model[4], sp18[0][3], sp18[1][3], sp18[2][3]);
    }
    temp_r27 = &lbl_1_bss_170[object->work[0]];
    temp_r25 = Hu3DModelObjPtrGet(object->model[0], "taihou-taihou");
    temp_r25->data.base.rot.x = temp_r27->unk4;
    temp_r24 = &Hu3DData[object->model[1]];
    temp_r24->rot.x = temp_r27->unk4;
}

void fn_1_14F0(omObjData* arg0) {
    s32 var_r30 = arg0->work[0];
    s32 sp28[4] = { 0x310012, 0x310013, 0x310015, 0x310014 };
    s32 sp18[4] = { 0x310019, 0x31001A, 0x31001B, 0x31001C };
    s32 sp8[4] = { 0x31001D, 0x31001E, 0x31001F, 0x310020 };
    
    arg0->model[0] = Hu3DModelCreateFile(0x310010);
    omSetTra(arg0, -540.0f + (360.0f * var_r30), 115.0f, -900.0f);
    arg0->model[1] = Hu3DModelCreateFile(sp28[var_r30]);
    Hu3DModelPosSet(arg0->model[1], -540.0f + (360.0f * var_r30), 115.0f, -900.0f);
    arg0->model[2] = Hu3DModelCreateFile(sp18[var_r30]);
    arg0->motion[2] = Hu3DMotionIDGet(arg0->model[2]);
    fn_1_ABC4(arg0, 2, 2, 0, 2);
    arg0->model[3] = Hu3DModelCreateFile(sp8[var_r30]);
    arg0->motion[3] = Hu3DMotionIDGet(arg0->model[3]);
    Hu3DModelAttrSet(arg0->model[3], 1);
    fn_1_ABC4(arg0, 3, 3, 0, 2);
    arg0->model[4] = Hu3DModelCreateFile(0x310025);
    arg0->motion[4] = Hu3DMotionIDGet(arg0->model[4]);
    Hu3DModelAttrSet(arg0->model[4], 1);
    fn_1_ABC4(arg0, 4, 4, 0, 2);
    arg0->model[5] = Hu3DModelCreateFile(0x310024);
    arg0->motion[5] = Hu3DMotionIDGet(arg0->model[5]);
    Hu3DModelAttrSet(arg0->model[5], 1);
    fn_1_ABC4(arg0, 5, 5, 0, 2);
    arg0->model[6] = Hu3DModelCreateFile(0x310028);
    arg0->motion[6] = Hu3DMotionIDGet(arg0->model[6]);
    Hu3DModelAttrSet(arg0->model[6], 1);
    fn_1_ABC4(arg0, 6, 6, 0, 2);
    Hu3DModelScaleSet(arg0->model[6], 3.0f, 3.0f, 3.0f);
    arg0->func = fn_1_E74;
}

void fn_1_18AC(omObjData* object) {
    M418DllUnkStruct4* var_r31;

    var_r31 = &lbl_1_bss_11C[object->work[0]];
    if (var_r31->unk14 == 0.0f) {
        var_r31->unk14 = 1.0f;
    }
}

s32 fn_1_18FC(omObjData* object, Vec arg1, f32 arg8, f32 arg9) {
    M418DllUnkStruct4* temp_r30;
    s32 var_r28;
    f32 var_f31;
    f32 var_f30;
    f32 var_f27;
    f32 var_f26;
    f32 var_f24;
    f32 var_f20;

    var_r28 = 0;
    temp_r30 = &lbl_1_bss_11C[object->work[0]];
    var_f31 = arg1.x - object->trans.x;
    var_f30 = object->trans.z - arg1.z;
    var_f26 = 90.0 + atan2d(var_f30, var_f31);
    var_f27 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
    if (var_f27 <= 15.0f) {
        var_f31 = var_f30 = 0.0f;
    } else {
        var_f31 = 55.0f * (var_f31 / var_f27);
        var_f30 = 55.0f * (var_f30 / var_f27);
    }
    if (temp_r30->unk14 == 1.0f) {
        temp_r30->unk18 = -1.47f;
    }
    var_f27 = arg9 * (sqrtf((var_f31 * var_f31) + (var_f30 * var_f30)) / 72.0f);
    if (var_f27 >= arg9) {
        var_f27 = arg9;
    } else if (var_f27 <= 1.0f) {
            var_f31 = var_f30 = var_f27 = 0.0f;
            var_r28 = 1;
    }
    if (var_f31 != 0.0f || var_f30 != 0.0f || arg8 >= 0.0f) {
        if (arg8 >= 0.0f && var_f31 == 0.0f && var_f30 == 0.0f) {
            var_f26 = arg8;
        }
        if (var_f26 >= 180.0f) {
            if (object->rot.y - var_f26 >= 180.0f) {
                object->rot.y -= 360.0f;
            }
            if (object->rot.y - var_f26 < -180.0f) {
                object->rot.y += 360.0f;
            }
        } else {
            if (object->rot.y - var_f26 > 180.0f) {
                object->rot.y -= 360.0f;
            }
            if (object->rot.y - var_f26 <= -180.0f) {
                object->rot.y += 360.0f;
            }
        }
        object->rot.y = (((9.0f * object->rot.y) + var_f26) / 10.0f);
    }
    object->trans.x += var_f27 * sind(object->rot.y);
    object->trans.z += var_f27 * cosd(object->rot.y);
    if (temp_r30->unk14) {
        temp_r30->unk14 = 2.0f;
        if (temp_r30->unk18 > 1.7f) {
            temp_r30->unk18 = 1.7f;
        }
        var_f20 = (temp_r30->unk18 * temp_r30->unk18) * (temp_r30->unk18 >= 0.0f ? -3.5f : 3.5f);
        object->trans.y += var_f20;
        if (object->trans.y <= arg1.y) {
            object->trans.y = arg1.y;
            temp_r30->unk14 = temp_r30->unk18 = 0.0f;
            var_r28 = 2;
        }
        temp_r30->unk18 += 0.11f;
    }
    if (var_f27 > 0.0f) {
        fn_1_AD14(object, 0, 1, 10, 1);
    } else {
        fn_1_AD14(object, 0, 0, 10, 1);
    }
    return var_r28;
}

s32 fn_1_20B0(omObjData* object, Vec arg1, f32 arg8, f32 arg9, s32 arg2) {
    if (arg2 == 1) fn_1_18AC(object);
    return fn_1_18FC(object, arg1, arg9, arg8);
}

Vec lbl_1_data_8C[9] = {
    {  140.0f,    0.0f,  -90.0f },
    { -200.0f,    0.0f,   50.0f },
    { -300.0f,    0.0f, -150.0f },
    { -250.0f,    0.0f, -500.0f },
    {    0.0f,    0.0f,  150.0f },
    {  700.0f,    0.0f,   50.0f },
    { 1000.0f,  -50.0f,  500.0f },
    { 1000.0f, -100.0f,  500.0f },
    { 1000.0f, -150.0f,  500.0f }
};

s32 fn_1_2178(omObjData* object) {
    s32 var_r30;
    
    switch (object->work[1]) {
        case 1:
            object->work[2] = 0;
            object->work[1] = 10;
        case 10:
            fn_1_20B0(object, lbl_1_data_8C[1], 0.0f, 25.0f, 0);
            if (object->work[2]++ >= 15) {
                object->work[1] = 11;
                object->work[2] = 0;
            }
            break;
        case 11:
            var_r30 = fn_1_20B0(object, lbl_1_data_8C[1], 6.0f, -1.0f, 0);
            if (var_r30 != 0) {
                object->work[1] = 12;
                object->work[2] = 0;
            }
            break;
        case 12:
            fn_1_20B0(object, lbl_1_data_8C[1], 0.0f, 0.0f, 0);
            if (object->work[2]++ >= 15) {
                object->work[1] = 13;
                object->work[2] = 0;
            }
            break;
            
        case 2:
            object->work[2] = 0;
            object->work[1] = 0x14;
        case 20:
            fn_1_20B0(object, lbl_1_data_8C[0], 0.0f, 25.0f, 0);
            if (object->work[2]++ >= 15) {
                object->work[1] = 21;
                object->work[2] = 0;
            }
            break;
        case 21:
            var_r30 = fn_1_20B0(object, lbl_1_data_8C[4], 6.0f, -1.0f, 0);
            if (var_r30 != 0) {
                object->work[1] = 22;
                object->work[2] = 0;
            }
            break;
        case 22:
            var_r30 = fn_1_20B0(object, lbl_1_data_8C[0], 6.0f, 0.0f, 0);
            if (var_r30 != 0) {
                object->work[1] = 24;
                object->work[2] = 0;
            }
            break;
        case 23:
            fn_1_20B0(object, lbl_1_data_8C[1], 0.0f, 0.0f, 0);
            if (object->work[2]++ >= 30) {
                object->work[1] = 24;
                object->work[2] = 0;
            }
            break;
        case 3:
            object->work[2] = 0;
            object->work[1] = 30;
        case 30:
            var_r30 = fn_1_20B0(object, lbl_1_data_8C[5], 6.0f, -1.0f, 0);
            if (var_r30 == 1) {
                object->work[1] = 31;
                object->work[2] = 0;
            }
            break;
        case 31:
            var_r30 = fn_1_20B0(object, lbl_1_data_8C[6], 6.0f, -1.0f, 1);
            if (var_r30 != 0) {
                object->work[1] = 32;
                object->work[2] = 0;
            }
            break;
        case 32:
            var_r30 = fn_1_20B0(object, lbl_1_data_8C[7], 6.0f, -1.0f, 1);
            if (var_r30 != 0) {
                object->work[1] = 33;
                object->work[2] = 0;
            }
            break;
        case 33:
            var_r30 = fn_1_20B0(object, lbl_1_data_8C[8], 6.0f, -1.0f, 1);
            if (var_r30 != 0) {
                object->work[1] = 34;
                object->work[2] = 0;
            }
            break;
    }
}
