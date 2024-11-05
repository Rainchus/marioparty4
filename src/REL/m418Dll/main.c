#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "rel_sqrt_consts.h"

#include "REL/m418Dll.h"

// types
typedef struct M418DllUnkStruct2 {
    char unk[0x4];
    s32 unk4[3];
    char unk10[0x4];
} M418DllUnkStruct2;

// bss
M418DllUnkStruct lbl_1_bss_1F4;
M418DllUnkStruct2 lbl_1_bss_1E0;
s32 lbl_1_bss_8;
s32 lbl_1_bss_4;
Process* lbl_1_bss_0;

// data
s32 lbl_1_data_8 = -1;

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
    char* sp8[2] = { 0, 0 };
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
