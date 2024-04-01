#include "REL/option.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"

#include "dolphin.h"
#include "math.h"

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ Vec unk08;
    /* 0x14 */ Vec unk14;
    /* 0x20 */ float unk20;
    /* 0x24 */ float unk24;
    /* 0x28 */ float unk28;
    /* 0x2C */ float unk2C;
    /* 0x30 */ float unk30;
    /* 0x34 */ float unk34;
    /* 0x38 */ float unk38;
    /* 0x3C */ float unk3C;
    /* 0x40 */ float unk40;
    /* 0x44 */ float unk44;
    /* 0x48 */ char unk48[0xC];
    /* 0x54 */ float unk54;
    /* 0x58 */ float unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
} UnkGuideDataStruct; // Size 0x64

static void fn_1_24A8(omObjData *arg0, s32 arg1);
static s32 fn_1_24EC(omObjData *arg0);
static void fn_1_25AC(omObjData *arg0);
static void fn_1_2A18(omObjData *arg0);
static float fn_1_2D00(float arg0, float arg1, float arg2);

omObjData *lbl_1_bss_20;

static const s32 lbl_1_rodata_E0[] = {
    DATA_MAKE_NUM(DATADIR_OPTION, 16),
    DATA_MAKE_NUM(DATADIR_OPTION, 17),
    DATA_MAKE_NUM(DATADIR_OPTION, 18)
};

static omObjFunc lbl_1_data_98[] = {
    NULL,
    fn_1_25AC
};

omObjData *fn_1_21F8(void) {
    omObjData *var_r31;
    UnkGuideDataStruct *temp_r30;
    s32 i;

    var_r31 = omAddObjEx(lbl_1_bss_8, 1002, 1, 3, 2, NULL);
    temp_r30 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkGuideDataStruct), MEMORY_DEFAULT_NUM);
    var_r31->data = temp_r30;
    temp_r30->unk08.x = -298.59f;
    temp_r30->unk08.z = 298.21f;
    temp_r30->unk08.y = 0.0f;
    temp_r30->unk20 = 0.0f;
    temp_r30->unk24 = 134.42f;
    temp_r30->unk28 = 0.0f;
    temp_r30->unk2C = 0.0f;
    temp_r30->unk34 = 0.0f;
    temp_r30->unk30 = 0.0f;
    var_r31->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 12));
    Hu3DModelLayerSet(var_r31->model[0], 1);
    for (i = 0; i < 3; i++) {
        var_r31->motion[i] = Hu3DJointMotion(var_r31->model[0], HuDataSelHeapReadNum(lbl_1_rodata_E0[i], MEMORY_DEFAULT_NUM, HEAP_DATA));
    }
    temp_r30->unk5C = CharModelEffectNpcInit(var_r31->model[0], var_r31->motion[2], 1, 0xC);
    temp_r30->unk60 = CharModelEffectNpcInit(var_r31->model[0], var_r31->motion[1], 0, 0xC);
    CharModelLayerSetAll(1);
    Hu3DModelShadowSet(var_r31->model[0]);
    Hu3DMotionShiftSet(var_r31->model[0], var_r31->motion[0], 0.0f, 8.0f, 0x40000001);
    fn_1_24A8(var_r31, 0);
    fn_1_2A18(var_r31);
    return var_r31;
}

void fn_1_241C(omObjData *arg0) {
    UnkGuideDataStruct *temp_r29 = arg0->data;
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(arg0->model[i]);
    }
    for (i = 0; i < 3; i++) {
        Hu3DMotionKill(arg0->motion[i]);
    }
    HuMemDirectFree(temp_r29);
}

static void fn_1_24A8(omObjData *arg0, s32 arg1) {
    UnkGuideDataStruct *temp_r31 = arg0->data;

    temp_r31->unk00 = arg1;
    arg0->func = lbl_1_data_98[arg1];
    arg0->unk10 = 0;
    arg0->unk10 = 0;
}

static s32 fn_1_24EC(omObjData *arg0) {
    UnkGuideDataStruct *temp_r31 = arg0->data;

    return temp_r31->unk00;
}

void fn_1_2508(omObjData *arg0, float arg1, float arg2, s32 arg3) {
    UnkGuideDataStruct *temp_r31 = arg0->data;

    temp_r31->unk40 = arg1;
    temp_r31->unk44 = arg2;
    temp_r31->unk54 = 0.0f;
    temp_r31->unk58 = 1.0f / arg3;
    temp_r31->unk04 = 0;
    fn_1_24A8(arg0, 1);
}

static void fn_1_25AC(omObjData *arg0) {
    UnkGuideDataStruct *temp_r31 = arg0->data;
    float var_f31;
    float var_f30;

    switch (arg0->unk10) {
        case 0:
            temp_r31->unk3C = fmod(-(180.0 * (atan2(temp_r31->unk08.x, temp_r31->unk08.z) / M_PI)), 360.0);
            if (temp_r31->unk3C < 0.0f) {
                temp_r31->unk3C += 360.0f;
            }
            arg0->unk10 = 1;
            /* fallthrough */
        case 1:
            var_f30 = sin(90.0f * temp_r31->unk54 * M_PI / 180.0);
            var_f31 = temp_r31->unk3C + var_f30 * (temp_r31->unk40 - temp_r31->unk3C);
            temp_r31->unk14.x = temp_r31->unk44 * -sin(var_f31 * M_PI / 180.0);
            temp_r31->unk14.z = temp_r31->unk44 * cos(var_f31 * M_PI / 180.0);
            temp_r31->unk14.y = 0.0f;
            temp_r31->unk2C = temp_r31->unk14.x - temp_r31->unk08.x;
            temp_r31->unk34 = temp_r31->unk14.z - temp_r31->unk08.z;
            if (temp_r31->unk54 <= 0.0f) {
                temp_r31->unk2C = 0.0f;
                temp_r31->unk34 = 0.0f;
                temp_r31->unk08 = temp_r31->unk14;
            }
            if ((temp_r31->unk54 += temp_r31->unk58) < 1.0f) {
                break;
            }
            var_f31 = fmod(-(180.0 * (atan2(temp_r31->unk08.x, temp_r31->unk08.z) / M_PI)), 360.0);
            if (var_f31 < 0.0f) {
                var_f31 += 360.0f;
            }
            temp_r31->unk14.x = 422.0 * -sin(var_f31 * M_PI / 180.0);
            temp_r31->unk14.z = 422.0 * cos(var_f31 * M_PI / 180.0);
            temp_r31->unk2C = (temp_r31->unk14.x - temp_r31->unk08.x) / 10.0f;
            temp_r31->unk34 = (temp_r31->unk14.z - temp_r31->unk08.z) / 10.0f;
            temp_r31->unk58 = 0.1f;
            temp_r31->unk54 = 0.0f;
            arg0->unk10 = 2;
            /* fallthrough */
        case 2:
            if ((temp_r31->unk54 += temp_r31->unk58) < 1.0f) {
                break;
            }
            arg0->unk10 = 3;
            /* fallthrough */
        case 3:
            temp_r31->unk08 = temp_r31->unk14;
            temp_r31->unk2C = 0.0f;
            temp_r31->unk30 = 0.0f;
            temp_r31->unk34 = 0.0f;
            fn_1_2A18(arg0);
            fn_1_24A8(arg0, 0);
            break;
    }
    fn_1_2A18(arg0);
}

static void fn_1_2A18(omObjData *arg0) {
    UnkGuideDataStruct *temp_r31 = arg0->data;
    s16 var_r29;

    var_r29 = 0;
    temp_r31->unk38 = sqrtf(temp_r31->unk2C * temp_r31->unk2C + temp_r31->unk34 * temp_r31->unk34);
    if (0.001f <= temp_r31->unk38) {
        if (14.0f <= temp_r31->unk38) {
            temp_r31->unk2C /= temp_r31->unk38;
            temp_r31->unk34 /= temp_r31->unk38;
            temp_r31->unk38 = 14.0f;
            temp_r31->unk2C = 14.0f * temp_r31->unk2C;
            temp_r31->unk34 = 14.0f * temp_r31->unk34;
        }
        temp_r31->unk24 = fn_1_2D00(temp_r31->unk24, 180.0 * (atan2(temp_r31->unk2C, temp_r31->unk34) / M_PI), 0.4f);
        if (8.0f <= temp_r31->unk38) {
            var_r29 = 2;
        } else {
            var_r29 = 1;
        }
    }
    temp_r31->unk08.x += temp_r31->unk2C;
    temp_r31->unk08.z += temp_r31->unk34;
    if (temp_r31->unk04 != var_r29) {
        Hu3DMotionShiftSet(*arg0->model, arg0->motion[var_r29], 0.0f, 8.0f, 0x40000001);
        temp_r31->unk04 = var_r29;
    }
    omSetTra(arg0, temp_r31->unk08.x, temp_r31->unk08.y, temp_r31->unk08.z);
    omSetRot(arg0, temp_r31->unk20, temp_r31->unk24, temp_r31->unk28);
}

static float fn_1_2D00(float arg0, float arg1, float arg2) {
    float var_f30;
    float var_f31;

    var_f31 = fmod(arg1 - arg0, 360.0);
    if (0.0f > var_f31) {
        var_f31 += 360.0f;
    }
    if (180.0f < var_f31) {
        var_f31 -= 360.0f;
    }
    var_f30 = fmod(arg0 + var_f31 * arg2, 360.0);
    if (0.0f > var_f30) {
        var_f30 += 360.0f;
    }
    return var_f30;
}
