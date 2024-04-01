#include "REL/option.h"
#include "game/audio.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/window.h"

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ omObjData *unk04;
    /* 0x08 */ omObjData *unk08;
    /* 0x0C */ omObjData *unk0C;
    /* 0x10 */ omObjData *unk10;
    /* 0x14 */ UnkWindowDataStruct *unk14[2];
    /* 0x20 */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
} UnkRumbleDataStruct; // Size 0x2C

static void fn_1_32F0(omObjData *arg0);
static omObjData *fn_1_37AC(void);
static void fn_1_3868(omObjData *arg0);
static omObjData *fn_1_38BC(void);
static void fn_1_398C(omObjData *arg0);
static void fn_1_39E0(omObjData *arg0, s32 arg1, s32 arg2);
static omObjData *fn_1_3B08(void);
static void fn_1_3B8C(omObjData *arg0);
static void fn_1_3BE0(omObjData *arg0, s32 arg1);
static omObjData *fn_1_3C6C(void);
static void fn_1_3D00(omObjData *arg0);
static omObjData *fn_1_3F28(void);
static void fn_1_3FD4(omObjData *arg0);

omObjData *lbl_1_bss_30;

static omObjFunc lbl_1_data_108[] = {
    NULL,
    fn_1_32F0
};

omObjData *fn_1_3158(void) {
    omObjData *temp_r30;
    UnkRumbleDataStruct *temp_r3;

    temp_r30 = omAddObjEx(lbl_1_bss_8, 1003, 0, 0, 1, NULL);
    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkRumbleDataStruct), MEMORY_DEFAULT_NUM);
    temp_r30->data = temp_r3;
    temp_r3->unk20 = GWGameStat.rumble;
    temp_r3->unk00 = fn_1_38BC();
    fn_1_39E0(temp_r3->unk00, temp_r3->unk20, 0);
    temp_r3->unk04 = fn_1_3B08();
    fn_1_3BE0(temp_r3->unk04, temp_r3->unk20);
    temp_r3->unk08 = fn_1_3C6C();
    temp_r3->unk10 = fn_1_3F28();
    temp_r3->unk0C = fn_1_37AC();
    fn_1_3290(temp_r30, 0);
    return temp_r30;
}

void fn_1_322C(omObjData *arg0) {
    UnkRumbleDataStruct *temp_r31 = arg0->data;

    fn_1_3868(temp_r31->unk0C);
    fn_1_398C(temp_r31->unk00);
    fn_1_3B8C(temp_r31->unk04);
    fn_1_3FD4(temp_r31->unk10);
    fn_1_3D00(temp_r31->unk08);
    HuMemDirectFree(temp_r31);
}

void fn_1_3290(omObjData *arg0, s32 arg1) {
    UnkRumbleDataStruct *temp_r31 = arg0->data;

    temp_r31->unk1C = arg1;
    arg0->func = lbl_1_data_108[arg1];
    arg0->unk10 = 0;
    arg0->unk10 = 0;
}

s32 fn_1_32D4(omObjData *arg0) {
    UnkRumbleDataStruct *temp_r31 = arg0->data;

    return temp_r31->unk1C;
}

static void fn_1_32F0(omObjData *arg0) {
    UnkRumbleDataStruct *temp_r31 = arg0->data;
    s32 i;

    switch (arg0->unk10) {
        case 0:
            temp_r31->unk14[0] = fn_1_A44C(0);
            temp_r31->unk14[1] = fn_1_A44C(1);
            fn_1_AF0(lbl_1_bss_10, -519.62f, 135.0f, 300.0f, 0x28);
            fn_1_A6C(lbl_1_bss_10, -315.64f, 135.0f, 182.25f, 0x28);
            fn_1_3D54(arg0);
            Hu3DModelLayerSet(temp_r31->unk08->model[0], 1);
            temp_r31->unk24 = 0;
            arg0->unk10 = 1;
            /* fallthrough */
        case 1:
            if (fn_1_CB8(lbl_1_bss_10) != 0) {
                break;
            }
            if (temp_r31->unk24 == 0) {
                Hu3DModelAttrReset(temp_r31->unk0C->model[0], 1);
                temp_r31->unk24 = 1;
                Hu3DModelHookSet(temp_r31->unk00->model[0], "target", temp_r31->unk0C->model[0]);
            }
            fn_1_A6EC(temp_r31->unk14[1]);
            fn_1_A71C(temp_r31->unk14[1], MAKE_MESSID(47, 15));
            fn_1_A6EC(temp_r31->unk14[0]);
            if (temp_r31->unk20 != 0) {
                fn_1_A71C(temp_r31->unk14[0], MAKE_MESSID(47, 2));
            } else {
                fn_1_A71C(temp_r31->unk14[0], MAKE_MESSID(47, 3));
            }
            arg0->unk10 = 2;
            /* fallthrough */
        case 2:
            if (temp_r31->unk14[0]->unk20 == 0 && temp_r31->unk14[1]->unk20 == 0) {
                if (fn_1_550(0x200) != 0) {
                    HuAudFXPlay(3);
                    arg0->unk10 = 4;
                } else if (fn_1_584(8) != 0 && temp_r31->unk20 == 0) {
                    fn_1_39E0(temp_r31->unk00, 1, 1);
                    temp_r31->unk20 = 1;
                    temp_r31->unk28 = 0;
                    GWGameStat.rumble = 1;
                    arg0->unk10 = 3;
                } else if (fn_1_584(4) != 0 && temp_r31->unk20 != 0) {
                    fn_1_39E0(temp_r31->unk00, 0, 1);
                    temp_r31->unk20 = 0;
                    temp_r31->unk28 = 0;
                    GWGameStat.rumble = 0;
                    HuPadRumbleAllStop();
                    arg0->unk10 = 3;
                }
            }
            break;
        case 3:
            if (temp_r31->unk28++ >= 60) {
                HuAudFXPlay(0x83C);
                fn_1_3BE0(temp_r31->unk04, temp_r31->unk20);
                if (temp_r31->unk20 != 0) {
                    HuPadRumbleSet(0, 0x3C, 0xA, 5);
                    Hu3DMotionTimeSet(temp_r31->unk10->model[0], 0.0f);
                    Hu3DModelAttrReset(temp_r31->unk10->model[0], 1);
                } else {
                    Hu3DModelAttrSet(temp_r31->unk10->model[0], 1);
                }
                arg0->unk10 = 1;
            }
            break;
        case 4:
            fn_1_A704(temp_r31->unk14[1]);
            fn_1_A704(temp_r31->unk14[0]);
            Hu3DModelAttrSet(temp_r31->unk0C->model[0], 1);
            fn_1_3E1C(arg0);
            arg0->unk10 = 5;
            /* fallthrough */
        case 5:
            if (temp_r31->unk14[1]->unk20 == 0 && temp_r31->unk14[0]->unk20 == 0 && fn_1_3ED0(lbl_1_bss_30) == 0) {
                for (i = 0; i < 2; i++) {
                    fn_1_A6AC(temp_r31->unk14[i]);
                }
                Hu3DModelHookReset(temp_r31->unk00->model[0]);
                fn_1_AF0(lbl_1_bss_10, -519.62f, 120.0f, 300.0f, 0x28);
                fn_1_A6C(lbl_1_bss_10, 0.0f, 120.0f, 0.0f, 0x28);
                fn_1_3290(arg0, 0);
            }
            break;
    }
}

static omObjData *fn_1_37AC(void) {
    omObjData *temp_r31;

    temp_r31 = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    temp_r31->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 15));
    Hu3DModelLayerSet(temp_r31->model[0], 3);
    omSetRot(temp_r31, 0.0f, 180.0f, 0.0f);
    Hu3DModelAttrSet(temp_r31->model[0], 1);
    return temp_r31;
}

static void fn_1_3868(omObjData *arg0) {
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(arg0->model[i]);
    }
}

static omObjData *fn_1_38BC(void) {
    omObjData *temp_r31;

    temp_r31 = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    temp_r31->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 2));
    Hu3DModelAttrSet(temp_r31->model[0], 0x40000002);
    if (GWGameStat.rumble != 0) {
        Hu3DMotionTimeSet(temp_r31->model[0], 60.0f);
    } else {
        Hu3DMotionTimeSet(temp_r31->model[0], 0.0f);
    }
    return temp_r31;
}

static void fn_1_398C(omObjData *arg0) {
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(arg0->model[i]);
    }
}

static void fn_1_39E0(omObjData *arg0, s32 arg1, s32 arg2) {
    s16 temp_r31 = arg0->model[0];

    Hu3DModelAttrReset(arg0->model[0], 0x40000002);
    Hu3DModelAttrReset(arg0->model[0], 0x40000001);
    if (arg1 != 0) {
        Hu3DMotionStartEndSet(temp_r31, 60.0f, 120.0f);
        if (arg2 != 0) {
            Hu3DMotionTimeSet(temp_r31, 60.0f);
        } else {
            Hu3DMotionTimeSet(temp_r31, 119.0f);
        }
    } else {
        Hu3DMotionStartEndSet(temp_r31, 0.0f, 60.0f);
        if (arg2 != 0) {
            Hu3DMotionTimeSet(temp_r31, 0.0f);
        } else {
            Hu3DMotionTimeSet(temp_r31, 59.0f);
        }
    }
}

static omObjData *fn_1_3B08(void) {
    omObjData *temp_r31;

    temp_r31 = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    temp_r31->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 9));
    Hu3DModelAttrSet(temp_r31->model[0], 0x40000001);
    return temp_r31;
}

static void fn_1_3B8C(omObjData *arg0) {
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(arg0->model[i]);
    }
}

static void fn_1_3BE0(omObjData *arg0, s32 arg1) {
    if (arg1 != 0) {
        Hu3DModelAttrReset(arg0->model[0], 0x40000002);
        Hu3DModelAttrSet(arg0->model[0], 0x40000001);
    } else {
        Hu3DModelAttrSet(arg0->model[0], 0x40000002);
        Hu3DModelAttrReset(arg0->model[0], 0x40000001);
    }
}

static omObjData *fn_1_3C6C(void) {
    omObjData *temp_r31;

    temp_r31 = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    temp_r31->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 10));
    Hu3DModelAttrSet(temp_r31->model[0], 0x40000002);
    Hu3DModelLayerSet(temp_r31->model[0], 2);
    return temp_r31;
}

static void fn_1_3D00(omObjData *arg0) {
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(arg0->model[i]);
    }
}

void fn_1_3D54(omObjData *arg0) {
    UnkRumbleDataStruct *temp_r31 = arg0->data;
    s16 temp_r30 = temp_r31->unk08->model[0];

    Hu3DMotionStartEndSet(temp_r30, 0.0f, 40.0f);
    Hu3DMotionTimeSet(temp_r30, 0.0f);
    Hu3DModelAttrReset(temp_r31->unk08->model[0], 0x40000002);
    Hu3DModelAttrReset(temp_r31->unk08->model[0], 0x40000001);
    Hu3DModelLayerSet(temp_r31->unk08->model[0], 2);
    HuAudFXPlay(0x83D);
}

void fn_1_3E1C(omObjData *arg0) {
    UnkRumbleDataStruct *temp_r31 = arg0->data;
    s16 temp_r30 = temp_r31->unk08->model[0];

    Hu3DMotionStartEndSet(temp_r30, 40.0f, 80.0f);
    Hu3DMotionTimeSet(temp_r30, 40.0f);
    Hu3DModelAttrReset(temp_r31->unk08->model[0], 0x40000002);
    Hu3DModelAttrReset(temp_r31->unk08->model[0], 0x40000001);
    HuAudFXPlay(0x83E);
}

s32 fn_1_3ED0(omObjData *arg0) {
    UnkRumbleDataStruct *temp_r31 = arg0->data;
    s16 temp_r30 = temp_r31->unk08->model[0];

    return !Hu3DMotionEndCheck(temp_r30);
}

static omObjData *fn_1_3F28(void) {
    omObjData *temp_r31;

    temp_r31 = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    temp_r31->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 11));
    if (GWGameStat.rumble != 0) {
        Hu3DModelAttrReset(temp_r31->model[0], 1);
    } else {
        Hu3DModelAttrSet(temp_r31->model[0], 1);
    }
    return temp_r31;
}

static void fn_1_3FD4(omObjData *arg0) {
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(arg0->model[i]);
    }
}
