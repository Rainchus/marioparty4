#include "REL/option.h"
#include "game/hsfman.h"
#include "game/memory.h"
#include "game/window.h"
#include "game/wipe.h"

#include "dolphin.h"

typedef struct {
    /* 0x00 */ UnkWindowDataStruct *unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ char unk0A[2];
} UnkStateDataStruct; // Size 0xC

typedef struct {
    Vec unk00;
    Vec unk0C;
    GXColor unk18;
} UnkLightDataStruct; // Size 0x1C

static void fn_1_2FB0(omObjData *arg0);

omObjData *lbl_1_bss_28;

static UnkLightDataStruct lbl_1_data_A0 = {
    { 0.0f,  300.0f,    0.0f },
    { 0.0f, -300.0f, -600.0f },
    { 0xFF, 0xFF, 0xFF, 0xFF }
};

static Vec lbl_1_data_BC[3] = {
    { 0.0f, 3000.0f, 1.0f },
    { 0.0f,    1.0f, 0.0f },
    { 0.0f,    0.0f, 0.0f }
};

omObjData *fn_1_2E04(void) {
    omObjData *var_r30;
    UnkStateDataStruct *temp_r3;
    LightData *sp8;

    var_r30 = omAddObjEx(lbl_1_bss_8, 1000, 0, 0, 4, fn_1_2FB0);
    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkStateDataStruct), MEMORY_DEFAULT_NUM);
    var_r30->data = temp_r3;
    lbl_1_bss_10 = fn_1_7F8();
    lbl_1_bss_18 = fn_1_15A4();
    temp_r3->unk00 = fn_1_A44C(0);
    Hu3DLighInit();
    temp_r3->unk08 = Hu3DGLightCreateV(&lbl_1_data_A0.unk00, &lbl_1_data_A0.unk0C, &lbl_1_data_A0.unk18);
    Hu3DGLightInfinitytSet(temp_r3->unk08);
    sp8 = &Hu3DGlobalLight[temp_r3->unk08];
    Hu3DShadowCreate(30.0f, 20.0f, 5000.0f);
    Hu3DShadowTPLvlSet(0.45f);
    Hu3DShadowPosSet(&lbl_1_data_BC[0], &lbl_1_data_BC[1], &lbl_1_data_BC[2]);
    return var_r30;
}

void fn_1_2F4C(omObjData *arg0) {
    UnkStateDataStruct *temp_r31 = arg0->data;

    fn_1_A3C(lbl_1_bss_10);
    fn_1_1798(lbl_1_bss_18);
    fn_1_A6AC(temp_r31->unk00);
    HuMemDirectFree(temp_r31);
}

static void fn_1_2FB0(omObjData *arg0) {
    UnkStateDataStruct *temp_r31 = arg0->data;

    switch (arg0->unk10) {
        case 0:
            arg0->unk10 = 1;
            /* fallthrough */
        case 1:
            WipeCreate(1, -1, 0x3C);
            arg0->unk10 = 2;
            break;
        case 2:
            if (WipeStatGet() != 0 || temp_r31->unk00->unk20 != 0) {
                break;
            }
            fn_1_1A2C(lbl_1_bss_18, 1);
            arg0->unk10 = 3;
            /* fallthrough */
        case 3:
            if (fn_1_1A70(lbl_1_bss_18) != 0) {
                break;
            }
            arg0->unk10 = 4;
            /* fallthrough */
        case 4:
            fn_1_A6EC(temp_r31->unk00);
            fn_1_A71C(temp_r31->unk00, MAKE_MESSID(47, 167));
            arg0->unk10 = 5;
            /* fallthrough */
        case 5:
            if (temp_r31->unk00->unk20 != 0) {
                break;
            }
            fn_1_A880(temp_r31->unk00, 1);
            arg0->unk10 = 6;
            /* fallthrough */
        case 6:
            if (temp_r31->unk00->unk20 != 0) {
                break;
            }
            fn_1_A704(temp_r31->unk00);
            if (temp_r31->unk00->unk1C == 0) {
                temp_r31->unk04 = 0;
                arg0->unk10 = 7;
            } else {
                arg0->unk10 = 2;
            }
            break;
        case 7:
            arg0->unk10 = 8;
            temp_r31->unk04 = 0;
            /* fallthrough */
        case 8:
            if (temp_r31->unk00->unk20 == 0 && temp_r31->unk04++ >= 60) {
                omSysExitReq = 1;
            }
            break;
    }
}
