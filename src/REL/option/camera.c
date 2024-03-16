#include "REL/option.h"
#include "game/hsfman.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/process.h"

#include "dolphin.h"
#include "math.h"

typedef struct {
    /* 0x00 */ Vec unk00;
    /* 0x0C */ Vec unk0C;
    /* 0x18 */ float unk18;
    /* 0x1C */ float unk1C;
    /* 0x20 */ float unk20;
    /* 0x24 */ float unk24;
    /* 0x28 */ float unk28;
    /* 0x2C */ Vec unk2C;
    /* 0x38 */ Vec unk38;
    /* 0x44 */ char unk44[0xC];
    /* 0x50 */ float unk50;
    /* 0x54 */ float unk54;
    /* 0x58 */ Vec unk58;
    /* 0x64 */ Vec unk64;
    /* 0x70 */ char unk70[0xC];
    /* 0x7C */ float unk7C;
    /* 0x80 */ float unk80;
    /* 0x84 */ float unk84;
    /* 0x88 */ float unk88;
    /* 0x8C */ float unk8C;
    /* 0x90 */ float unk90;
    /* 0x94 */ float unk94;
    /* 0x98 */ float unk98;
} UnkCameraDataStruct; // Size 0x9C

static void fn_1_C58(omObjData *arg0, float *arg1, float *arg2, float *arg3);
static void fn_1_D44(omObjData *arg0);
static void fn_1_D6C(omObjData *arg0);
static void fn_1_12E4(omObjData *arg0);
static void fn_1_14E4(omObjData *arg0);

omObjData *lbl_1_bss_10;

static float pad_04_00000000_data[] = {
    0.0f, 500.0f, 0.0f,
    0.0f,  -1.0f, 0.0f
};

static s32 pad_04_00000018_data = -1;

omObjData *fn_1_7F8(void) {
    omObjData *var_r30;
    UnkCameraDataStruct *temp_r31;

    var_r30 = omAddObjEx(lbl_1_bss_8, 1001, 0, 0, 3, fn_1_D44);
    temp_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkCameraDataStruct), MEMORY_DEFAULT_NUM);
    var_r30->data = temp_r31;
    temp_r31->unk00.x = 0.0f;
    temp_r31->unk00.y = 0.0f;
    temp_r31->unk00.z = 0.0f;
    temp_r31->unk0C.x = 0.0f;
    temp_r31->unk0C.y = 0.0f;
    temp_r31->unk0C.z = 0.0f;
    temp_r31->unk18 = 0.0f;
    temp_r31->unk1C = 1.0f;
    temp_r31->unk20 = 0.0f;
    temp_r31->unk24 = 0.0f;
    temp_r31->unk28 = 0.0f;
    temp_r31->unk8C = 1.0f;
    temp_r31->unk84 = 1.0f;
    temp_r31->unk94 = 1.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 42.0f, 10.0f, 8000.0f, 1.2f);
    fn_1_B74(var_r30, 600.0f, 60.0f, 120.0f, 1);
    fn_1_A6C(var_r30, 180.0f, 120.0f, 0.0f, 1);
    return var_r30;
}

void fn_1_A3C(omObjData *arg0) {
    HuMemDirectFree(arg0->data);
}

void fn_1_A6C(omObjData *arg0, float arg1, float arg2, float arg3, s32 arg4) {
    UnkCameraDataStruct *temp_r31 = arg0->data;

    temp_r31->unk58.x = arg1;
    temp_r31->unk58.y = arg2;
    temp_r31->unk58.z = arg3;
    temp_r31->unk2C = temp_r31->unk00;
    temp_r31->unk84 = 0.0f;
    temp_r31->unk88 = 1.0f / arg4;
}

void fn_1_AF0(omObjData *arg0, float arg1, float arg2, float arg3, s32 arg4) {
    UnkCameraDataStruct *temp_r31 = arg0->data;

    temp_r31->unk64.x = arg1;
    temp_r31->unk64.y = arg2;
    temp_r31->unk64.z = arg3;
    temp_r31->unk38 = temp_r31->unk0C;
    temp_r31->unk8C = 0.0f;
    temp_r31->unk90 = 1.0f / arg4;
}

void fn_1_B74(omObjData *arg0, float arg1, float arg2, float arg3, s32 arg4) {
    UnkCameraDataStruct *temp_r31 = arg0->data;

    temp_r31->unk64.y = arg3;
    temp_r31->unk7C = arg1;
    temp_r31->unk80 = arg2;
    temp_r31->unk38.y = temp_r31->unk0C.y;
    temp_r31->unk50 = temp_r31->unk24;
    temp_r31->unk54 = temp_r31->unk28;
    temp_r31->unk94 = 0.0f;
    temp_r31->unk98 = 1.0f / arg4;
}

float fn_1_BF8(omObjData *arg0) {
    UnkCameraDataStruct *temp_r31 = arg0->data;
    float temp_f31;

    temp_f31 = temp_r31->unk24;
    return temp_f31;
}

float fn_1_C28(omObjData *arg0) {
    UnkCameraDataStruct *temp_r31 = arg0->data;
    float temp_f31;

    temp_f31 = temp_r31->unk28;
    return temp_f31;
}

static void fn_1_C58(omObjData *arg0, float *arg1, float *arg2, float *arg3) {
    UnkCameraDataStruct *temp_r31 = arg0->data;

    *arg1 = temp_r31->unk00.x;
    *arg2 = temp_r31->unk00.y;
    *arg3 = temp_r31->unk00.z;
}

void fn_1_C88(omObjData *arg0, float *arg1, float *arg2, float *arg3) {
    UnkCameraDataStruct *temp_r31 = arg0->data;

    *arg1 = temp_r31->unk0C.x;
    *arg2 = temp_r31->unk0C.y;
    *arg3 = temp_r31->unk0C.z;
}

s32 fn_1_CB8(omObjData *arg0) {
    UnkCameraDataStruct *temp_r31 = arg0->data;
    s32 var_r30 = 1;
    s32 var_r29 = 1;

    if (!(temp_r31->unk8C < 1.0f) && !(temp_r31->unk94 < 1.0f)) {
        var_r29 = 0;
    }
    if (var_r29 == 0 && !(temp_r31->unk84 < 1.0f)) {
        var_r30 = 0;
    }
    return var_r30;
}

static void fn_1_D44(omObjData *arg0) {
    fn_1_D6C(arg0);
}

static void fn_1_D6C(omObjData *arg0) {
    UnkCameraDataStruct *temp_r31 = arg0->data;
    float temp_f28;
    float temp_f31;
    float temp_f30;

    if (temp_r31->unk84 < 1.0f) {
        temp_f28 = sin(90.0f * temp_r31->unk84 * M_PI / 180.0);
        temp_r31->unk00.x = temp_r31->unk2C.x + temp_f28 * (temp_r31->unk58.x - temp_r31->unk2C.x);
        temp_r31->unk00.y = temp_r31->unk2C.y + temp_f28 * (temp_r31->unk58.y - temp_r31->unk2C.y);
        temp_r31->unk00.z = temp_r31->unk2C.z + temp_f28 * (temp_r31->unk58.z - temp_r31->unk2C.z);
        if ((temp_r31->unk84 += temp_r31->unk88) >= 1.0f) {
            temp_r31->unk00 = temp_r31->unk58;
        }
    }
    if (temp_r31->unk8C < 1.0f) {
        temp_f28 = sin(90.0f * temp_r31->unk8C * M_PI / 180.0);
        temp_r31->unk0C.x = temp_r31->unk38.x + temp_f28 * (temp_r31->unk64.x - temp_r31->unk38.x);
        temp_r31->unk0C.y = temp_r31->unk38.y + temp_f28 * (temp_r31->unk64.y - temp_r31->unk38.y);
        temp_r31->unk0C.z = temp_r31->unk38.z + temp_f28 * (temp_r31->unk64.z - temp_r31->unk38.z);
        if ((temp_r31->unk8C += temp_r31->unk90) >= 1.0f) {
            temp_r31->unk0C = temp_r31->unk64;
        }
    }
    if (temp_r31->unk94 < 1.0f) {
        temp_f28 = sin(90.0f * temp_r31->unk94 * M_PI / 180.0);
        temp_r31->unk0C.y = temp_r31->unk38.y + temp_f28 * (temp_r31->unk64.y - temp_r31->unk38.y);
        temp_r31->unk24 = temp_r31->unk50 + temp_f28 * (temp_r31->unk7C - temp_r31->unk50);
        temp_r31->unk28 = temp_r31->unk54 + temp_f28 * (temp_r31->unk80 - temp_r31->unk54);
        if ((temp_r31->unk94 += temp_r31->unk98) >= 1.0f) {
            temp_r31->unk0C.y = temp_r31->unk64.y;
            temp_r31->unk24 = temp_r31->unk7C;
            temp_r31->unk28 = temp_r31->unk80;
        }
        temp_r31->unk0C.x = temp_r31->unk24 * -sin(temp_r31->unk28 * M_PI / 180.0);
        temp_r31->unk0C.z = temp_r31->unk24 * cos(temp_r31->unk28 * M_PI / 180.0);
    }
    temp_f31 = temp_r31->unk0C.x - temp_r31->unk00.x;
    temp_f30 = temp_r31->unk0C.z - temp_r31->unk00.z;
    temp_r31->unk24 = sqrtf(temp_f31 * temp_f31 + temp_f30 * temp_f30);
    temp_r31->unk28 = fmod(-(180.0 * (atan2(temp_f31, temp_f30) / M_PI)), 360.0);
    if (temp_r31->unk28 < 0.0f) {
        temp_r31->unk28 += 360.0f;
    }
    Hu3DCameraPosSet(1, temp_r31->unk00.x, temp_r31->unk00.y, temp_r31->unk00.z, temp_r31->unk18, temp_r31->unk1C, temp_r31->unk20, temp_r31->unk0C.x, temp_r31->unk0C.y, temp_r31->unk0C.z);
}

static void fn_1_12E4(omObjData *arg0) {
    UnkCameraDataStruct *temp_r31;

    if (HuPadBtn[0] & 0xF) {
        temp_r31 = arg0->data;
        temp_r31->unk0C.x += 0.5f * HuPadStkX[0];
        temp_r31->unk0C.y += 0.5f * HuPadStkY[0];
        temp_r31->unk00.z += 0.5f * HuPadTrigL[0];
        temp_r31->unk00.z -= 0.5f * HuPadTrigR[0];
        temp_r31->unk00.x += 0.5f * HuPadSubStkY[0];
        temp_r31->unk00.y += 0.5f * HuPadSubStkX[0];
    }
}

static void fn_1_14E4(omObjData *arg0) {
    UnkCameraDataStruct *temp_r31 = arg0->data;

    print8(32, 64, 1.5f, "AT  : x=%.2f y=%.2f z=%.2f", temp_r31->unk0C.x, temp_r31->unk0C.y, temp_r31->unk0C.z);
    print8(32, 80, 1.5f, "EYE : x=%.2f y=%.2f z=%.2f", temp_r31->unk00.x, temp_r31->unk00.y, temp_r31->unk00.z);
    print8(32, 96, 1.5f, "R : %.2f    DEG: %.2f", temp_r31->unk24, temp_r31->unk28);
}
