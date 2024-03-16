#include "REL/option.h"
#include "game/audio.h"
#include "game/hsfman.h"
#include "game/memory.h"
#include "game/process.h"
#include "game/window.h"

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ omObjData *unk04;
    /* 0x08 */ omObjData *unk08;
    /* 0x0C */ omObjData *unk0C;
    /* 0x10 */ UnkWindowDataStruct *unk10;
    /* 0x14 */ UnkWindowDataStruct *unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ char unk22[6];
    /* 0x28 */ s32 unk28;
} UnkRoomDataStruct; // Size 0x2C

static void fn_1_1844(omObjData *arg0, s32 arg1);
static void fn_1_1A8C(omObjData *arg0);
static omObjData *fn_1_2088(void);
static void fn_1_2110(omObjData *arg0);
static omObjData *fn_1_2144(void);
static void fn_1_21C4(omObjData *arg0);

omObjData *lbl_1_bss_18;

static omObjFunc lbl_1_data_68[] = {
    NULL,
    fn_1_1A8C
};

omObjData *fn_1_15A4(void) {
    omObjData *var_r30;
    UnkRoomDataStruct *temp_r31;

    var_r30 = omAddObjEx(lbl_1_bss_8, 1003, 0, 0, 1, NULL);
    temp_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkRoomDataStruct), MEMORY_DEFAULT_NUM);
    var_r30->data = temp_r31;
    temp_r31->unk18 = 0;
    temp_r31->unk20 = -1;
    temp_r31->unk28 = 0;
    fn_1_B74(lbl_1_bss_10, 600.0f, 60.0f, 120.0f, 1);
    fn_1_A6C(lbl_1_bss_10, 0.0f, 120.0f, 0.0f, 1);
    temp_r31->unk00 = fn_1_2088();
    lbl_1_bss_38 = fn_1_4028();
    lbl_1_bss_40 = fn_1_80E4();
    lbl_1_bss_30 = fn_1_3158();
    lbl_1_bss_20 = fn_1_21F8();
    temp_r31->unk04 = fn_1_2144();
    temp_r31->unk08 = fn_1_2144();
    temp_r31->unk0C = fn_1_2144();
    omSetRot(temp_r31->unk04, 0.0f, 0.0f, 0.0f);
    omSetRot(temp_r31->unk08, 0.0f, 120.0f, 0.0f);
    omSetRot(temp_r31->unk0C, 0.0f, 240.0f, 0.0f);
    temp_r31->unk10 = fn_1_A44C(0);
    temp_r31->unk14 = fn_1_A44C(1);
    return var_r30;
}

void fn_1_1798(omObjData *arg0) {
    UnkRoomDataStruct *temp_r31 = arg0->data;

    fn_1_2110(temp_r31->unk00);
    fn_1_42DC(lbl_1_bss_38);
    fn_1_322C(lbl_1_bss_30);
    fn_1_825C(lbl_1_bss_40);
    fn_1_241C(lbl_1_bss_20);
    fn_1_21C4(temp_r31->unk04);
    fn_1_21C4(temp_r31->unk08);
    fn_1_21C4(temp_r31->unk0C);
    fn_1_A6AC(temp_r31->unk10);
    fn_1_A6AC(temp_r31->unk14);
    HuMemDirectFree(temp_r31);
}

static const float lbl_1_rodata_BC[3] = { 45.0f, 165.0f, 285.0f };

static void fn_1_1844(omObjData *arg0, s32 arg1) {
    UnkRoomDataStruct *temp_r31 = arg0->data;
    float sp10;
    float spC;
    float sp8;
    float var_f31;

    temp_r31->unk18 += (arg1 == 0) ? -1 : 1;
    if (temp_r31->unk18 < 0) {
        temp_r31->unk18 = 2;
    } else if (temp_r31->unk18 >= 3) {
        temp_r31->unk18 = 0;
    }
    fn_1_C88(lbl_1_bss_10, &sp10, &spC, &sp8);
    fn_1_B74(lbl_1_bss_10, fn_1_BF8(lbl_1_bss_10), fn_1_C28(lbl_1_bss_10) + (arg1 == 0 ? -120.0f : 120.0f), spC, 0x60);
    if (temp_r31->unk18 == 2 && arg1 == 0) {
        var_f31 = lbl_1_rodata_BC[2] - 360.0f;
    } else if (temp_r31->unk18 == 0 && arg1 == 1) {
        var_f31 = 360.0f + lbl_1_rodata_BC[0];
    } else {
        var_f31 = lbl_1_rodata_BC[temp_r31->unk18];
    }
    fn_1_2508(lbl_1_bss_20, var_f31, 430.0f, 0x60);
}

void fn_1_1A2C(omObjData *arg0, s32 arg1) {
    UnkRoomDataStruct *temp_r31 = arg0->data;

    temp_r31->unk1C = arg1;
    arg0->func = lbl_1_data_68[arg1];
    arg0->unk10 = 0;
    arg0->unk10 = 0;
}

s32 fn_1_1A70(omObjData *arg0) {
    UnkRoomDataStruct *temp_r31 = arg0->data;

    return temp_r31->unk1C;
}

static const s32 lbl_1_rodata_D4[] = {
    MAKE_MESSID(47, 1),
    MAKE_MESSID(47, 7),
    MAKE_MESSID(47, 4)
};

static void fn_1_1A8C(omObjData *arg0) {
    UnkRoomDataStruct *temp_r31 = arg0->data;

    switch (arg0->unk10) {
        case 0:
            if (temp_r31->unk28 == 0) {
                fn_1_B74(lbl_1_bss_10, 600.0f, 60.0f, 120.0f, 1);
                fn_1_A6C(lbl_1_bss_10, 0.0f, 120.0f, 0.0f, 1);
                temp_r31->unk28 = 1;
            }
            arg0->unk10 = 1;
            /* fallthrough */
        case 1:
            if (fn_1_CB8(lbl_1_bss_10) != 0) {
                break;
            }
            fn_1_A6EC(temp_r31->unk10);
            fn_1_A71C(temp_r31->unk10, lbl_1_rodata_D4[temp_r31->unk18]);
            fn_1_A6EC(temp_r31->unk14);
            fn_1_A71C(temp_r31->unk14, MAKE_MESSID(47, 14));
            arg0->unk10 = 2;
            /* fallthrough */
        case 2:
            if (temp_r31->unk10->unk20 == 0 && temp_r31->unk14->unk20 == 0) {
                if (fn_1_550(0x200) != 0) {
                    HuAudFXPlay(3);
                    arg0->unk10 = 7;
                } else if (fn_1_584(1) != 0) {
                    fn_1_1844(arg0, 0);
                    fn_1_A704(temp_r31->unk10);
                    fn_1_A704(temp_r31->unk14);
                    HuAudFXPlay(0);
                    arg0->unk10 = 1;
                } else if (fn_1_584(2) != 0) {
                    fn_1_1844(arg0, 1);
                    fn_1_A704(temp_r31->unk10);
                    fn_1_A704(temp_r31->unk14);
                    HuAudFXPlay(0);
                    arg0->unk10 = 1;
                } else if (fn_1_550(0x100) != 0) {
                    fn_1_A704(temp_r31->unk10);
                    fn_1_A704(temp_r31->unk14);
                    HuAudFXPlay(2);
                    arg0->unk10 = 3;
                }
            }
            break;
        case 3:
            if (temp_r31->unk10->unk20 == 0 && temp_r31->unk14->unk20 == 0) {
                switch (temp_r31->unk18) {
                    case 0:
                        fn_1_3290(lbl_1_bss_30, 1);
                        arg0->unk10 = 4;
                        break;
                    case 1:
                        fn_1_4388(lbl_1_bss_38, 1);
                        arg0->unk10 = 5;
                        break;
                    case 2:
                        fn_1_82B0(lbl_1_bss_40, 1);
                        arg0->unk10 = 6;
                        break;
                }
            }
            break;
        case 4:
            if (fn_1_32D4(lbl_1_bss_30) == 0) {
                arg0->unk10 = 1;
            }
            break;
        case 5:
            if (fn_1_43CC(lbl_1_bss_38) == 0) {
                arg0->unk10 = 1;
            }
            break;
        case 6:
            if (fn_1_82F4(lbl_1_bss_40) == 0) {
                arg0->unk10 = 1;
            }
            break;
        case 7:
            fn_1_A704(temp_r31->unk10);
            fn_1_A704(temp_r31->unk14);
            arg0->unk10 = 8;
            /* fallthrough */
        case 8:
            if (temp_r31->unk10->unk20 == 0 && temp_r31->unk14->unk20 == 0) {
                fn_1_1A2C(arg0, 0);
            }
            break;
    }
}

static omObjData *fn_1_2088(void) {
    omObjData *temp_r31;

    temp_r31 = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    temp_r31->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 0));
    Hu3DModelLayerSet(temp_r31->model[0], 0);
    Hu3DModelShadowMapSet(temp_r31->model[0]);
    return temp_r31;
}

static void fn_1_2110(omObjData *arg0) {
    Hu3DModelKill(arg0->model[0]);
}

static omObjData *fn_1_2144(void) {
    omObjData *temp_r31;

    temp_r31 = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    Hu3DModelLayerSet(temp_r31->model[0], 0);
    temp_r31->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 6));
    return temp_r31;
}

static void fn_1_21C4(omObjData *arg0) {
    Hu3DModelKill(arg0->model[0]);
}
