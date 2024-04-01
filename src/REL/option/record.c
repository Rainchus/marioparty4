#include "REL/option.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/window.h"

#include "dolphin.h"
#include "math.h"

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04[8];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
} UnkRecordDataStruct00; // Size 0x2C

typedef struct {
    /* 0x000 */ omObjData *unk00;
    /* 0x004 */ omObjData *unk04;
    /* 0x008 */ UnkWindowDataStruct *unk08[10];
    /* 0x030 */ s32 unk30;
    /* 0x034 */ s16 unk34[153];
    /* 0x166 */ char unk166[6];
    /* 0x16C */ s32 unk16C;
    /* 0x170 */ s32 unk170;
    /* 0x174 */ s32 unk174;
    /* 0x178 */ UnkRecordDataStruct00 unk178[6];
    /* 0x280 */ s32 unk280[6];
    /* 0x298 */ s32 unk298;
    /* 0x29C */ s32 unk29C;
} UnkRecordDataStruct01; // Size 0x2A0

static void fn_1_8310(omObjData *arg0);
static omObjData *fn_1_8A88(void);
static void fn_1_8B58(omObjData *arg0);
static void fn_1_8BAC(omObjData *arg0, s32 arg1);
static omObjData *fn_1_8C84(void);
static void fn_1_8D80(omObjData *arg0);
static void fn_1_8DD4(omObjData *arg0);
static void fn_1_8E98(omObjData *arg0);
static s32 fn_1_8EF8(s32 arg0, s32 arg1);
static void fn_1_8F38(omObjData *arg0, s32 arg1);
static void fn_1_96B4(omObjData *arg0);
static void fn_1_9750(omObjData *arg0);
static void fn_1_9A94(omObjData *arg0);
static void fn_1_9B10(omObjData *arg0, s32 arg1);
static void fn_1_A3B0(omObjData *arg0);

omObjData *lbl_1_bss_40;

static const s32 lbl_1_rodata_13C0[] = { 0, 1, 2, 3, 5, 10 };

static omObjFunc lbl_1_data_210[] = {
    NULL,
    fn_1_8310
};

omObjData *fn_1_80E4(void) {
    omObjData *temp_r29;
    UnkRecordDataStruct01 *temp_r3;
    s32 i;
    s32 j;

    temp_r29 = omAddObjEx(lbl_1_bss_8, 1003, 0, 0, 1, NULL);
    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkRecordDataStruct01), MEMORY_DEFAULT_NUM);
    temp_r29->data = temp_r3;
    for (i = 0; i < 6; i++) {
        temp_r3->unk178[i].unk00 = GWBoardPlayCountGet(i);
        temp_r3->unk178[i].unk28 = GWBoardMaxStarsGet(i);
        temp_r3->unk178[i].unk24 = GWBoardMaxCoinsGet(i);
        for (j = 0; j < 8; j++) {
            temp_r3->unk178[i].unk04[j] = GWBoardWinCountGet(j, i);
        }
    }
    for (i = 0; i < 6; i++) {
        temp_r3->unk280[i] = GWMGRecordGet(lbl_1_rodata_13C0[i]);
    }
    temp_r3->unk170 = 0;
    temp_r3->unk174 = 0;
    temp_r3->unk16C = 0;
    temp_r3->unk00 = fn_1_8A88();
    temp_r3->unk04 = fn_1_8C84();
    fn_1_8DD4(temp_r29);
    fn_1_82B0(temp_r29, 0);
    return temp_r29;
}

void fn_1_825C(omObjData *arg0) {
    UnkRecordDataStruct01 *temp_r31 = arg0->data;

    fn_1_8B58(temp_r31->unk00);
    fn_1_8D80(temp_r31->unk04);
    fn_1_8E98(arg0);
    HuMemDirectFree(temp_r31);
}

void fn_1_82B0(omObjData *arg0, s32 arg1) {
    UnkRecordDataStruct01 *temp_r31 = arg0->data;

    temp_r31->unk30 = arg1;
    arg0->func = lbl_1_data_210[arg1];
    arg0->unk10 = 0;
    arg0->unk10 = 0;
}

s32 fn_1_82F4(omObjData *arg0) {
    UnkRecordDataStruct01 *temp_r31 = arg0->data;

    return temp_r31->unk30;
}

static void fn_1_8310(omObjData *arg0) {
    UnkRecordDataStruct01 *temp_r31 = arg0->data;
    Vec sp8;
    s32 i;

    switch (arg0->unk10) {
        case 0:
            temp_r31->unk08[0] = fn_1_A44C(0);
            temp_r31->unk08[1] = fn_1_A44C(1);
            for (i = 0; i < 8; i++) {
                temp_r31->unk08[i + 2] = fn_1_A44C(3);
            }
            fn_1_AF0(lbl_1_bss_10, 519.0f, 125.0f, 300.0f, 0x28);
            fn_1_A6C(lbl_1_bss_10, 308.98f, 125.0f, 178.74f, 0x28);
            temp_r31->unk170 = 0;
            temp_r31->unk174 = 0;
            temp_r31->unk298 = 0;
            arg0->unk10 = 1;
            /* fallthrough */
        case 1:
            if (fn_1_CB8(lbl_1_bss_10) != 0) {
                break;
            }
            fn_1_3D54(lbl_1_bss_30);
            espBankSet(temp_r31->unk34[47], 0);
            espBankSet(temp_r31->unk34[48], 2);
            espPosSet(temp_r31->unk34[47], 46.0f, 240.0f);
            espPosSet(temp_r31->unk34[48], 494.0f, 240.0f);
            if (temp_r31->unk16C == 0) {
                fn_1_160(temp_r31->unk34[47], 1, 10);
                fn_1_160(temp_r31->unk34[48], 1, 10);
                temp_r31->unk29C = 0;
            }
            arg0->unk10 = 2;
            /* fallthrough */
        case 2:
            fn_1_96B4(arg0);
            fn_1_A3B0(arg0);
            fn_1_9A94(arg0);
            switch (temp_r31->unk16C) {
                case 0:
                    if (temp_r31->unk170 < 6) {
                        fn_1_8F38(arg0, temp_r31->unk170);
                    } else {
                        fn_1_9750(arg0);
                    }
                    fn_1_A6EC(temp_r31->unk08[0]);
                    fn_1_A71C(temp_r31->unk08[0], MAKE_MESSID(47, 5));
                    break;
                case 1:
                    fn_1_9B10(arg0, temp_r31->unk174);
                    fn_1_A6EC(temp_r31->unk08[0]);
                    fn_1_A71C(temp_r31->unk08[0], MAKE_MESSID(47, 6));
                    break;
            }
            fn_1_A6EC(temp_r31->unk08[1]);
            fn_1_A71C(temp_r31->unk08[1], MAKE_MESSID(47, 169));
            if (temp_r31->unk298 == 0) {
                Hu3DModelAttrReset(temp_r31->unk04->model[0], 1);
                temp_r31->unk298 = 1;
            }
            sp8.x = 505.0 * -sin(305 * M_PI / 180.0);
            sp8.z = 505.0 * cos(305 * M_PI / 180.0);
            sp8.y = 144.0f - 14.0f * temp_r31->unk16C;
            omSetTra(temp_r31->unk04, sp8.x, sp8.y, sp8.z);
            arg0->unk10 = 3;
            /* fallthrough */
        case 3:
            if (temp_r31->unk29C > 0) {
                temp_r31->unk29C--;
                break;
            }
            espBankSet(temp_r31->unk34[47], 0);
            espBankSet(temp_r31->unk34[48], 2);
            arg0->unk10 = 4;
            /* fallthrough */
        case 4:
            if (temp_r31->unk08[1]->unk20 != 0) {
                break;
            }
            if (fn_1_550(0x200) != 0) {
                HuAudFXPlay(3);
                arg0->unk10 = 5;
            } else if (fn_1_584(8) != 0 && temp_r31->unk16C == 1) {
                temp_r31->unk16C = 0;
                temp_r31->unk170 = 0;
                fn_1_8BAC(temp_r31->unk00, temp_r31->unk16C);
                fn_1_160(temp_r31->unk34[47], 1, 5);
                fn_1_160(temp_r31->unk34[48], 1, 5);
                temp_r31->unk29C = 5;
                HuAudFXPlay(0x83F);
                arg0->unk10 = 2;
            } else if (fn_1_584(4) != 0 && temp_r31->unk16C == 0) {
                temp_r31->unk16C = 1;
                temp_r31->unk174 = 0;
                fn_1_8BAC(temp_r31->unk00, temp_r31->unk16C);
                fn_1_160(temp_r31->unk34[47], 0, 5);
                fn_1_160(temp_r31->unk34[48], 0, 5);
                temp_r31->unk29C = 5;
                HuAudFXPlay(0x83F);
                arg0->unk10 = 2;
            } else {
                switch (temp_r31->unk16C) {
                    case 0:
                        if (fn_1_550(0x40) != 0) {
                            if (--temp_r31->unk170 < 0) {
                                temp_r31->unk170 = 6;
                            }
                            if (GWGameStat.open_w06 == 0 && temp_r31->unk170 == 5) {
                                temp_r31->unk170--;
                            }
                            HuAudFXPlay(0x840);
                            espBankSet(temp_r31->unk34[47], 1);
                            temp_r31->unk29C = 0xA;
                            arg0->unk10 = 2;
                            return;
                        }
                        if (fn_1_550(0x20) != 0) {
                            if (++temp_r31->unk170 >= 7) {
                                temp_r31->unk170 = 0;
                            }
                            if (GWGameStat.open_w06 == 0 && temp_r31->unk170 == 5) {
                                temp_r31->unk170++;
                            }
                            HuAudFXPlay(0x840);
                            espBankSet(temp_r31->unk34[48], 3);
                            temp_r31->unk29C = 0xA;
                            arg0->unk10 = 2;
                        }
                        break;
                    case 1:
                        break;
                }
            }
            break;
        case 5:
            fn_1_3E1C(lbl_1_bss_30);
            if (temp_r31->unk16C == 0) {
                fn_1_160(temp_r31->unk34[47], 0, 10);
                fn_1_160(temp_r31->unk34[48], 0, 10);
            }
            fn_1_A704(temp_r31->unk08[0]);
            fn_1_A704(temp_r31->unk08[1]);
            Hu3DModelAttrSet(temp_r31->unk04->model[0], 1);
            arg0->unk10 = 6;
            /* fallthrough */
        case 6:
            if (temp_r31->unk08[1]->unk20 == 0 && fn_1_3ED0(lbl_1_bss_30) == 0) {
                for (i = 0; i < 10; i++) {
                    fn_1_A6AC(temp_r31->unk08[i]);
                }
                fn_1_96B4(arg0);
                fn_1_A3B0(arg0);
                fn_1_9A94(arg0);
                fn_1_AF0(lbl_1_bss_10, 519.62f, 120.0f, 300.0f, 0x28);
                fn_1_A6C(lbl_1_bss_10, 0.0f, 120.0f, 0.0f, 0x28);
                fn_1_82B0(arg0, 0);
            }
            break;
    }
}

static omObjData *fn_1_8A88(void) {
    omObjData *temp_r31;

    temp_r31 = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    temp_r31->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 1));
    Hu3DModelAttrSet(temp_r31->model[0], 0x40000002);
    Hu3DModelLayerSet(temp_r31->model[0], 0);
    Hu3DMotionStartEndSet(temp_r31->model[0], 0.0f, 6.0f);
    Hu3DMotionTimeSet(temp_r31->model[0], 6.0f);
    return temp_r31;
}

static void fn_1_8B58(omObjData *arg0) {
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(arg0->model[i]);
    }
}

static void fn_1_8BAC(omObjData *arg0, s32 arg1) {
    s16 temp_r31 = arg0->model[0];

    switch (arg1) {
        case 0:
            Hu3DMotionStartEndSet(temp_r31, 0.0f, 6.0f);
            Hu3DMotionTimeSet(temp_r31, 0.0f);
            break;
        case 1:
            Hu3DMotionStartEndSet(temp_r31, 6.0f, 12.0f);
            Hu3DMotionTimeSet(temp_r31, 6.0f);
            break;
    }
    Hu3DModelAttrReset(arg0->model[0], 0x40000002);
}

static omObjData *fn_1_8C84(void) {
    omObjData *temp_r31;

    temp_r31 = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    temp_r31->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 14));
    Hu3DModelLayerSet(temp_r31->model[0], 2);
    Hu3DModelAttrSet(temp_r31->model[0], 0x40000001);
    omSetRot(temp_r31, 30.0f, 190.0f, 0.0f);
    omSetSca(temp_r31, 0.6f, 0.6f, 0.6f);
    Hu3DModelAttrSet(temp_r31->model[0], 1);
    return temp_r31;
}

static void fn_1_8D80(omObjData *arg0) {
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(arg0->model[i]);
    }
}

static const s32 lbl_1_rodata_143C[153] = {
    DATA_MAKE_NUM(DATADIR_OPTION, 55),
    DATA_MAKE_NUM(DATADIR_OPTION, 56),
    DATA_MAKE_NUM(DATADIR_OPTION, 57),
    DATA_MAKE_NUM(DATADIR_OPTION, 58),
    DATA_MAKE_NUM(DATADIR_OPTION, 59),
    DATA_MAKE_NUM(DATADIR_OPTION, 60),
    DATA_MAKE_NUM(DATADIR_OPTION, 61),
    DATA_MAKE_NUM(DATADIR_OPTION, 62),
    DATA_MAKE_NUM(DATADIR_OPTION, 50),
    DATA_MAKE_NUM(DATADIR_OPTION, 51),
    DATA_MAKE_NUM(DATADIR_OPTION, 66),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 49),
    DATA_MAKE_NUM(DATADIR_OPTION, 49),
    DATA_MAKE_NUM(DATADIR_OPTION, 19),
    DATA_MAKE_NUM(DATADIR_OPTION, 20),
    DATA_MAKE_NUM(DATADIR_OPTION, 21),
    DATA_MAKE_NUM(DATADIR_OPTION, 22),
    DATA_MAKE_NUM(DATADIR_OPTION, 23),
    DATA_MAKE_NUM(DATADIR_OPTION, 24),
    DATA_MAKE_NUM(DATADIR_OPTION, 25),
    DATA_MAKE_NUM(DATADIR_OPTION, 26),
    DATA_MAKE_NUM(DATADIR_OPTION, 27),
    DATA_MAKE_NUM(DATADIR_OPTION, 28),
    DATA_MAKE_NUM(DATADIR_OPTION, 29),
    DATA_MAKE_NUM(DATADIR_OPTION, 30),
    DATA_MAKE_NUM(DATADIR_OPTION, 31),
    DATA_MAKE_NUM(DATADIR_OPTION, 32),
    DATA_MAKE_NUM(DATADIR_OPTION, 33),
    DATA_MAKE_NUM(DATADIR_OPTION, 34),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54)
};

static void fn_1_8DD4(omObjData *arg0) {
    UnkRecordDataStruct01 *temp_r31 = arg0->data;
    s32 i;

    for (i = 0; i < 153; i++) {
        temp_r31->unk34[i] = espEntry(lbl_1_rodata_143C[i], 0, 0);
        espDrawNoSet(temp_r31->unk34[i], 0x40);
        espDispOff(temp_r31->unk34[i]);
    }
    espBankSet(temp_r31->unk34[47], 0);
    espBankSet(temp_r31->unk34[48], 2);
    HuSprExecLayerSet(0x40, 1);
}

static void fn_1_8E98(omObjData *arg0) {
    UnkRecordDataStruct01 *temp_r31 = arg0->data;
    s32 i;

    for (i = 0; i < 153; i++) {
        espKill(temp_r31->unk34[i]);
    }
}

static s32 fn_1_8EF8(s32 arg0, s32 arg1) {
    s32 var_r31;

    var_r31 = 1;
    while (arg1-- != 0) {
        var_r31 *= 10;
    }
    return (arg0 % (var_r31 * 10)) / var_r31;
}

static void fn_1_8F38(omObjData *arg0, s32 arg1) {
    UnkRecordDataStruct01 *temp_r31 = arg0->data;
    s32 temp_r28;
    s32 i;
    s32 j;

    espPosSet(temp_r31->unk34[arg1], 275.0f, 72.0f);
    temp_r28 = temp_r31->unk178[temp_r31->unk170].unk00;
    for (i = 0; i < 4; i++) {
        espPosSet(temp_r31->unk34[i + 11], 323.0f + 20.0f * i, 116.0f);
        if (temp_r28 > 999) {
            espBankSet(temp_r31->unk34[i + 11], i + 10);
        } else {
            espBankSet(temp_r31->unk34[i + 11], fn_1_8EF8(temp_r28, 3 - i));
        }
    }
    espPosSet(temp_r31->unk34[8], 416.0f, 120.0f);
    temp_r28 = temp_r31->unk178[temp_r31->unk170].unk24;
    for (i = 0; i < 4; i++) {
        espPosSet(temp_r31->unk34[i + 15], 364.0f + 20.0f * i, 268.0f);
        if (temp_r28 > 999) {
            espBankSet(temp_r31->unk34[i + 15], i + 10);
        } else {
            espBankSet(temp_r31->unk34[i + 15], fn_1_8EF8(temp_r28, 3 - i));
        }
    }
    espPosSet(temp_r31->unk34[9], 456.0f, 268.0f);
    temp_r28 = temp_r31->unk178[temp_r31->unk170].unk28;
    for (i = 0; i < 4; i++) {
        espPosSet(temp_r31->unk34[i + 19], 364.0f + 20.0f * i, 312.0f);
        if (temp_r28 > 999) {
            espBankSet(temp_r31->unk34[i + 19], i + 10);
        } else {
            espBankSet(temp_r31->unk34[i + 19], fn_1_8EF8(temp_r28, 3 - i));
        }
    }
    espPosSet(temp_r31->unk34[10], 456.0f, 312.0f);
    for (i = 0; i < 8; i++) {
        espPosSet(temp_r31->unk34[i + 49], 92.0f + 50.0f * i, 200.0f);
        for (j = 0; j < 3; j++) {
            espPosSet(temp_r31->unk34[i * 3 + 23 + j], 80.0f + 50.0f * i + 12.0f * j, 230.0f);
            espBankSet(temp_r31->unk34[i * 3 + 23 + j], fn_1_8EF8(temp_r31->unk178[temp_r31->unk170].unk04[i], 2 - j));
        }
    }
    espPosSet(temp_r31->unk34[47], 48.0f, 240.0f);
    espPosSet(temp_r31->unk34[48], 492.0f, 240.0f);
    espDispOn(temp_r31->unk34[arg1]);
    for (i = 0; i < 4; i++) {
        espDispOn(temp_r31->unk34[i + 11]);
    }
    espDispOn(temp_r31->unk34[8]);
    for (i = 0; i < 4; i++) {
        espDispOn(temp_r31->unk34[i + 15]);
    }
    espDispOn(temp_r31->unk34[9]);
    for (i = 0; i < 4; i++) {
        espDispOn(temp_r31->unk34[i + 19]);
    }
    espDispOn(temp_r31->unk34[10]);
    for (i = 0; i < 8; i++) {
        espDispOn(temp_r31->unk34[i + 49]);
        for (j = 0; j < 3; j++) {
            espDispOn(temp_r31->unk34[i * 3 + 23 + j]);
        }
    }
    for (i = 0; i < 4; i++) {
        fn_1_A7F0(temp_r31->unk08[i + 2]);
    }
    fn_1_A7B0(temp_r31->unk08[2], 64.0f, 96.0f);
    fn_1_A71C(temp_r31->unk08[2], MAKE_MESSID(47, 19));
    fn_1_A7B0(temp_r31->unk08[3], 64.0f, 140.0f);
    fn_1_A71C(temp_r31->unk08[3], MAKE_MESSID(47, 20));
    fn_1_A7B0(temp_r31->unk08[4], 64.0f, 248.0f);
    fn_1_A71C(temp_r31->unk08[4], MAKE_MESSID(47, 21));
    fn_1_A7B0(temp_r31->unk08[5], 64.0f, 292.0f);
    fn_1_A71C(temp_r31->unk08[5], MAKE_MESSID(47, 22));
}

static const s32 lbl_1_rodata_16F8[53] = {
     0,  1,  2,  3,  4,  5, 49, 50, 51, 52,
    53, 54, 55, 56,  8,  9, 10, 11, 12, 13,
    14, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 38, 39, 40, 35, 36, 37, 41,
    42, 43, 44, 45, 46, 15, 16, 17, 18, 19,
    20, 21, 22
};

static void fn_1_96B4(omObjData *arg0) {
    UnkRecordDataStruct01 *temp_r31 = arg0->data;
    s32 i;

    for (i = 0; i < 53; i++) {
        espDispOff(temp_r31->unk34[lbl_1_rodata_16F8[i]]);
    }
    for (i = 0; i < 4; i++) {
        fn_1_A828(temp_r31->unk08[i + 2]);
    }
}

static void fn_1_9750(omObjData *arg0) {
    UnkRecordDataStruct01 *temp_r31 = arg0->data;
    s32 var_r27;
    s32 i;
    s32 j;

    espPosSet(temp_r31->unk34[6], 275.0f, 72.0f);
    for (i = 0; i < 8; i++) {
        espPosSet(temp_r31->unk34[i + 57], 148.0f + 80.0f * (i % 4), 172.0f + 104.0f * (i / 4));
        for (j = 0, var_r27 = 0; j < 6; j++) {
            var_r27 += temp_r31->unk178[j].unk04[i];
        }
        for (j = 0; j < 3; j++) {
            espPosSet(temp_r31->unk34[i * 3 + 65 + j], 132.0f + 80.0f * (i % 4) + 16.0f * j, 218.0f + 104.0f * (i / 4));
            espBankSet(temp_r31->unk34[i * 3 + 65 + j], fn_1_8EF8(var_r27, 2 - j));
        }
    }
    espDispOn(temp_r31->unk34[6]);
    for (i = 0; i < 8; i++) {
        espDispOn(temp_r31->unk34[i + 57]);
        for (j = 0; j < 3; j++) {
            espDispOn(temp_r31->unk34[i * 3 + 65 + j]);
        }
    }
    fn_1_A7B0(temp_r31->unk08[2], 136.0f, 96.0f);
    fn_1_A71C(temp_r31->unk08[2], MAKE_MESSID(47, 23));
    fn_1_A7F0(temp_r31->unk08[2]);
}

static const s32 lbl_1_rodata_17E8[33] = {
     6, 57, 58, 59, 60, 61, 62, 63, 64, 65,
    66, 67, 68, 69, 70, 71, 72, 73, 74, 75,
    76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
    86, 87, 88
};

static void fn_1_9A94(omObjData *arg0) {
    UnkRecordDataStruct01 *temp_r31 = arg0->data;
    s32 i;

    for (i = 0; i < 33; i++) {
        espDispOff(temp_r31->unk34[lbl_1_rodata_17E8[i]]);
    }
    fn_1_A828(temp_r31->unk08[2]);
}

static const s32 lbl_1_rodata_186C[6][3] = {
    { 0x00000195, MAKE_MESSID(23,  5), 0 },
    { 0x00000197, MAKE_MESSID(23,  7), 1 },
    { 0x000001AB, MAKE_MESSID(23, 27), 0 },
    { 0x000001B0, MAKE_MESSID(23, 32), 0 },
    { 0x000001BB, MAKE_MESSID(23, 43), 0 },
    { 0x000001C8, MAKE_MESSID(23, 54), 0 }
};

static void fn_1_9B10(omObjData *arg0, s32 arg1) {
    UnkRecordDataStruct01 *temp_r31 = arg0->data;
    s32 temp_r25;
    s32 temp_r27;
    s32 var_r28;
    s32 var_r26;
    s32 var_r17;
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 i;
    s32 j;

    espPosSet(temp_r31->unk34[7], 275.0f, 72.0f);
    espPosSet(temp_r31->unk34[47], 48.0f, 240.0f);
    espPosSet(temp_r31->unk34[48], 492.0f, 240.0f);
    espDispOn(temp_r31->unk34[7]);
    for (i = 0; i < 8; i++) {
        sp50 = 0;
        temp_r27 = i + arg1 * 8;
        if (temp_r27 >= 6) {
            break;
        }
        sp54 = GWMGAvailGet(lbl_1_rodata_186C[temp_r27][0]);
        temp_r25 = temp_r31->unk280[temp_r27];
        if (sp54 != 0) {
            switch (lbl_1_rodata_186C[temp_r27][2]) {
                case 1:
                    for (j = 0; j < 8; j++) {
                        var_r17 = fn_1_8EF8(temp_r25, 7 - j);
                        if (var_r17 != 0 || sp50 != 0 || j >= 7) {
                            espPosSet(temp_r31->unk34[i * 8 + 89 + j], 336.0f + 16.0f * j, 116.0f + 40.0f * i);
                            espBankSet(temp_r31->unk34[i * 8 + 89 + j], var_r17);
                            espDispOn(temp_r31->unk34[i * 8 + 89 + j]);
                            sp50 = 1;
                        }
                    }
                    break;
                case 0:
                    sp5C = temp_r25 / 3600;
                    sp58 = (temp_r25 % 3600) / 60;
                    var_r26 = (temp_r25 % 3600) % 60;
                    if (lbl_1_rodata_186C[temp_r27][0] == 0x195 || lbl_1_rodata_186C[temp_r27][0] == 0x1B0) {
                        var_r26 *= 1.6916667f;
                    } else {
                        var_r26 *= 1.6666666f;
                    }
                    for (j = 1; j < 8; j++) {
                        espPosSet(temp_r31->unk34[i * 8 + 89 + j], 336.0f + 16.0f * j, 116.0f + 40.0f * i);
                        switch (j) {
                            case 0:
                                var_r28 = fn_1_8EF8(sp5C, 1);
                                break;
                            case 1:
                                var_r28 = fn_1_8EF8(sp5C, 0);
                                break;
                            case 3:
                                var_r28 = fn_1_8EF8(sp58, 1);
                                break;
                            case 4:
                                var_r28 = fn_1_8EF8(sp58, 0);
                                break;
                            case 6:
                                var_r28 = fn_1_8EF8(var_r26, 1);
                                break;
                            case 7:
                                var_r28 = fn_1_8EF8(var_r26, 0);
                                break;
                            case 2:
                                var_r28 = 11;
                                break;
                            case 5:
                                var_r28 = 12;
                                break;
                        }
                        espBankSet(temp_r31->unk34[i * 8 + 89 + j], var_r28);
                        espDispOn(temp_r31->unk34[i * 8 + 89 + j]);
                    }
                    break;
            }
        } else {
            for (j = 0; j < 8; j++) {
                espPosSet(temp_r31->unk34[i * 8 + 89 + j], 336.0f + 16.0f * j, 116.0f + 40.0f * i);
                espBankSet(temp_r31->unk34[i * 8 + 89 + j], 0);
                espDispOn(temp_r31->unk34[i * 8 + 89 + j]);
            }
        }
        fn_1_A7B0(temp_r31->unk08[i + 2], 60.0f, 96.0f + 40.0f * i);
        sp4C = (sp54 != 0) ? lbl_1_rodata_186C[temp_r27][1] : MAKE_MESSID(35, 0);
        fn_1_A71C(temp_r31->unk08[i + 2], sp4C);
        fn_1_A7F0(temp_r31->unk08[i + 2]);
    }
}

static const s32 lbl_1_rodata_18C8[65] = {
      7,  89,  90,  91,  92,  93,  94,  95,  96,  97,
     98,  99, 100, 101, 102, 103, 104, 105, 106, 107,
    108, 109, 110, 111, 112, 113, 114, 115, 116, 117,
    118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
    128, 129, 130, 131, 132, 133, 134, 135, 136, 137,
    138, 139, 140, 141, 142, 143, 144, 145, 146, 147,
    148, 149, 150, 151, 152
};

static void fn_1_A3B0(omObjData *arg0) {
    UnkRecordDataStruct01 *temp_r30 = arg0->data;
    s32 i;

    for (i = 0; i < 65; i++) {
        espDispOff(temp_r30->unk34[lbl_1_rodata_18C8[i]]);
    }
    for (i = 0; i < 8; i++) {
        fn_1_A828(temp_r30->unk08[i + 2]);
    }
}
